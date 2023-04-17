import 'package:bot_toast/bot_toast.dart';
import 'package:flutter_water_tank/utils/ble.device.dart';
import 'package:flutter_water_tank/utils/ble_callback.dart';
import 'package:flutter_water_tank/utils/ble_device_bean.dart';
import 'package:flutter_water_tank/utils/ble_utils.dart';
import 'package:flutter_water_tank/utils/common.dart';
import 'package:flutter_water_tank/utils/date.utils.dart';
import 'package:flutter_water_tank/utils/loading.dart';
import 'package:get/get.dart';

class BleScanController extends GetxController implements BleCallBack {
  BleScanController();
  var isScan = true.obs;
  var deviceList = <DeviceBean>[].obs;
  var bleDeviceList = <BleDevice>[];

  void onTap() {}

  // @override
  // void onInit() {
  //   super.onInit();
  // }

  @override
  void onReady() {
    super.onReady();
    //注册蓝牙扫描监听
    BleUtils.getInstance().setCallBack(this);
    //开始扫描
    BleUtils.getInstance().startScan();
  }

  void scanToggle() {
    isScan.toggle();
    if (!isScan.value) {
      deviceList.clear();
      BleUtils.getInstance().stopScan();
    } else {
      BleUtils.getInstance().startScan();
    }
  }

  ///连接BLE设备
  void connectBle(index) async {
    final knownDeviceIndex = BleUtils.getInstance().activeBleDevices.indexWhere(
        (d) =>
            d.discoveredDevice.id == bleDeviceList[index].discoveredDevice.id);
    if (knownDeviceIndex >= 0 && bleDeviceList[index].isConnected) {
      //Loading.dismiss();
      BotToast.showText(text: "当前设备已连接".tr);
    } else {
      //连接设备
      BotToast.showLoading();
      BleUtils.getInstance().connectBle(bleDeviceList[index]);
    }
  }

  @override
  void connectFailListener(BleDevice bleDevice) {
    // Loading.toast('连接超时');
    BotToast.cleanAll();
  }

  @override
  void connectListener(BleDevice bleDevice) {
    BotToast.showText(text: "连接设备成功".tr);
    String name =
        DataUtils.emptyStringToReplace(bleDevice.discoveredDevice.name);
    //添加设备到本地缓存
    Common.addDevice(DeviceBean(
      id: bleDevice.discoveredDevice.id,
      localName: name,
      displayName: name,
      isConnected: bleDevice.isConnected,
      enabled: false,
      isChecked: false,
    ));
    BotToast.cleanAll();
    Get.back(result: bleDevice);
  }

  @override
  void dataListener(String deviceId, List<int> data) {}

  @override
  void deviceFailListener() {
    // TODO: implement deviceFailListener
  }

  @override
  void disconnectListener() {
    // TODO: implement disconnectListener
  }

  @override
  void scanFailListener() {
    Future<void>.delayed(
      const Duration(milliseconds: 2000),
      () async => BleUtils.getInstance().startScan(),
    );
  }

  @override
  void scanListener(List<BleDevice> list) async {
    deviceList.clear();
    bleDeviceList.clear();
    print('================scanListener==========================');
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
      bleDeviceList.add(list[i]);
      String name =
          DataUtils.emptyStringToReplace(list[i].discoveredDevice.name);
      deviceList.add(DeviceBean(
        id: list[i].discoveredDevice.id,
        localName: name,
        displayName: device == null ? name : device.displayName,
        isConnected: list[i].isConnected,
        enabled: false,
        isChecked: false,
      ));
    }
  }

  @override
  void stopScanListener() {
    // TODO: implement stopScanListener
  }
}
