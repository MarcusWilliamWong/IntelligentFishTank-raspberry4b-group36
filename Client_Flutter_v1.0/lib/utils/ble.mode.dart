///
/// BLE模块蓝牙连接信息
class BleModel {
  int id;
  String? modelName; // 设备名字
  String? uuidDiscover;
  String? uuidCmd;
  String? uuidWrite;
  String? uuidRead;
  String? uuidUpdate;
  String? uuidWriteRead;

  BleModel(
      {required this.id,
      this.modelName,
      this.uuidDiscover,
      this.uuidCmd,
      this.uuidWrite,
      this.uuidRead,
      this.uuidUpdate,
      this.uuidWriteRead});

  factory BleModel.fromMap(Map<String, dynamic> json) => BleModel(
      id: json["id"],
      modelName: json["modelName"],
      uuidDiscover: json["uuidDiscover"],
      uuidCmd: json["uuidCmd"],
      uuidWrite: json["uuidWrite"],
      uuidRead: json["uuidRead"],
      uuidUpdate: json["uuidUpdate"],
      uuidWriteRead: json["uuidWriteRead"]);
  Map<String, dynamic> toMap() => {
        "id": id,
        "modelName": modelName,
        "uuidDiscover": uuidDiscover,
        "uuidCmd": uuidCmd,
        "uuidWrite": uuidWrite,
        "uuidRead": uuidRead,
        "uuidUpdate": uuidUpdate,
        "uuidWriteRead": uuidWriteRead,
      };
}
