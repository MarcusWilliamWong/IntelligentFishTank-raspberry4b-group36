#ifndef CONFIG_H_
#define CONFIG_H_

namespace app_config {
  const unsigned int HEATER_PIN = 26u; // use GPIO 26 to connect heater pwm
  const unsigned int AIRPUMP_PIN = 23u; // use GPIO 23 to connect airpump pwm
  const unsigned int WATERUMP_PIN = 24u; // use GPIO 24 to connect airpump pwm
  const unsigned int LED_PIN = 4u; // use GPIO 4 to connect LED pwm
  // const unsigned int THERMOMETER; // 5, 6, 13, 19
}

#endif