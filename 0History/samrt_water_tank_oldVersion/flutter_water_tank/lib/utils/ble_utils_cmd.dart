
import 'package:flutter/cupertino.dart';
import 'package:flutter_water_tank/utils/ble.device.dart';
import 'package:flutter_water_tank/utils/ble_utils.dart';


class CommonBleUtils{

  ///发送蓝牙命令到蓝牙板
  static Future<void> send(BleDevice? bleDevice, int cmd, [List<int>? params, bool isWithout = true]) async {
    if (bleDevice == null) return;
    params ??= [];
    List<int> buffer = [CmdConst.header, cmd];
    buffer.addAll(params);
    //累加和
    int cks = 0;
    for (int item in buffer) {
      cks = (cks + item);
    }
    buffer.add(cks);

    //加密
      debugPrint("${3 % 4}");
    List<int> encryptionBuffer = [];
    int pkLength = CmdConst.publicKey.length;
    for (int i = 0; i < buffer.length; i++) {
      int remainder = i % pkLength; //余数
      int j = remainder == 0 ? 0 : remainder;
      encryptionBuffer.add(buffer[i] ^ CmdConst.publicKey[j]);
    }

    print("写入BLE数据：明文：$buffer，密文：$encryptionBuffer");
    await BleUtils.getInstance().writeCharacteristicWithoutResponse(bleDevice, encryptionBuffer, isWithout);
  }
  ///蓝牙板通知数据 解密
  static decrypt(List<int> params){
    List<int> encryptionBuffer = [];
    int pkLength = CmdConst.publicKey.length;

    for (int i = 0; i < params.length; i++) {
      int remainder = i % pkLength; //余数
      int j = remainder == 0 ? 0 : remainder;
      encryptionBuffer.add(params[i] ^ CmdConst.publicKey[j]);
    }
    debugPrint("蓝牙板通知数据：密文：$params,解密：$encryptionBuffer");

    return encryptionBuffer;
  }
}



///
/// 从0x00到0xFF的含义
/// 对于二进制来说，8位二进制我们称之为一个字节，二进制的表达范围值是从0b00000000～0b11111111，
/// 而我们程序中用十六进制表示的时候就是从0x00到0xFF，这里教大家一个二进制转换十进制和十六进制的方法，
/// 二进制4位一组，遵循8,4,2,1的规律比如 1010，那么从最高位开始算，数字大小是8*1+4*0+2*1+1*0 = 10，
/// 那么十进制就是10，十六进制就是0xA。尤其二进制转十六进制的时候，十六进制一位刚好是和二进制的4位相互对应的，
/// 进制转换：https://tool.lu/hexconvert/
class CmdConst {
  //公钥
  static var publicKey = [0xf6, 0x1e, 0x25, 0x62];

  //前缀
  static var header = 0x35; //协议头

  //功能命令
  static var cmdStandby = 0x60;  //待机模式
  static var cmdFixed = 0x61;  //固定模式
  static var cmdGear = 0x62;  //强度模式
  static var cmdOther = 0x63;  //特控模式(预留扩展)
  static var cmdStatus = 0x71;  //状态查询/上报
  static var cmdMsg = 0x50; 

  //电机
  static var motors = [0x01, 0x02, 0x04]; //电机编号集合
  /*static var motorA = 0x01;  //电机A
  static var motorB = 0x02;  //电机B
  static var motorC = 0x04;  //电机C*/
  static var motorAll = 0x00;  //所有电机
}
