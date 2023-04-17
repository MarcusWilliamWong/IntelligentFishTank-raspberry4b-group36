import 'package:flutter/material.dart';
import 'package:flutter_water_tank/utils/input_widget.dart';
import 'package:get/get.dart';

import 'index.dart';

class HomePage extends GetView<HomeController> {
  const HomePage({Key? key}) : super(key: key);

  // 主视图
  Widget _buildView(HomeController _) {
    return SingleChildScrollView(
      child: Column(
        children: [
          const SizedBox(height: 10),
          Container(
              color: Colors.white,
              padding: const EdgeInsets.all(10),
              child: Column(
                children: [
                  const Align(
                    child: Text('Temperature Control'),
                  ),
                  Container(
                    margin: const EdgeInsets.symmetric(vertical: 10),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: const [
                        Text('Current temperature（℃）：'),
                        Text('55.3℃'),
                      ],
                    ),
                  ),
                  Container(
                    margin: const EdgeInsets.symmetric(vertical: 10),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        const Text('Set temperature（℃）：'),
                        Row(
                          children: [
                            Container(
                              decoration: BoxDecoration(
                                  border: Border.all(
                                      color: const Color(0xffcccccc),
                                      width: 1)),
                              width: 60,
                              height: 24,
                              child: TDLTextField(
                                controller: _.minTemperature,
                                hintText: 'e.g. 23.5',
                                contentPadding:
                                    const EdgeInsets.only(top: 3, left: 3),
                                hintColor: const Color(0xffA6A6A6),
                                inputType: TextInputType.number,
                                inputAction: TextInputAction.done,
                                onEditingComplete: () {
                                  //这里写填入的水平 发送蓝牙指令
                                },
                                isSystem: true,
                              ),
                            ),
                            const Text('一'),
                            Container(
                              decoration: BoxDecoration(
                                  border: Border.all(
                                      color: const Color(0xffcccccc),
                                      width: 1)),
                              width: 60,
                              height: 24,
                              child: TDLTextField(
                                controller: _.maxTemperature,
                                hintText: 'e.g. 23.5',
                                contentPadding:
                                    const EdgeInsets.only(top: 3, left: 3),
                                hintColor: const Color(0xffA6A6A6),
                                inputType: TextInputType.number,
                                inputAction: TextInputAction.done,
                                onEditingComplete: () {
                                  //这里写填入的水平 发送蓝牙指令
                                },
                                isSystem: true,
                              ),
                            ),
                          ],
                        )
                      ],
                    ),
                  ),
                  const SizedBox(height: 10),
                  ElevatedButton(
                    onPressed: _.setTemperature,
                    child: const Text('Confirm'),
                  )
                ],
              )),
          const SizedBox(height: 10),
          Container(
              color: Colors.white,
              padding: const EdgeInsets.all(10),
              child: Column(
                children: [
                  const Align(
                    child: Text('Airpump Control'),
                  ),
                  Container(
                    margin: const EdgeInsets.symmetric(vertical: 10),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: const [
                        Text('Current operating mode'),
                        Text('1 mode'),
                      ],
                    ),
                  ),
                  Container(
                    margin: const EdgeInsets.symmetric(vertical: 10),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        const Text('Set temperature（℃）：'),
                        const SizedBox(width: 40),
                        Expanded(
                          child: Container(
                            decoration: BoxDecoration(
                                border: Border.all(
                                    color: const Color(0xffcccccc), width: 1)),
                            height: 24,
                            child: TDLTextField(
                              controller: _.airpump,
                              hintText: 'e.g. 0,1,2,3,4',
                              contentPadding:
                                  const EdgeInsets.only(top: 3, left: 3),
                              hintColor: const Color(0xffA6A6A6),
                              inputType: TextInputType.number,
                              inputAction: TextInputAction.done,
                              isSystem: true,
                            ),
                          ),
                        )
                      ],
                    ),
                  ),
                  const SizedBox(height: 10),
                  ElevatedButton(
                    onPressed: _.setAirpump,
                    child: const Text('Confirm'),
                  )
                ],
              )),
          const SizedBox(height: 10),
          Container(
              color: Colors.white,
              padding: const EdgeInsets.all(10),
              child: Column(
                children: [
                  const Align(
                    child: Text('Waterpump Control'),
                  ),
                  Container(
                    margin: const EdgeInsets.symmetric(vertical: 10),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: const [
                        Text('Current operating mode'),
                        Text('1 mode'),
                      ],
                    ),
                  ),
                  Container(
                    margin: const EdgeInsets.symmetric(vertical: 10),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        const Text('Set temperature（℃）：'),
                        const SizedBox(width: 40),
                        Expanded(
                          child: Container(
                            decoration: BoxDecoration(
                                border: Border.all(
                                    color: const Color(0xffcccccc), width: 1)),
                            height: 24,
                            child: TDLTextField(
                              controller: _.waterpump,
                              hintText: 'e.g. 0,1,2,3,4',
                              contentPadding:
                                  const EdgeInsets.only(top: 3, left: 3),
                              hintColor: const Color(0xffA6A6A6),
                              inputType: TextInputType.number,
                              inputAction: TextInputAction.done,
                              isSystem: true,
                            ),
                          ),
                        )
                      ],
                    ),
                  ),
                  const SizedBox(height: 10),
                  ElevatedButton(
                    onPressed: _.setWaterpump,
                    child: const Text('Confirm'),
                  )
                ],
              )),
          const SizedBox(
            height: 80,
          )
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return GetBuilder<HomeController>(
      init: HomeController(),
      id: "home",
      builder: (_) {
        return Scaffold(
          backgroundColor: const Color(0xfff4f4fa),
          appBar: AppBar(
            title: const Text("Device Control",
                style: TextStyle(color: Color(0xff212121), fontSize: 14)),
            elevation: 0,
            centerTitle: true,
            backgroundColor: Colors.white,
          ),
          body: SafeArea(
            child: _buildView(_),
          ),
        );
      },
    );
  }
}
