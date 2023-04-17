import 'package:flutter/material.dart';
import 'package:flutter_slidable/flutter_slidable.dart';
import 'package:flutter_water_tank/pages/ble_scan/view.dart';
import 'package:flutter_water_tank/utils/instance.dart';
import 'package:get/get.dart';
import 'index.dart';

late DeviceManageController logic;

/// 设备管理页
class DeviceManagePage extends StatelessWidget {
  const DeviceManagePage({Key? key}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    logic = Get.put(DeviceManageController());

    return Scaffold(
      resizeToAvoidBottomInset: false, //输入框抵住键盘，防止键盘弹出导致超出屏幕
      backgroundColor: Colors.transparent,
      floatingActionButtonLocation: FloatingButtonCustomLocation(
          FloatingActionButtonLocation.centerFloat,
          offsetY: -30),
      floatingActionButton: InkWell(
        onTap: logic.gotoBleScanPage,
        child: Container(
          width: 55,
          height: 55,
          decoration: const BoxDecoration(
              borderRadius: BorderRadius.all(Radius.circular(55)),
              color: Color(0xff8690C7)),
          child: const Icon(
            Icons.add,
            color: Colors.white,
          ),
        ),
      ),
      // appBar: _appBar(),
      // bottomNavigationBar: _bottomAppBar(),
      // body: _content()
      body: Container(
        color: const Color(0xfff4f4fa),
        child: Column(
          children: [
            Container(
              alignment: Alignment.bottomCenter,
              height: kToolbarHeight + currentContext.mediaQueryPadding.top,
              decoration: const BoxDecoration(
                borderRadius: BorderRadius.only(
                    bottomLeft: Radius.circular(30),
                    bottomRight: Radius.circular(30)),
                gradient: LinearGradient(
                  begin: Alignment.centerLeft,
                  end: Alignment.centerRight,
                  colors: [
                    Color(0xFF8690c7), //背景渐变
                    Color(0xFFf5afa3),
                  ],
                ),
              ),
              child: AppBar(
                backgroundColor: Colors.transparent,
                elevation: 0,
                centerTitle: true,
                title: const Text(
                  '设备管理',
                  style: TextStyle(color: Colors.white, fontSize: 18),
                ),
              ),
            ),
            Expanded(child: _content())
          ],
        ),
      ),
    );
  }

  Widget _content() {
    return Obx(() => SizedBox(
          child: logic.deviceList.isNotEmpty ? _listShowView() : _notDecive,
        ));
  }

  Widget get _notDecive => Container(
        color: const Color(0xfff4f4fa),
        alignment: Alignment.center,
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: const [
            Padding(
              padding: EdgeInsets.only(top: 6, bottom: 14),
              child: Text(
                "没有设备",
                style: TextStyle(
                  fontSize: 12,
                  color: Color(0xff424242),
                ),
              ),
            ),
            Text(
              """添加你的智能水箱
柔情的呵护，贴心的温暖""",
              style: TextStyle(
                fontSize: 14,
                color: Color(0xff808080),
              ),
            ),
          ],
        ),
      );
  void doNothing() {}

  Widget _listShowView() {
    return ListView.builder(
      shrinkWrap: true, //解决ListView/GridView作为Column的子Widget时候，会一片空白、不显示
      scrollDirection: Axis.vertical,
      itemCount: logic.deviceList.length,
      itemBuilder: (BuildContext context, int index) {
        return Container(
          margin: const EdgeInsets.symmetric(horizontal: 15, vertical: 10),
          decoration: const BoxDecoration(
              color: Color(0xff8690c7),
              borderRadius: BorderRadius.all(Radius.circular(14))),
          child: Slidable(
              key: ValueKey(index),
              endActionPane: ActionPane(
                motion: const ScrollMotion(),
                children: [
                  CustomSlidableAction(
                    autoClose: false,
                    onPressed: (context) {
                      _editDeviceNameDialog(index, context);
                    },
                    padding: const EdgeInsets.all(0),
                    foregroundColor: Colors.white,
                    backgroundColor: const Color(0xff8690c7),
                    child: const Text(
                      '编辑',
                      style: TextStyle(fontSize: 14),
                    ),
                  ),
                  CustomSlidableAction(
                    autoClose: false,
                    onPressed: (context) => _lockDeviceDialog(index, context),
                    foregroundColor: Colors.white,
                    padding: const EdgeInsets.all(0),
                    backgroundColor: const Color(0xfff5afa3),
                    child: const Text(
                      '锁定',
                      style: TextStyle(fontSize: 14),
                    ),
                  ),
                  CustomSlidableAction(
                    autoClose: false,
                    onPressed: (context) {
                      _deleteDeviceDialog(index, context);
                    },
                    padding: const EdgeInsets.all(0),
                    backgroundColor: const Color(0xffff654a),
                    borderRadius: const BorderRadius.only(
                        bottomRight: Radius.circular(14),
                        topRight: Radius.circular(14)),
                    child: const Text(
                      '删除',
                      style: TextStyle(fontSize: 14),
                    ),
                  ),
                ],
              ),
              child: InkWell(
                onTap: () {
                  logic.gotoDeviceControlMainPage(logic.deviceList[index]);
                },
                child: Container(
                  height: 60,
                  padding: const EdgeInsets.symmetric(horizontal: 22),
                  decoration: const BoxDecoration(
                    color: Color(0xffffffff),
                    boxShadow: [
                      BoxShadow(
                        color: Color(0xff8B96DB),
                        blurRadius: 1,
                        spreadRadius: .1,
                        offset: Offset(0, .5),
                      ),
                    ],
                    borderRadius: BorderRadius.all(Radius.circular(14)),
                  ),
                  child: Row(
                    crossAxisAlignment: CrossAxisAlignment.center,
                    mainAxisAlignment: MainAxisAlignment.spaceBetween, //一左一右
                    children: [
                      const SizedBox(
                        width: 50,
                        child: Icon(
                          Icons.device_hub_rounded,
                          size: 24,
                        ),
                      ),
                      const SizedBox(width: 9),
                      Expanded(
                        flex: 3,
                        child: Row(
                          crossAxisAlignment: CrossAxisAlignment.center,
                          children: [
                            Expanded(
                              child: Container(
                                padding: const EdgeInsets.only(left: 10),
                                alignment: Alignment.centerLeft,
                                child: Text(logic.deviceList[index].displayName,
                                    maxLines: 1,
                                    overflow: TextOverflow.ellipsis,
                                    style: const TextStyle(
                                        fontSize: 16,
                                        color: Color(0xff212121))),
                              ),
                            ),
                          ],
                        ),
                      ),
                      Obx(() => Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              Row(
                                children: [
                                  Obx(() => Container(
                                        width: 5,
                                        height: 5,
                                        decoration: BoxDecoration(
                                            borderRadius:
                                                BorderRadius.circular(10),
                                            color: logic.deviceList[index]
                                                    .isConnected
                                                ? const Color(0xff8690C7)
                                                : const Color(0xffcccccc)),
                                      )),
                                  Container(
                                    padding: const EdgeInsets.only(left: 5),
                                    alignment: Alignment.centerLeft,
                                    child: Text(
                                        logic.deviceList[index].isConnected
                                            ? "在线"
                                            : "离线",
                                        maxLines: 1,
                                        overflow: TextOverflow.ellipsis,
                                        style: TextStyle(
                                          fontSize: 13,
                                          color: logic
                                                  .deviceList[index].isConnected
                                              ? const Color(0xff8690C7)
                                              : const Color(0xff808080),
                                        )),
                                  ),
                                ],
                              ),
                            ],
                          ))
                    ],
                  ),
                ),
              )),
        );
      },
    );
  }

  ///编辑设备名称对话框
  _editDeviceNameDialog(int index, BuildContext context) {}

  ///是否锁定设备
  _lockDeviceDialog(int index, BuildContext context) {}

  ///是否删除设备
  _deleteDeviceDialog(int index, BuildContext context) {
    logic.removeSelectedDevices(index);
  }
}
