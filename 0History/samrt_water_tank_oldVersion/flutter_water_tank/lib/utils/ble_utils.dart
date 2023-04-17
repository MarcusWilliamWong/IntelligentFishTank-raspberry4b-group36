// //@dart=2.9
import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:flutter_water_tank/utils/ble.device.dart';
import 'package:flutter_water_tank/utils/ble.mode.dart';
import 'package:flutter_water_tank/utils/ble_callback.dart';
import 'package:flutter_water_tank/utils/ble_model_data.dart';
import 'package:flutter_water_tank/utils/date.utils.dart';
import 'package:flutter_water_tank/utils/shared_perferenc.dart';
import 'package:flutter_water_tank/utils/storage_active.dart';
import 'package:get/get.dart';
import 'package:location_service_check/location_service_check.dart';
import 'package:permission_handler/permission_handler.dart';

typedef ScanListener = void Function(List<BleDevice> list); //扫描
typedef ConnectListener = void Function(BleDevice bleDevice); //连接
typedef StopScanListener = void Function(); // 停止扫描
typedef DataListener = void Function(List<int> data); //监听数据
typedef DisconnectListener = void Function(); // 断开连接监听
typedef ConnectFailListener = void Function(); //连接失败
typedef DeviceFailListener = void Function(); //连接失败

class BleUtils {
  static BleUtils? _bleUtils;
  FlutterReactiveBle? _ble;
  BleStatus _bleStatus = BleStatus.unknown;
  BleStatus get bleStatus => _bleStatus;
  BleCallBack? _bleCallBack;
  static List<Uuid> uuids = [];

  late StreamSubscription<BleStatus?> _bleStatusSubscription; //蓝牙开启状态
  static StreamSubscription? _scanSubscription; //扫描订阅器

  num _scanningCount = 0; // 扫描次数
  num get scanningCount => _scanningCount;

  final num _limitScanningCount = 600; // 扫描次数限制，防止找不到设备时，一直扫描
  num get limitScanningCount => _limitScanningCount;

  final List<BleDevice> _bleDevices = <BleDevice>[]; //扫描发现的设备列表集合
  List<BleDevice> get bleDevices => _bleDevices;

  static final List<BleDevice> _activeBleDevices =
      <BleDevice>[]; //活动中(已连接)的设备列表集合
  List<BleDevice> get activeBleDevices => _activeBleDevices;
  //static List<StorageActiveBleDevice> _storageActiveBleDevices = []; //活动中(已连接)的设备列表集合(存入缓存)

  static BleUtils getInstance() {
    _bleUtils ??= BleUtils();
    return _bleUtils!;
  }

  void setCallBack(BleCallBack bleCallBack) {
    _bleCallBack = bleCallBack;
  }

  ///初始化uuid集合数据
  Future<void> initUuids() async {
    debugPrint("初始化uuid集合数据...");
    uuids.clear();
    for (BleModel bleModel in bleModels) {
      uuids.add(Uuid.parse(bleModel.uuidDiscover!));
    }
  }

  /// 初始化
  Future<BleUtils?> init() async {
    if (_ble == null) {
      debugPrint("初始化蓝牙连接管理器(FlutterReactiveBle)...");
      _ble = FlutterReactiveBle();
      await initUuids();

      //await _checkPermissions().catchError((e) => Log.e("蓝牙开启失败")).then((_) => _waitForBluetoothPoweredOn());
      _waitForBluetoothPoweredOn(); //.then((value) => _checkLocationPermissions().catchError((e) => Log.w("定位权限未授权")));
    }
    return _bleUtils;
  }

  // 蓝牙扫描
  Future<void> startScan() async {
    _scanningCount = 0;
    //必须先初始化
    await BleUtils.getInstance().init();

    //定位权限检查并请求
    if (!await checkAndRequestPermissions()) {
      return;
    }

    //检查蓝牙是否开启
    if (!await checkBluetoothSwitch()) {
      return;
    }

    //App是否获得发现附近的设备权限检查并请求（针对Android 12及以上）
    if (!await checkAndRequestBluetoothScanPermissions()) {
      return;
    }

    await stopScan(); //这里有个隐形的大bug，并不能确定底层硬件层面的停止扫描动作完成，导致下面重新扫描开启失败：Device scan fails with error: Exception: GenericFailure<ScanFailure>
    //_scanSubscription?.cancel();
    if (!isOpen()) {
      if (_bleCallBack != null) {
        _bleCallBack?.scanFailListener();
      }
      return;
    }

    debugPrint("开始扫描BLE蓝牙设备...");
    _bleDevices.clear();
    _scanSubscription =
        _ble!.scanForDevices(withServices: uuids).listen((device) async {
      _scanningCount += 1;
      //扫描600次
      debugPrint("第$_scanningCount次扫描...");
      // 通过else里面的函数添加已扫描的蓝牙设备 进行有条件地查询所需数据的位置
      final knownDeviceIndex = _bleDevices.indexWhere((d) {
        return d.discoveredDevice.id == device.id;
      });
      debugPrint('------------------------');
      debugPrint(knownDeviceIndex.toString());
      debugPrint('------------------------');
      // 有两种情况 1、已经缓存的设备现在能不能继续搜寻到 只显示目前能搜素到的设备
      //2. 找到新的设备
      if (knownDeviceIndex >= 0) {
        _bleDevices[knownDeviceIndex] = BleDevice(device);
        debugPrint(_bleDevices[knownDeviceIndex].toString());
      } else {
        //最开始是空的 ——bledevice是没有数据的 这里查找新的蓝牙设备
        debugPrint('found new device ${device.toString()}');
        //把找到的蓝牙设备 序列化
        var bleDevice = BleDevice(device);
        // 把找到的每一个设备都往_bledevice 里面添加
        _bleDevices.add(bleDevice);
        //connectBle(bleDevice);
        if (_bleCallBack != null) {
          _bleCallBack?.scanListener(_bleDevices);
        }
      }
    }, onError: (Object e) {
      debugPrint('Device scan fails with error: $e');
      if (_bleCallBack != null) {
        _bleCallBack?.scanFailListener();
      }
      /*debugPrint("由于扫描设备出现异常，正在尝试重新开始扫描BLE蓝牙设备...");
      Future<void>.delayed(
        const Duration(milliseconds: 2000),
            () async => BleUtils.getInstance().startScan(),
      );*/
    });
  }

  ///停止扫描
  Future<void> stopScan() async {
    debugPrint("停止扫描设备...");
    await _scanSubscription?.cancel();
    _scanSubscription = null;
    _bleCallBack?.stopScanListener();
    debugPrint("设备扫描已停止！");
  }

  ///刷新
  Future<void> refresh() async {
    await stopScan();
    await startScan();
  }

  ///检查蓝牙是否开启
  Future<bool> checkBluetoothSwitch() async {
    if (_ble!.status == BleStatus.poweredOff) {
      Get.defaultDialog(
          title: "提示",
          onConfirm: () {
            openAppSettings();
            Get.back();
            Get.back();
          },
          onCancel: () => {},
          middleText: "请打开蓝牙",
          textConfirm: "确认",
          textCancel: "取消",
          confirmTextColor: Colors.white);

      return Future.value(false);
    }
    return Future.value(true);
  }

  ///检查麦克风权限
  void checkPhonePermission(Permission permission) async {
    PermissionStatus status = await permission.request();
    if (status.isPermanentlyDenied) {
      openAppSettings();
    }
  }

  Future<bool> getPhonePermissionStatus() async {
    Permission permission = Permission.microphone;
    //granted 通过，denied 被拒绝，permanentlyDenied 拒绝且不在提示
    PermissionStatus status = await permission.status;
    if (status.isGranted) {
      return true;
    } else if (status.isDenied) {
      checkPhonePermission(permission);
    } else if (status.isPermanentlyDenied) {
      openAppSettings();
    } else if (status.isRestricted) {
      checkPhonePermission(permission);
    } else {}
    return false;
  }

  ///检查麦克风权限
  void checkCameraPermission(Permission permission) async {
    PermissionStatus status = await permission.request();
    if (status.isPermanentlyDenied) {
      openAppSettings();
    }
  }

  Future<bool> getCameraPermissionStatus() async {
    Permission permission = Permission.camera;
    //granted 通过，denied 被拒绝，permanentlyDenied 拒绝且不在提示
    PermissionStatus status = await permission.status;
    if (status.isGranted) {
      return true;
    } else if (status.isDenied) {
      checkCameraPermission(permission);
    } else if (status.isPermanentlyDenied) {
      openAppSettings();
    } else if (status.isRestricted) {
      checkCameraPermission(permission);
    } else {}
    return false;
  }

  ///定位权限检查并请求
  Future<bool> checkAndRequestPermissions() async {
    //检查App是否打开蓝牙开关(注：【iOS下判断不了是否开启系统蓝牙开关】)
    //iOS 13及以上版本：核心蓝牙管理器的授权状态。当运行<iOS 13或Android时，这始终是允许的。
    /*if (!await Permission.bluetooth.request().isGranted) {
      Loading.toast("请开启蓝牙权限");
      Get.defaultDialog(title:"提示信息", onConfirm: () {AppSettings.openBluetoothSettings();Get.back();}, onCancel:()=> {}, middleText: "请开启蓝牙权限", textConfirm: "确认", textCancel: "取消", confirmTextColor: Colors.white);
      return;
    }*/

    ///系统定位开关是否开启判断（注：只能判断系统定位是否开启，并不能判断App是否授权定位权限）
    if (!await LocationServiceCheck.checkLocationIsOpen) {
      //Loading.toast("need_open_gps");
      //Android直接打开系统的定位服务， iOS由于ios10开始不支持打开系统详细设置，所以打开应用的设置页
      Get.defaultDialog(
          title: "提示",
          onConfirm: () {
            LocationServiceCheck.openLocationSetting();
            Get.back();
            Get.back();
          },
          onCancel: () => {},
          middleText: "扫描蓝牙设备需要获取位置信息",
          textConfirm: "确认",
          textCancel: "取消",
          confirmTextColor: Colors.white);
      return Future.value(false);
    }

    bool isGranted = false;
    if (Platform.isAndroid) {
      //检查App是否获得定位权限(注：并不代表系统定位开关开启)，会等待系统对话框用户授权结果
      isGranted = await Permission.location.request().isGranted;
      /*await _checkLocationPermissions().catchError((e) {
        isGranted = false;
      });*/
    } else if (Platform.isIOS) {
      isGranted = true;
    }
    if (!isGranted) {
      //Loading.toast("扫描蓝牙设备需要获取位置信息");
      //Android/iOS直接打开当前应用详情页
      Get.defaultDialog(
          title: "提示",
          onConfirm: () {
            openAppSettings();
            Get.back();
            Get.back();
          },
          onCancel: () => {},
          middleText: "扫描蓝牙设备需要获取位置信息",
          textConfirm: "确认",
          textCancel: "取消",
          confirmTextColor: Colors.white);
      return Future.value(false);
    }
    return Future.value(true);
  }

  Future<void> _checkLocationPermissions() async {
    Completer completer = Completer();
    Map<Permission, PermissionStatus> statuses = await [
      Permission.location,
      Permission.locationWhenInUse,
      Permission.locationAlways,
    ].request();

    if (statuses[Permission.location] == PermissionStatus.granted) {
      completer.complete();
    }
    if (statuses[Permission.locationWhenInUse] == PermissionStatus.granted) {
      completer.complete();
    }
    if (statuses[Permission.locationAlways] == PermissionStatus.granted) {
      completer.complete();
    }
    completer.completeError("Not granted!");
    //return completer.future;
  }

  ///App是否获得发现附近的设备权限检查并请求（针对Android 12及以上）
  Future<bool> checkAndRequestBluetoothScanPermissions() async {
    bool isGranted = false;
    if (Platform.isAndroid) {
      //检查App是否获得发现附近的设备权限(注：Android12 关于蓝牙这部分新增了BLUETOOTH_SCAN、BLUETOOTH_ADVERTISE 和 BLUETOOTH_CONNECT 权限，这些权限都属于敏感权限，都需要在代码中动态申请。)，会等待系统对话框用户授权结果
      //参考：https://blog.csdn.net/ymclyor_pig/article/details/125534451  https://blog.csdn.net/androiddevs/article/details/122429617
      isGranted = await Permission.bluetoothScan.request().isGranted;
    } else if (Platform.isIOS) {
      isGranted = true;
    }
    if (!isGranted) {
      //Loading.toast("扫描蓝牙设备需要获取位置信息");
      //Android/iOS直接打开当前应用详情页

      Get.defaultDialog(
          title: "提示",
          onConfirm: () {
            openAppSettings();
            Get.back();
            Get.back();
          },
          onCancel: () => {},
          middleText: "请打开蓝牙",
          textConfirm: "确认",
          textCancel: "取消",
          confirmTextColor: Colors.white);

      return Future.value(false);
    }
    return Future.value(true);
  }

  bool isOpen() {
    return _bleStatus == BleStatus.ready;
  }

  /*Future<void> _checkPermissions() async {
    // 此方法为运行时，权限检测（ android4.4不支持）
    if (Platform.isAndroid) {
      await _bleManager.enableRadio();
      _bluetoothStatus = await _bleManager.bluetoothState();
      if (_bluetoothStatus != BluetoothState.POWERED_ON) {
        return Future.error(Exception("请开启蓝牙"));
      }
    }
  }*/

  Future<void> _waitForBluetoothPoweredOn() async {
    Completer completer = Completer();
    _bleStatusSubscription =
        _ble!.statusStream.listen((BleStatus? state) async {
      debugPrint("------------蓝牙是否打开：$state");
      if (state != null) {
        _bleStatus = state;
        if (_bleStatus == BleStatus.ready && !completer.isCompleted) {
          await _bleStatusSubscription.cancel();
          completer.complete();
        }
        if (_bleStatus == BleStatus.ready) {
        } else if (_bleStatus == BleStatus.poweredOff) {
          Get.defaultDialog(
              title: "提示",
              onConfirm: () {
                openAppSettings();
                Get.back();
                Get.back();
              },
              onCancel: () => {},
              middleText: "请打开蓝牙",
              textConfirm: "确认",
              textCancel: "取消",
              confirmTextColor: Colors.white);
        }
      }
    });
    return completer.future;
  }

  void dispose() async {
    debugPrint("销毁页面时调用dispose");
    await _scanSubscription?.cancel();
    //await destroyClient();
  }

  Future destroyClient() async {
    //await _bleUtils?.destroyClient(); //remember to release native resources when you're done!
    _bleUtils = null;
  }

  Future<void> radio() async {
    //_bleUtils?.enableRadio();
  }

  ///App是否获得连接设备的权限检查并请求（针对Android 12及以上）
  Future<bool> checkAndRequestBluetoothConnectPermissions() async {
    bool isGranted = false;
    if (Platform.isAndroid) {
      //检查App是否获得发现附近的设备权限(注：Android12 关于蓝牙这部分新增了BLUETOOTH_SCAN、BLUETOOTH_ADVERTISE 和 BLUETOOTH_CONNECT 权限，这些权限都属于敏感权限，都需要在代码中动态申请。)，会等待系统对话框用户授权结果
      //参考：https://blog.csdn.net/ymclyor_pig/article/details/125534451  https://blog.csdn.net/androiddevs/article/details/122429617
      isGranted = await Permission.bluetoothConnect.request().isGranted;
    } else if (Platform.isIOS) {
      isGranted = true;
    }
    if (!isGranted) {
      //Loading.toast("扫描蓝牙设备需要获取位置信息");
      //Android/iOS直接打开当前应用详情页
      Get.defaultDialog(
          title: "提示",
          onConfirm: () {
            openAppSettings();
            Get.back();
            Get.back();
          },
          onCancel: () => {},
          middleText: "请打开蓝牙",
          textConfirm: "确认",
          textCancel: "取消",
          confirmTextColor: Colors.white);
      return Future.value(false);
    }
    return Future.value(true);
  }

  ///连接BLE设备
  Future<void> connectBle(BleDevice bleDevice) async {
    //App是否获得连接设备的权限检查并请求（针对Android 12及以上）
    if (!await checkAndRequestBluetoothConnectPermissions()) {
      return;
    }
    //停止扫描
    await stopScan();
    String name =
        DataUtils.emptyStringToReplace(bleDevice.discoveredDevice.name);
    debugPrint("连接设备之前的名称：$name");
    debugPrint("BLE设备($name)连接开始...");
    Stream<ConnectionStateUpdate> currentConnectionStream = _ble!
        .connectToDevice(
            id: bleDevice.discoveredDevice.id,
            connectionTimeout: const Duration(milliseconds: 1000 * 30));
    bleDevice.connectionSubscription =
        currentConnectionStream.listen((event) async {
      doConnectionListen(bleDevice, event);
    }, onError: (Object e) {
      if (_bleCallBack != null) {
        _bleCallBack!.connectFailListener(bleDevice);
        //由于连接前会停止扫描，所以连接出现异常后重新开启扫描
        startScan();
      }
      debugPrint("--------BLE蓝牙设备($name)接收数据异常：$e");
    });
  }

  ///处理连接监听
  Future<void> doConnectionListen(BleDevice bleDevice, dynamic event) async {
    debugPrint(
        'ConnectionState for device ${event.deviceId} : ${event.connectionState}');
    switch (event.connectionState) {
      // We're connected and good to go!
      case DeviceConnectionState.connected:
        {
          await initService(bleDevice);
          break;
        }
      // Can add various state state updates on disconnect
      case DeviceConnectionState.disconnected:
        {
          if (_bleCallBack != null) {
            //event.deviceId
            _bleCallBack!.connectFailListener(bleDevice);
          }
          break;
        }
      default:
    }
  }

  ///连接BLE设备(连接前扫描)
  Future<void> connectToAdvertisingDevice(BleDevice bleDevice) async {
    //连接前先停止扫描，因为connectToAdvertisingDevice()方法会开启扫描
    await stopScan();
    //_scanner?.stopScan();
    //_scanSubscription?.cancel();
    String name =
        DataUtils.emptyStringToReplace(bleDevice.discoveredDevice.name);
    debugPrint("连接设备之前的名称：$name");
    debugPrint("BLE设备($name)连接开始...");
    BleModel? bleModel = await getBleModelUuidInfo(bleDevice);
    Stream<ConnectionStateUpdate> currentConnectionStream =
        _ble!.connectToAdvertisingDevice(
            id: bleDevice.discoveredDevice.id,
            withServices: [
              Uuid.parse(bleModel!.uuidDiscover!),
              Uuid.parse(bleModel.uuidWrite!),
              Uuid.parse(bleModel.uuidRead!)
            ],
            prescanDuration: const Duration(seconds: 1),
            connectionTimeout: const Duration(milliseconds: 1000 * 30));
    bleDevice.connectionSubscription =
        currentConnectionStream.listen((event) async {
      doConnectionListen(bleDevice, event);
    }, onError: (Object e) {
      if (_bleCallBack != null) {
        _bleCallBack!.connectFailListener(bleDevice);
      }
      debugPrint("--------BLE蓝牙设备($name)接收数据异常：$e");
    });
  }

  ///初始化服务
  Future<void> initService(BleDevice bleDevice) async {
    String name =
        DataUtils.emptyStringToReplace(bleDevice.discoveredDevice.name);
    debugPrint("----------BLE连接蓝牙设备($name)以及扫描特征值------");
    //特征值/描述符
    List<DiscoveredService> serviceList =
        await _ble!.discoverServices(bleDevice.discoveredDevice.id);
    BleModel? bleModel = await getBleModelUuidInfo(bleDevice);
    var uuidWrite = uuidToComplete(bleModel?.uuidWrite);
    for (int i = 0; i < serviceList.length; i++) {
      DiscoveredService discoveredService = serviceList[i];
      debugPrint(
          "BLE蓝牙设备($name)描述符UUID$i：${discoveredService.serviceId}，isWithout：${discoveredService.characteristics[0].isWritableWithoutResponse}");
      bool isFlag = false;
      for (int j = 0; j < discoveredService.characteristics.length; j++) {
        DiscoveredCharacteristic characteristic =
            discoveredService.characteristics[j];
        if (uuidWrite ==
            uuidToComplete(characteristic.characteristicId.toString())) {
          bleDevice.isWithout = characteristic.isWritableWithoutResponse;
          isFlag = true;
          break;
        }
      }
      if (isFlag) break;
    }

    bleDevice.isConnected = true;

    //添加到活动设备列表，并存储到缓存
    addActiveBleDevice(bleDevice);

    //去监听上报来的数据,参数来自前面扫描到的结果serviceId--服务ID, characteristicId--特征ID，deviceId--设备ID
    Timer(const Duration(milliseconds: 500), () async {
      //seconds: 1
      print("bleModel >>> ${bleModel}");
      await bleDevice.monitoringStreamSubscription?.cancel();
      final characteristic = QualifiedCharacteristic(
          serviceId: Uuid.parse(bleModel!.uuidCmd!),
          characteristicId: Uuid.parse(bleModel.uuidRead!),
          deviceId: bleDevice.discoveredDevice.id);
      bleDevice.monitoringStreamSubscription =
          _ble!.subscribeToCharacteristic(characteristic).listen((data) {
        // code to handle incoming data
        //debugPrint("deviceId =${bleDevice.discoveredDevice.id}---上报来的数据data = $data");
        if (_bleCallBack != null) {
          //监听到设备上报的数据后返回
          _bleCallBack!.dataListener(bleDevice.discoveredDevice.id, data);
        }
      }, onError: (dynamic error) {
        disconnect(bleDevice);
        // code to handle errors
        debugPrint("--------BLE蓝牙设备($name)接收数据异常：$error");
      }, cancelOnError: true, onDone: () {});
      //通知回调：连接成功
      if (_bleCallBack != null) {
        _bleCallBack!.connectListener(bleDevice);
      }
      debugPrint('BLE设备$name连接成功！');
    });
  }

  ///发送蓝牙命令到蓝牙板
  Future<void> writeCharacteristicWithoutResponse(
      BleDevice bleDevice, List<int> buffer,
      [bool isWithout = true]) async {
    BleModel? bleModel = await getBleModelUuidInfo(bleDevice);
    final writeCharacteristic = QualifiedCharacteristic(
        serviceId: Uuid.parse(bleModel!.uuidCmd!),
        characteristicId: Uuid.parse(bleModel.uuidWrite!),
        deviceId: bleDevice.discoveredDevice.id);
    if (bleDevice.isWithout) {
      await _ble?.writeCharacteristicWithoutResponse(writeCharacteristic,
          value: buffer);
    } else {
      await _ble?.writeCharacteristicWithResponse(writeCharacteristic,
          value: buffer); //Uint8List.fromList(buffer)
    }
  }

  ///释放连接
  Future<void> disconnect(BleDevice bleDevice) async {
    if (_bleUtils == null) return;
    if (bleDevice.isConnected) {
      debugPrint("BLE正在断开设备(${bleDevice.discoveredDevice.id})连接(正常断开)...");
      try {
        await bleDevice.monitoringStreamSubscription?.cancel();
        await bleDevice.connectionSubscription?.cancel();
        bleDevice.connectionSubscription = null;
        debugPrint("BLE设备(${bleDevice.discoveredDevice.id})连接已断开(正常断开)...");
        bleDevice.isConnected = false;
        //从活动列表移除设备
        removeActiveBleDevice(bleDevice);
        if (_bleCallBack != null) {
          _bleCallBack?.disconnectListener();
        }
      } on Exception catch (e, _) {
        debugPrint("BLE设备(${bleDevice.discoveredDevice.id})连接断开时出现异常：$e");
      } finally {}
    }
  }

  ///释放所有连接（App正常情况下退出时使用）
  Future<void> disconnectAll() async {
    for (BleDevice bleDevice in _activeBleDevices) {
      disconnect(bleDevice);
    }
  }

  ///释放所有连接（App非正常情况下退出时使用）
  ///解决：iOS应用运行时在设置中更改权限应用崩溃问题 https://blog.csdn.net/YLGWHYH/article/details/51164238
  Future<void> disconnectAllUnsafe() async {
    //if (Platform.isIOS) {
    //必须先初始化
    BleUtils? bleUtils = await BleUtils.getInstance().init();
    List<dynamic> storageList = await getStorageActiveBleDevices();
    for (var element in storageList) {
      BleModel? bleModel =
          await getBleModelUuidInfoByModelName(element["name"]);
      final StreamSubscription<ConnectionStateUpdate>? connectionSubscription =
          bleUtils?._ble!
              .connectToAdvertisingDevice(
                  id: element["id"],
                  withServices: [
                    Uuid.parse(bleModel!.uuidDiscover!),
                    Uuid.parse(bleModel.uuidWrite!),
                    Uuid.parse(bleModel.uuidRead!)
                  ],
                  prescanDuration: const Duration(seconds: 1),
                  connectionTimeout: const Duration(milliseconds: 1000 * 30))
              .listen((update) async {
        debugPrint(
            'ConnectionState for device ${update.deviceId} : ${update.connectionState}');
        debugPrint("BLE正在断开设备(${element["id"]})连接(非正常断开：Unsafe)...");
        //未完成，待定
        //connectionSubscription?.cancel();
      }, onError: (Object e) {});
    }

    _activeBleDevices.clear();
    //setStorageActiveBleDevices([]);//清空缓存
    //}
  }

  ///恢复所有连接
  ///但请记住，如果不先扫描，Android 可能仍然无法找到外围设备
  Future<void> recoveryAllUnsafe() async {
    //必须先初始化
    BleUtils? bleUtils = await BleUtils.getInstance().init();
    List<dynamic> storageList = await getStorageActiveBleDevices();
    List<StorageActiveBleDevice> storageActiveBleDevices = [];

    for (var element in storageList) {
      BleModel? bleModel =
          await getBleModelUuidInfoByModelName(element["name"]);
      debugPrint("BLE正在恢复设备(${element["id"]})连接(Unsafe)...");
      final StreamSubscription<ConnectionStateUpdate> connectionSubscription =
          bleUtils!._ble!
              .connectToAdvertisingDevice(
                  id: element["id"],
                  withServices: [
                    Uuid.parse(bleModel!.uuidDiscover!),
                    Uuid.parse(bleModel.uuidWrite!),
                    Uuid.parse(bleModel.uuidRead!)
                  ],
                  prescanDuration: const Duration(seconds: 1),
                  connectionTimeout: const Duration(milliseconds: 1000 * 30))
              .listen((update) async {
        debugPrint(
            'ConnectionState for device ${update.deviceId} : ${update.connectionState}');
        //await _monitoringStreamSubscription?.cancel();
        final characteristic = QualifiedCharacteristic(
            serviceId: Uuid.parse(bleModel.uuidCmd!),
            characteristicId: Uuid.parse(bleModel.uuidRead!),
            deviceId: element["id"]);
        //_monitoringStreamSubscription =
        bleUtils._ble?.subscribeToCharacteristic(characteristic).listen(
          (data) {
            // code to handle incoming data
            debugPrint("deviceId =${element["id"]}---上报来的数据data = $data");
            if (_bleCallBack != null) {
              _bleCallBack!.dataListener(element["id"], data);
            }
          },
          onError: (dynamic error) {
            //_bleDeviceConnector?.disconnect(element["id"]);
            // code to handle errors
            debugPrint("--------BLE蓝牙设备(${element["id"]})接收数据异常：$error");
          },
          cancelOnError: true,
        );
        /*var bleDevice = BleDevice(null, element["id"], element["name"], peripheral);
            bleDevice.isConnected = true;
            _activeBleDevices.add(bleDevice);*/
        storageActiveBleDevices.add(element);
      }, onError: (Object e) {});
      //未完成，待定
      //_activeBleDevices.add(bleDevice);
    }

    setStorageActiveBleDevices(storageActiveBleDevices); //更新活动中的设备列表
  }

  ///根据id查询指定的BLE设备
  Future<BleDevice?> getBleDeviceById(String id) {
    BleDevice? bleDevice;
    final knownDeviceIndex = BleUtils.getInstance()
        .activeBleDevices
        .indexWhere((d) => d.discoveredDevice.id == id);
    if (knownDeviceIndex >= 0) {
      bleDevice = BleUtils.getInstance().activeBleDevices[knownDeviceIndex];
    }
    return Future.value(bleDevice);
  }

  ///根据BLE模块uuid查找指定连接特征值
  Future<BleModel?> getBleModelUuidInfo(BleDevice bleDevice) async {
    BleModel? bleModel;
    int index = 0;
    var uuids = bleDevice.discoveredDevice.serviceUuids;
    var uuid0 = uuids.isNotEmpty ? uuids[0].toString() : "";
    var newUuid = uuidToComplete(uuid0);
    for (BleModel item in bleModels) {
      if (newUuid == uuidToComplete(item.uuidCmd)) {
        bleModel = item;
        break;
      }
    }
    return bleModel;
  }

  ///uuid补全
  String uuidToComplete(String? uuid) {
    uuid = uuid?.toLowerCase();
    if (uuid?.length == 4) {
      uuid = "0000$uuid-0000-1000-8000-00805f9b34fb";
    }
    return uuid ?? "";
  }

  ///根据BLE模块名称查找指定连接特征值
  Future<BleModel?> getBleModelUuidInfoByModelName(String modelName) async {
    BleModel? bleModel;
    for (BleModel item in bleModels) {
      if (item.modelName == modelName) {
        bleModel = item;
        break;
      }
    }
    return bleModel;
  }

  ///存储激活中的设备列表
  Future<bool?> setStorageActiveBleDevices(
      List<StorageActiveBleDevice> storageActiveBleDevices) async {
    return await SharedPreferencesUtils()
        .setStorage("_storageActiveBleDevices", storageActiveBleDevices);
    //return await SpUtil.putStringList("_storageActiveBleDevices", storageActiveBleDevices);
  }

  ///获取激活中的设备列表
  Future<List<StorageActiveBleDevice>> getStorageActiveBleDevices() async {
    List<StorageActiveBleDevice> deviceList = [];
    List<dynamic>? storageList =
        await SharedPreferencesUtils().getStorage("_storageActiveBleDevices");
    storageList = storageList ??= [];
    for (var element in storageList) {
      //JsonUtil.getObj(element, (v) => BleDevice.fromJson(v));
      deviceList.add(
          StorageActiveBleDevice(id: element["id"], name: element["name"]));
    }
    return deviceList;
  }

  ///添加激活中的设备(缓存里添加设备id，用于无扫描恢复连接)
  Future<bool> addActiveBleDevice(BleDevice bleDevice) async {
    List<StorageActiveBleDevice> storageList =
        await getStorageActiveBleDevices();
    storageList.add(StorageActiveBleDevice(
        id: bleDevice.discoveredDevice.id,
        name: DataUtils.emptyStringToReplace(bleDevice.discoveredDevice.name)));
    setStorageActiveBleDevices(storageList);
    _activeBleDevices.add(bleDevice);
    return true;
  }

  ///移除激活中的设备
  Future<bool> removeActiveBleDevice(BleDevice bleDevice) async {
    List<StorageActiveBleDevice> storageList =
        await getStorageActiveBleDevices();
    storageList
        .removeWhere((element) => element.id == bleDevice.discoveredDevice.id);
    setStorageActiveBleDevices(storageList);
    _activeBleDevices.removeWhere((element) =>
        element.discoveredDevice.id == bleDevice.discoveredDevice.id);
    return true;
  }
}
