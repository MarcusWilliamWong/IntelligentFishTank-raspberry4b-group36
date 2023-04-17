import 'package:flutter_water_tank/utils/ble.device.dart';
import 'package:flutter_water_tank/utils/ble_device_bean.dart';
import 'package:flutter_water_tank/utils/ble_utils.dart';
import 'package:get/get.dart';

class UluckyService extends GetxService {
  static UluckyService get instance => Get.find<UluckyService>();
  DateTime? currentDateTimeMillisecondsSinceEpoch;
  //设备类
  DeviceBean? device;
  //蓝牙设备
  BleDevice? bleDevice;
  getBleDeviceById(id) async {
    bleDevice = (await BleUtils.getInstance().getBleDeviceById(id))!;
  }

  clearBleDevice() {
    bleDevice = null;
  }
}
