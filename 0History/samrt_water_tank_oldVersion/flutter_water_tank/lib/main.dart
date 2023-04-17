import 'package:bot_toast/bot_toast.dart';
import 'package:flutter/material.dart';
import 'package:flutter_water_tank/pages/device_manage/index.dart';
import 'package:flutter_water_tank/utils/ble_service.dart';
import 'package:flutter_water_tank/utils/instance.dart';
import 'package:get/get.dart';

void main() {
  Get.put<UluckyService>(UluckyService());
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    final botToastBuilder = BotToastInit();
    return GetMaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        // This is the theme of your application.
        //
        // Try running your application with "flutter run". You'll see the
        // application has a blue toolbar. Then, without quitting the app, try
        // changing the primarySwatch below to Colors.green and then invoke
        // "hot reload" (press "r" in the console where you ran "flutter run",
        // or simply save your changes to "hot reload" in a Flutter IDE).
        // Notice that the counter didn't reset back to zero; the application
        // is not restarted.
        primarySwatch: Colors.blue,
      ),

      navigatorObservers: [BotToastNavigatorObserver()], //2.注册路由观察者

      navigatorKey: Instances.navigatorKey,

      //     builder: (context, child) {
      //  EasyLoading.init();  //do something
      //   child = botToastBuilder(context,child);
      //   return child;
      // },
      builder: (context, child) {
        child = GestureDetector(
          onTap: () {
            FocusScopeNode currentFocus = FocusScope.of(context);
            if (!currentFocus.hasPrimaryFocus &&
                currentFocus.focusedChild != null) {
              FocusManager.instance.primaryFocus!.unfocus();
            }
          },
          child: MediaQuery(
            //设置文字大小不随系统设置改变
            data: MediaQuery.of(context).copyWith(textScaleFactor: 1.0),
            child: botToastBuilder(context, child),
          ),
        );

        return child;
      },
      home: const DeviceManagePage(),
    );
  }
}
