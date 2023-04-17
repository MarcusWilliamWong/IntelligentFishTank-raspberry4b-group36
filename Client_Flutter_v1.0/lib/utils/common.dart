import 'package:flutter/material.dart';
import 'package:flutter_water_tank/utils/ble_device_bean.dart';
import 'package:flutter_water_tank/utils/shared_perferenc.dart';

class Common {
  static void goPage(BuildContext context, Widget page, [Object? arguments]) {
    Navigator.push(
        context,
        MaterialPageRoute(
          builder: (_) => page,
          settings: RouteSettings(
            arguments: arguments,
          ),
        ));
  }

  static Future<bool> removeStorage(String key) async {
    return await SharedPreferencesUtils().removeStorage(key);
  }

  static Future<void> setDevices(List<DeviceBean> devices) async {
    return await SharedPreferencesUtils().setStorage("_deviceList", devices);
  }

  static Future<List<DeviceBean>> getDevices() async {
    List<DeviceBean> deviceList = [];
    List<dynamic>? storageList =
        await SharedPreferencesUtils().getStorage("_deviceList");
    storageList = storageList ?? [];
    for (var element in storageList) {
      deviceList.add(DeviceBean(
        id: element["id"],
        localName: element["localName"],
        displayName: element["displayName"],
        isConnected: element["isConnected"],
        enabled: element["enabled"],
        isChecked: element["isChecked"],
      ));
    }
    return deviceList;
  }

  ///添加设备（isCover=false: 没有就添加，有就啥也不干; isCover=true: 没有就添加，有就替换;）
  static Future<bool> addDevice(DeviceBean device,
      [bool isCover = false]) async {
    bool isFind = false;
    List<DeviceBean> storageList = await getDevices();
    for (DeviceBean item in storageList) {
      if (item.id == device.id) {
        isFind = true;
        break;
      }
    }
    if (isFind && !isCover) return false; //存在/不替换，直接返回
    List<DeviceBean> deviceList = [];
    if (!isFind) deviceList.add(device); //不存在，添加设备
    for (var element in storageList) {
      if (isCover && element.id == device.id) {
        //替换
        deviceList.add(device);
      } else {
        deviceList.add(element);
      }
    }
    setDevices(deviceList);
    return true;
  }

  ///根据id查询缓存是否存在指定设备
  static Future<DeviceBean?> findDeviceById(
      {required String id, List<DeviceBean>? storageList}) async {
    DeviceBean? result;
    storageList ??= await getDevices();
    for (DeviceBean item in storageList) {
      if (item.id == id) {
        result = item;
        break;
      }
    }
    return result;
  }

  ///存储模式列表
  static Future<void> setModes(List<dynamic> modes, int soundType) async {
    return await SharedPreferencesUtils()
        .setStorage("_modes_$soundType", modes);
  }

  ///获取模式列表
  static Future<List<dynamic>> getModes(int soundType) async {
    List<dynamic>? storageList =
        await SharedPreferencesUtils().getStorage("_modes_$soundType");
    storageList = storageList ?? [];
    return storageList;
  }

  ///添加模式
  static Future<bool> addMode(dynamic mode, int soundType) async {
    List<dynamic> storageList = await getModes(soundType);
    storageList.add(mode);
    setModes(storageList, soundType);
    return true;
  }

  static Future<void> setDeviceDelayCloseValue(
      deviceId, delayCloseValue) async {
    return await SharedPreferencesUtils()
        .setStorage("deviceDelayClose_" + deviceId, delayCloseValue);
  }

  static Future<int> getDeviceDelayCloseValue(deviceId) async {
    dynamic temp = await SharedPreferencesUtils()
        .getStorage("deviceDelayClose_" + deviceId);
    return temp ?? 0;
  }

  static Future<void> setDeviceBrightnessValue(deviceId, value) async {
    return await SharedPreferencesUtils()
        .setStorage("deviceBrightness_" + deviceId, value);
  }

  static Future<double> getDeviceBrightnessValue(deviceId) async {
    dynamic temp = await SharedPreferencesUtils()
        .getStorage("deviceBrightness_" + deviceId);
    return temp ?? 0.0;
  }

  static Future<void> setDeviceVolumeValue(deviceId, value) async {
    return await SharedPreferencesUtils()
        .setStorage("deviceVolume_" + deviceId, value);
  }

  static Future<double> getDeviceVolumeValue(deviceId) async {
    dynamic temp =
        await SharedPreferencesUtils().getStorage("deviceVolume_" + deviceId);
    return temp ?? 0.0;
  }
}
