import 'dart:convert';

import 'package:bot_toast/bot_toast.dart';
import 'package:flutter/material.dart';
import 'package:flutter_water_tank/utils/ble.device.dart';
import 'package:flutter_water_tank/utils/ble_callback.dart';
import 'package:flutter_water_tank/utils/ble_device_bean.dart';
import 'package:flutter_water_tank/utils/ble_service.dart';
import 'package:flutter_water_tank/utils/ble_utils_cmd.dart';
import 'package:get/get.dart';

class HomeController extends GetxController implements BleCallBack {
  HomeController();
  TextEditingController airpump = TextEditingController();
  TextEditingController waterpump = TextEditingController();
  TextEditingController minTemperature = TextEditingController();
  TextEditingController maxTemperature = TextEditingController();
  //设备类
  late DeviceBean device;
  //蓝牙设备
  late BleDevice bleDevice;
  var temperature = 23.obs;
  var airOperatingModel = 0.obs;
  var waterOperatingModel = 0.obs;

  _initData() {
    if (UluckyService.instance.bleDevice != null) {
      bleDevice = UluckyService.instance.bleDevice!;
      debugPrint('-=--------------------------------');
      debugPrint(bleDevice.deviceName.toString());
      debugPrint('-=--------------------------------');
    }

    update(["home"]);
  }

  @override
  void onInit() {
    _initData();
    //比如说查询温度 你一进来就可以先发送查询指令 例如
    // CommonBleUtils.send(bleDevice, 0x60, [6, 0], false);
    //这个bledevice 就是这个连接的设备 后面 就是指令头 具体的指令 最后的false固定不用管就行
    super.onInit();
  }

  setTemperature() {
    num? min = num.tryParse(minTemperature.text);
    num? max = num.tryParse(maxTemperature.text);
    if (min == null || max == null) {
      BotToast.showText(text: '格式输入错误');
      return;
    } else {
      temperature(max.toInt());
      if (min > 50 || max > 50) {
        BotToast.showText(text: '最大温度50℃');
        return;
      }
      if (min >= max) {
        BotToast.showText(
          text: '温度设置错误',
        );
        return;
      }
      CommonBleUtils.send(
          bleDevice, 0x01, padWithZeros([max.toInt(), min.toInt()]), false);
      // 发送指令
      //保留一位小数
      // max.toStringAsFixed(1);
      // min.toStringAsFixed(1);
    }
  }

  setAirpump() {
    num? air = num.tryParse(airpump.text);
    if (air == null) {
      BotToast.showText(text: '格式输入错误');
      return;
    } else {
      if (air < 0 || air > 4) {
        BotToast.showText(
          text: '档位设置错误',
        );
        return;
      }
    }
    airOperatingModel(air.toInt());
    debugPrint('================================');
    CommonBleUtils.send(bleDevice, 0x02, padWithZeros([air.toInt()]), false);

    debugPrint('================================');
  }

  setWaterpump() {
    num? water = num.tryParse(waterpump.text);
    if (water == null) {
      BotToast.showText(text: '格式输入错误');
      return;
    } else {
      waterOperatingModel(water.toInt());
      if (water < 0 || water > 4) {
        BotToast.showText(
          text: '档位设置错误',
        );
        return;
      }
    }

    CommonBleUtils.send(bleDevice, 0x03, padWithZeros([water.toInt()]), false);
  }

  List<int> padWithZeros(List<int> inputList) {
    if (inputList.length >= 7) {
      return inputList;
    }

    while (inputList.length < 7) {
      inputList.add(0);
    }
    debugPrint('------------++---------');
    debugPrint(inputList.toString());
    debugPrint('-------------++----------');
    return inputList;
  }

  @override
  void connectFailListener(BleDevice bleDevice) {}

  @override
  void connectListener(BleDevice bleDevice) {}

  @override
  void dataListener(String deviceId, List<int> data) {
    debugPrint('=======$data=========================');
    //这里接收蓝牙版的广播  比如你发送一条查询指令 在这里可以拿到data
  }

  @override
  void deviceFailListener() {}

  @override
  void disconnectListener() {}

  @override
  void scanFailListener() {}

  @override
  void scanListener(List<BleDevice> list) {}

  @override
  void stopScanListener() {}
}
