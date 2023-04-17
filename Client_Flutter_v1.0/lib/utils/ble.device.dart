import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:flutter_water_tank/utils/date.utils.dart';
import 'package:collection/collection.dart';


class BleDevice {
  late DiscoveredDevice discoveredDevice;
  late String deviceName; //设备名称
  late String id; //设备ID
  bool isConnected = false; //是否已连接
  bool isWithout = true; //写入数据是否带响应

  StreamSubscription<ConnectionStateUpdate>? connectionSubscription; //连接状态更新订阅器
  StreamSubscription? monitoringStreamSubscription; //监控设备上报数据

  BleDevice(this.discoveredDevice) {
    var name = DataUtils.emptyStringToReplace(discoveredDevice.name);
    deviceName = name.isEmpty ? "Unknown" : name;
  }

  @override
  int get hashCode => discoveredDevice.id.hashCode;

  @override
  bool operator ==(other) =>
      other is BleDevice &&
      compareAsciiLowerCase(
              discoveredDevice.name, other.discoveredDevice.name) ==
          0 &&
      discoveredDevice.id == other.discoveredDevice.id;

  @override
  String toString() {
    return 'BleDevice{id: ${discoveredDevice.id}, deviceName: ${DataUtils.emptyStringToReplace(discoveredDevice.name)}}';
  }
}
