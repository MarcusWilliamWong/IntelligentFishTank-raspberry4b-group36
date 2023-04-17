import 'package:flutter_water_tank/utils/ble.device.dart';

abstract class BleCallBack {
  void scanListener(List<BleDevice> list); //扫描
  void scanFailListener(); //扫描失败
  void connectListener(BleDevice bleDevice); //连接
  void stopScanListener(); // 停止扫描
  void dataListener(String deviceId, List<int> data); //监听数据
  void disconnectListener(); // 断开连接监听
  void connectFailListener(BleDevice bleDevice); //连接失败
  void deviceFailListener(); //连接失败
}
