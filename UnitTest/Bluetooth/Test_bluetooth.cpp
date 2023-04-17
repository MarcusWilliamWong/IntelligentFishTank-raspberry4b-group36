#define DEBUG
#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <memory>
#include <cstring>
#include "bluetooth.h"
#include "config.h"


// Test Class bluthtooth (HC06) function
int main() {
  if (gpioInitialise() < 0) {
    std::cout << "Failed" << std::endl;
  } else {
    std::cout << "PIGPIO is ready" << std::endl;
  }

  Bluetooth bt(app_config::BLUETOOTH_DEV_PATH);
  std::unique_ptr<char[]> data(new char[app_config::CMD_LEN]);
  std::memcpy(data.get(), app_config::CMD_DEFUALT.c_str(), app_config::CMD_LEN);

  // test receive data
  while (false) {
    getchar();
    // each time get data needs initialised
    std::memcpy(data.get(), app_config::CMD_DEFUALT.c_str(), app_config::CMD_LEN);
    int ret = bt.recvData(data.get(), app_config::CMD_LEN);
    std::cout << "received result : " << ret << std::endl;
    for (int i = 0; i < app_config::CMD_LEN; ++i) {
      std::cout << data[i];
    }
    std::cout << std::endl;
  }

  // test sendata
  while (true) {
    getchar();
    bt.sendData(data.get(), app_config::CMD_LEN);
    for (int i = 0; i < app_config::CMD_LEN; ++i) {
      std::cout << data[i];
    }
    std::cout << std::endl;
    // bt.recvData(data.get(), static_cast<int>(initData.size()));
  }
}