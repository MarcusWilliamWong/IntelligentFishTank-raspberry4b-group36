import 'dart:typed_data';

///
/// 数据处理工具类
class DataUtils {
  ///空格转换横杠
  static String emptyStringToReplace(String content) {
    return content.replaceAll(" ", "-");
  }

  ///累加和取低8位
  static int calculateAdd8Bit(List<int> buffer) {
    int cks = 0;
    for (int item in buffer) {
      cks = (cks + item) % 0xffff;
    }
    //int bt = (int)((cks & 0xff00) >> 8);//取校验和高8位
    int bt = (cks & 0xff); //取校验和低8位
    return bt;
  }

  ///
  /// int 转 byte[]
  static int2Bytes(int source, {Type type = Type.WORD}) {
    var s = source.toRadixString(16);
    var pre = '0';
    if (s.length % 2 == 1) {
      s = pre + s;
    }
    List<int> list = [];
    var uint8list = Hex.createUint8ListFromHexString(s);
    switch (type) {
      case Type.BYTE:
        break;
      case Type.WORD:
        if (uint8list.length == 1) {
          list.add(0);
        }
        break;
      case Type.DWORD:
        for (var i = 0; i < 4 - uint8list.length; i++) {
          list.add(0);
        }
        break;
      case Type.STRING:
        break;
    }
    list.addAll(uint8list);
    return list;
  }

  ///
  /// byte[] 转 int
  static bytes2Int(List<int> list) {
    var length = list.length;
    switch (length) {
      case 1:
        return list[0];
      case 2:
        return toInt16(list);
      case 4:
        return toInt32(list);
      default:
        print('传入数据不对');
        break;
    }
  }

  //byte[] to int
  static int toInt16(List<int> list, {int index = 0}) {
    Uint8List byteArray = Uint8List.fromList(list);
    ByteBuffer buffer = byteArray.buffer;
    ByteData data = ByteData.view(buffer);
    int short = data.getInt16(index, Endian.big);
    return short;
  }

  static int toInt32(List<int> list, {int index = 0}) {
    Uint8List byteArray = Uint8List.fromList(list);
    ByteBuffer buffer = byteArray.buffer;
    ByteData data = ByteData.view(buffer);
    int short = data.getInt32(index, Endian.big);
    return short;
  }

  static int toInt64(List<int> list, {int index = 0}) {
    Uint8List byteArray = Uint8List.fromList(list);
    ByteBuffer buffer = byteArray.buffer;
    ByteData data = ByteData.view(buffer);
    int short = data.getInt64(index, Endian.big);
    return short;
  }
}

enum Type {
  BYTE, //1
  WORD, //2
  DWORD, //4
  STRING
}

class Hex {
  /// Creates a `Uint8List` by a hex string.
  static Uint8List createUint8ListFromHexString(String hex) {
    if (hex == null) throw ArgumentError("hex is null");

    var result = Uint8List(hex.length ~/ 2);
    for (var i = 0; i < hex.length; i += 2) {
      var num = hex.substring(i, i + 2);
      var byte = int.parse(num, radix: 16);
      result[i ~/ 2] = byte;
    }

    return result;
  }

  /// Returns a hex string by a `Uint8List`.
  static String formatBytesAsHexString(Uint8List bytes) {
    if (bytes == null) throw ArgumentError("The list is null");

    var result = StringBuffer();
    for (var i = 0; i < bytes.lengthInBytes; i++) {
      var part = bytes[i];
      result.write('${part < 16 ? '0' : ''}${part.toRadixString(16)}');
    }

    return result.toString();
  }
}
