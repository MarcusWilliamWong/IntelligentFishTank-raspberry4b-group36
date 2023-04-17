class DeviceBean {
  String id;
  String localName;
  String displayName;
  bool isConnected;
  bool enabled; //电源
  bool isChecked;
  DeviceBean({
    required this.id,
    required this.localName,
    required this.displayName,
    this.isConnected = false,
    this.enabled = false,
    this.isChecked = false,
  });

  factory DeviceBean.fromJson(Map<String, dynamic> json) => DeviceBean(
        id: json["id"],
        localName: json["localName"],
        displayName: json["displayName"],
        isConnected: json["isConnected"],
        enabled: json["enabled"],
        isChecked: json["isChecked"],
      );

  Map<String, dynamic> toJson() => {
        "id": id,
        "localName": localName,
        "displayName": displayName,
        "isConnected": isConnected,
        "enabled": enabled,
        "isChecked": isChecked,
      };
}
