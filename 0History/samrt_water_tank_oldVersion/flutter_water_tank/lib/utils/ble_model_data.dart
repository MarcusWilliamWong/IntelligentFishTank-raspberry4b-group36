import 'package:flutter_water_tank/utils/ble.mode.dart';

///
/// App平台已注册蓝牙模块数据列表
List<BleModel> bleModels = [
  BleModel(
    id: 5,
    modelName: 'DSJM',
    uuidDiscover: "fffe",
    uuidCmd: "fffe",
    uuidWrite: "fe02",
    uuidRead: "fe01",
  ),
  BleModel(
    id: 6,
    modelName: 'CX2-FJB-2127',
    uuidDiscover: "ff60",
    uuidCmd: "ff60",
    uuidWrite: "ff61",
    uuidRead: "ff62",
  ),
];
