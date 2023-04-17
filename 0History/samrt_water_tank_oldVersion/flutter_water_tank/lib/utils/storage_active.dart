
///
/// 持久化的激活中的BLE设备
class StorageActiveBleDevice {
  late final String id;
  late final String name;

  StorageActiveBleDevice({required this.id, required this.name });

  factory StorageActiveBleDevice.fromJson(Map<String, dynamic> json) => StorageActiveBleDevice(
    id: json["id"],
    name: json["name"],
  );

  Map<String, dynamic> toJson() => {
    "id": id,
    "name": name,
  };
}