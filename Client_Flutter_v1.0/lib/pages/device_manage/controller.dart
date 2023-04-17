import 'dart:io';
import 'package:bot_toast/bot_toast.dart';
import 'package:flutter/material.dart';
import 'package:flutter_water_tank/pages/ble_scan/index.dart';
import 'package:flutter_water_tank/utils/ble.device.dart';
import 'package:flutter_water_tank/utils/ble_callback.dart';
import 'package:flutter_water_tank/utils/ble_device_bean.dart';
import 'package:flutter_water_tank/utils/ble_service.dart';
import 'package:flutter_water_tank/utils/ble_utils.dart';
import 'package:flutter_water_tank/utils/date.utils.dart';
import 'package:flutter_water_tank/utils/loading.dart';
import 'package:get/get.dart';
import '../../../../utils/common.dart';
import '../home/view.dart';

class DeviceManageController extends GetxController
    with GetTickerProviderStateMixin, WidgetsBindingObserver
    implements BleCallBack {
  late TextEditingController deviceEditingController;

  final isHasCheckedBox = false.obs; //是否有选中的checkbox
  var deviceList = <DeviceBean>[].obs;
  final showType = 0.obs; //0.列表 1.网格
  bool isAllFlag = true;
  @override
  void onInit() {
    super.onInit();
    //App的生命周期监听
    WidgetsBinding.instance.addObserver(this);
    deviceEditingController = TextEditingController();
  }

  @override
  void onReady() async {
    super.onReady();
    //注册蓝牙扫描监听
    BleUtils.getInstance().setCallBack(this);
    //解决：iOS应用运行时在设置中更改权限应用崩溃问题 https://blog.csdn.net/YLGWHYH/article/details/51164238
    if (Platform.isIOS) {
      //未完成，待定
      //await BleUtils.getInstance().disconnectAllUnsafe();
    }
    initDevices();
  }

  @override
  void onClose() {
    super.onClose();
    deviceEditingController.dispose();
    BleUtils.getInstance().stopScan();
    WidgetsBinding.instance.removeObserver(this);
  }

  /*
   * 节点树依赖变化
   * widget树中，若节点的父级结构中的层级 或 父级结构中的任一节点的widget类型有变化，节点会调用didChangeDependencies；若仅仅是父级结构某一节点的widget的某些属性值变化，节点不会调用didChangeDependencies
  */
  /*@override
  void didChangeDependencies() {
    super.didChangeDependencies();
  }*/

  /// 当应用生命周期发生变化时 , 会回调该方法
  /// App的生命周期 参考：http://events.jianshu.io/p/0ba5ce1dbbc5
  @override
  void didChangeAppLifecycleState(AppLifecycleState state) {
    super.didChangeAppLifecycleState(state);
    if (state == AppLifecycleState.paused) {
      //应用进入后台 paused
      debugPrint("应用进入后台paused状态");
      if (Platform.isAndroid) {
        //3个toast插件，只有Fluttertoast能够脱离ui线程执行
        // Fluttertoast.showToast(
        //     msg: "${ApplicationContext.getAppName()} ${"running_in_bg".tr}",
        //     gravity: ToastGravity.BOTTOM,
        //     textColor: ColorAsset.colorWhite,
        //     fontSize: 15.sp,
        //     backgroundColor: ColorAsset.color666);
        //Loading.toast("${ApplicationContext.getAppName()} ${"running_in_bg".tr}");
        //showToast("${ApplicationContext.getAppName()} ${"running_in_bg".tr}", OKToast.ToastPosition.bottom);
      }
    } else if (state == AppLifecycleState.resumed) {
      //应用进入前台 resumed
      debugPrint("应用进入前台resumed状态");
      scanFailListener();
    } else if (state == AppLifecycleState.inactive) {
      // 应用进入非活动状态 , 如来了个电话 , 电话应用进入前台
      // 本应用进入该状态
      //应用进入非活动状态 inactive
      debugPrint("应用进入非活动inactive状态");
    } else if (state == AppLifecycleState.detached) {
      // 应用程序仍然在 Flutter 引擎上运行 , 但是与宿主 View 组件分离
      //应用进入 detached 状态 detached
      debugPrint("应用进入detached状态，应用程序仍然在 Flutter 引擎上运行 , 但是与宿主 View 组件分离");
    }
  }

  ///
  /// 蓝牙扫描监听器
  @override
  void scanListener(List<BleDevice> list) async {
    //1.只能连接之前连接过的
    //2.未连接的
    List<DeviceBean> storageList = await Common.getDevices();
    for (var i = 0; i < list.length; i++) {
      final knownDeviceIndex = BleUtils.getInstance()
          .activeBleDevices
          .indexWhere(
              (d) => d.discoveredDevice.id == list[i].discoveredDevice.id);
      if (knownDeviceIndex >= 0) {
        continue; //已经连接的设备不用显示
      }
      //去缓存中查询是否存在指定设备，用于替换自定义名称
      DeviceBean? device = await Common.findDeviceById(
          id: list[i].discoveredDevice.id, storageList: storageList);
      if (device != null) BleUtils.getInstance().connectBle(list[i]);
    }
  }

  @override
  void scanFailListener() {
    //解决：苹果手机退出后重新进入不会恢复连接问题
    Future<void>.delayed(
      const Duration(milliseconds: 2000),
      () async => BleUtils.getInstance().startScan(),
    );
  }

  @override
  void stopScanListener() {}

  ///连接成功回调
  @override
  void connectListener(BleDevice bleDevice) async {
    String name =
        DataUtils.emptyStringToReplace(bleDevice.discoveredDevice.name);
    //添加设备到本地缓存
    await Common.addDevice(DeviceBean(
      id: bleDevice.discoveredDevice.id,
      localName: name,
      displayName: name,
      isConnected: bleDevice.isConnected,
      enabled: false,
      isChecked: false,
    ));
    await initDevices();
    //主动读取蓝牙板子状态
    // readDeviceStatus(bleDevice);
    DeviceBean? device =
        await Common.findDeviceById(id: bleDevice.discoveredDevice.id);
  }

  //主动读取蓝牙板子状态
  Future<void> readDeviceStatus(BleDevice bleDevice) async {
    //await CommonBleUtils.send(bleDevice, 0xF0, [0xF4]);
  }

  @override
  void connectFailListener(BleDevice bleDevice) async {
    await disconnect(bleDevice);
    //由于连接前会停止扫描，所以连接出现异常后重新开启扫描
    //BleUtils.getInstance().startScan();
    //Loading.dismiss();
  }

  ///蓝牙板返回通知
  @override
  void dataListener(String deviceId, List<int> data) async {
    BleDevice? bleDevice =
        await BleUtils.getInstance().getBleDeviceById(deviceId);
    if (bleDevice == null) return;
  }

  ///初始化设备状态
  Future<void> initDeviceStatus(
      BleDevice bleDevice, bool isLight, bool isPlaying, bool enabled) async {
    final index =
        deviceList.indexWhere((d) => d.id == bleDevice.discoveredDevice.id);
    if (index >= 0) {
      deviceList[index].enabled = enabled;
      deviceList.refresh();
      await Common.setDevices(deviceList); //更新缓存
    }
    update();
  }

  @override
  void deviceFailListener() {}

  @override
  void disconnectListener() {}

  Future<void> initDevices() async {
    deviceList.clear();
    List<DeviceBean> storageList = await Common.getDevices();
    for (DeviceBean item in storageList) {
      item.isConnected = false;
      final knownDeviceIndex = BleUtils.getInstance()
          .activeBleDevices
          .indexWhere((d) => d.discoveredDevice.id == item.id);
      if (knownDeviceIndex >= 0) {
        item.isConnected = true;
      } else {
        item.enabled = false;
      }
    }
    deviceList.addAll(storageList);
    //有数据的情况下才会自动扫描
    update();
    if (storageList.isNotEmpty) {
      BleUtils.getInstance().startScan();
      //解决：苹果手机退出后重新进入不会恢复连接问题
      /*Future<void>.delayed(
        const Duration(milliseconds: 2000),
            () async => BleUtils.getInstance().startScan(),
      );*/
    }
  }

  ///跳转BLE设备扫描页
  void gotoBleScanPage() async {
    var result =
        await Get.to(const UluckyBleScanPage()); //加await后会阻塞，直到页面返回后才会往下执行
    BleUtils.getInstance().setCallBack(this);
    if (result != null) {
      initDevices();
      //主动读取蓝牙板子状态
      // await readDeviceStatus(result);
    }
  }

  ///修改设备名称
  void modifyDeviceName(int index) {
    if (deviceEditingController.text == "") {
      return;
    }
    deviceList[index].displayName = deviceEditingController.text;
    Common.addDevice(deviceList[index], true); //更新缓存
    deviceList.refresh();
  }

  ///移除选中设备
  void removeSelectedDevices(index) async {
    // List<DeviceBean> tempDevices = [];
    // for (var element in deviceList) {
    //   if (!element.isChecked) {
    //     //过滤未选中状态
    //     tempDevices.add(element);
    //   } else {
    //     if (element.isConnected) {
    //       await disconnectBLE(element.id);
    //     }
    //   }
    // }
    // deviceList.clear();
    // if (tempDevices.isEmpty) {
    //   //全部清空了，直接退出管理状态
    //   isManage.value = false;
    // }
    // //refreshDeviceList(tempDevices);
    // deviceList.addAll(tempDevices);
    if (deviceList[index].isConnected) {
      await disconnectBLE(deviceList[index].id);
    }
    deviceList.removeAt(index);
    Common.setDevices(deviceList); //更新缓存
  }

  ///刷新设备列表数据
  /*void refreshDeviceList(data) {
    deviceList.clear();
    deviceList.addAll(data);
    Common.setDevices(deviceList);//更新缓存
    deviceList.refresh();
  }*/

  ///断开逻辑连接
  Future<void> disconnect(BleDevice bleDevice) async {
    //List<DeviceBean> storageList = await Common.getDevices();
    final index =
        deviceList.indexWhere((d) => d.id == bleDevice.discoveredDevice.id);
    if (index >= 0) {
      //断开BLE蓝牙物理连接
      await disconnectBLE(bleDevice.discoveredDevice.id);

      //refreshDeviceList(storageList);
      await Common.setDevices(deviceList); //更新缓存
      deviceList.refresh();
      BotToast.showText(text: "${deviceList[index].displayName}：${"离线".tr}");
      //Loading.toast("设备：${deviceList[index].displayName}断开连接！");
    }
    //有数据的情况下才会自动扫描
    if (deviceList.isNotEmpty) {
      BleUtils.getInstance().startScan();
    }
    //initDevices();
  }

  ///断开BLE物理连接
  Future<void> disconnectBLE(String deviceId) async {
    final knownDeviceIndex = BleUtils.getInstance()
        .activeBleDevices
        .indexWhere((d) => d.discoveredDevice.id == deviceId);
    if (knownDeviceIndex >= 0) {
      //断开BLE蓝牙物理连接
      BleUtils.getInstance().disconnect(
          BleUtils.getInstance().activeBleDevices[knownDeviceIndex]);
    }
  }

  ///跳转设备控制主页面
  void gotoDeviceControlMainPage(DeviceBean device) async {
    debugPrint(device.isConnected.toString());
    if (!device.isConnected) return; //设备未连接
    final knownDeviceIndex = BleUtils.getInstance()
        .activeBleDevices
        .indexWhere((d) => d.discoveredDevice.id == device.id);
    debugPrint(knownDeviceIndex.toString());
    debugPrint(device.id.toString());
    if (knownDeviceIndex < 0) return;
    //定位权限检查并请求
    if (!await BleUtils.getInstance().checkAndRequestPermissions()) return;
    await BleUtils.getInstance().init();
    //检查蓝牙是否开启
    if (!await BleUtils.getInstance().checkBluetoothSwitch()) {
      debugPrint('=======蓝牙未开启===========');
      return;
    }

    //停止扫描
    BleUtils.getInstance().stopScan();
    UluckyService.instance.getBleDeviceById(device.id);

    Get.offAll(const HomePage(), arguments: device);
  }
}
