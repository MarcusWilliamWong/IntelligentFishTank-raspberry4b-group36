import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:lottie/lottie.dart';

import 'index.dart';

class UluckyBleScanPage extends StatelessWidget {
  const UluckyBleScanPage({Key? key}) : super(key: key);

  // 主视图
  Widget _buildView(BleScanController _) {
    return SingleChildScrollView(
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Container(
            alignment: Alignment.center,
            child: const Text(
              '正在搜索附近的设备，请确保设备处于匹配状态',
              style: TextStyle(color: Color(0xff424242), fontSize: 14),
            ),
          ),
          Container(
              alignment: Alignment.topCenter,
              margin: const EdgeInsets.only(top: 20),
              child: Obx(
                () => SizedBox(
                  width: 175,
                  height: 175,
                  child: Lottie.asset(
                      'assets/lottie/common/ble_scan_lottie.json',
                      width: 175,
                      height: 175,
                      animate: _.isScan.value ? true : false,
                      fit: BoxFit.fill),
                ),
              )),
          Obx(() => Container(
                margin: const EdgeInsets.only(left: 37, top: 20),
                child: Text.rich(TextSpan(
                    text: "${'发现设备'}：",
                    children: [
                      TextSpan(
                          text: _.deviceList.length.toString(),
                          style: const TextStyle(color: Colors.red))
                    ],
                    style: const TextStyle(color: Color(0xff212121)))),
              )),
          Obx(() => Container(
                margin: const EdgeInsets.symmetric(horizontal: 40)
                    .copyWith(top: 10),
                constraints:
                    const BoxConstraints(maxHeight: 250, minHeight: 150),
                child: SingleChildScrollView(
                  child: Column(children: _renderItme(_)),
                ),
              )),
          const SizedBox(
            height: 20,
          ),
          Align(
            alignment: Alignment.center,
            child: Ink(
              width: 195,
              decoration: const BoxDecoration(
                borderRadius: BorderRadius.all(Radius.circular(50)),
                gradient: LinearGradient(
                  begin: Alignment.topLeft,
                  end: Alignment.bottomRight,
                  colors: [
                    Color(0xff7682CF), //背景渐变
                    Color(0xffA0ABF2),
                  ],
                ),
              ),
              child: Obx(() => InkWell(
                    borderRadius: const BorderRadius.all(Radius.circular(8.0)),
                    onTap: () => _.scanToggle(),
                    child: SizedBox(
                      height: 56,
                      child: Center(
                        child: Text(
                          _.isScan.value ? '停止扫描' : '重新扫描',
                          style: const TextStyle(
                              color: Colors.white, fontSize: 18),
                        ),
                      ),
                    ),
                  )),
            ),
          ),
          const SizedBox(
            height: 20,
          ),
        ],
      ),
    );
  }

  List<Widget> _renderItme(BleScanController _) {
    List<Widget> itme = [];
    for (var i = 0; i < _.deviceList.length; i++) {
      itme.add(Container(
        height: 60,
        padding: const EdgeInsets.symmetric(horizontal: 15),
        margin: const EdgeInsets.only(bottom: 10),
        decoration: const BoxDecoration(
            color: Colors.white,
            borderRadius: BorderRadius.all(Radius.circular(14))),
        child: Row(
          children: [
            const Icon(Icons.device_hub_sharp),
            Expanded(
                child: Padding(
              padding: EdgeInsets.only(left: 10),
              child: Text(
                _.deviceList[i].localName,
                style: const TextStyle(color: Color(0xff333333), fontSize: 14),
              ),
            )),
            InkWell(
              onTap: () {
                _.connectBle(i);
              },
              child: Container(
                padding:
                    const EdgeInsets.symmetric(vertical: 7, horizontal: 17),
                decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(25),
                    color: const Color(0xff8690C7)),
                child: const Text(
                  '连接',
                  style:  TextStyle(color: Colors.white, fontSize: 14),
                ),
              ),
            )
          ],
        ),
      ));
    }
    return itme;
  }

  @override
  Widget build(BuildContext context) {
    return GetBuilder<BleScanController>(
      init: BleScanController(),
      id: "ble_scan",
      builder: (_) {
        return Container(
          decoration: const BoxDecoration(color: Color(0xfff4f4fa)),
          child: Scaffold(
            backgroundColor: Colors.transparent,
            appBar: AppBar(
              title: const Text(
                '搜索设备',
                style: TextStyle(color: Color(0xff212121), fontSize: 18),
              ),
              backgroundColor: Colors.transparent,
              elevation: 0,
              centerTitle: true,
              leading: IconButton(
                onPressed: () {
                  Get.back(result: true);
                },
                icon: const Icon(
                  Icons.keyboard_arrow_left,
                  color: Color(0xff212121),
                  size: 35,
                ),
              ),
            ),
            body: SafeArea(
              child: _buildView(_),
            ),
          ),
        );
      },
    );
  }
}

class FloatingButtonCustomLocation extends FloatingActionButtonLocation {
  FloatingActionButtonLocation location;
  final double offsetX;
  final double offsetY;
  FloatingButtonCustomLocation(this.location,
      {this.offsetX = 0, this.offsetY = 0});

  @override
  Offset getOffset(ScaffoldPrelayoutGeometry scaffoldGeometry) {
    Offset offset = location.getOffset(scaffoldGeometry);
    return Offset(offset.dx + offsetX, offset.dy + offsetY);
  }
}
