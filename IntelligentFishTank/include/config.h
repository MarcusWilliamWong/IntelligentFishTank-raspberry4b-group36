#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <memory>

// config some pins and device file path
namespace app_config {
  // pin
  const unsigned int HEATER_PIN{26u}; // use GPIO 26 to connect heater pwm
  const unsigned int AIRPUMP_PIN{23u}; // use GPIO 23 to connect airpump pwm
  const unsigned int WATERPUMP_PIN{24u}; // use GPIO 24 to connect airpump pwm
  const unsigned int LED_PIN{4u}; // use GPIO 4 to connect LED pwm
  // const unsigned int THERMOMETER; // 5, 6, 13, 19

  // file path
  const std::string BLUETOOTH_DEV_PATH{"/dev/ttyS0"};
  const std::string THERMOMETER_DEV_PATH{"/sys/bus/w1/devices"};

  // cmd
  const std::string CMD_DEFUALT{"*********"};
  const unsigned int CMD_LEN{CMD_DEFUALT.size()};
}

#endif