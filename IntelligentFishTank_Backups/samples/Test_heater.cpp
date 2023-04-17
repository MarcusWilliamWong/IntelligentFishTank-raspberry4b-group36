#include <pigpio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "heater.h"
#include "config.h"

int main() {
  if (gpioInitialise() < 0) {
    std::cout << "Failed" << std::endl;
  } else {
    std::cout << "PIGPIO is ready" << std::endl;
  }

  std::unique_ptr<char[]> pwmLvl(new char[8]{'0', '1', '2', '3', '4', '5', '2', '0'});
  {
    Heater heater(app_config::HEATER_PIN);
    for (int i = 0; i < 8; ++i) {
      heater.set(pwmLvl[i]);
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
  }

  #ifdef DEBUG_OUTDATE
  const unsigned int pin = 24u;
  unsigned int dutycycle = 500;
  dutycycle = 0;
  gpioSetMode(pin, PI_ALT5);
  // // gpioSetMode(pin, PI_OUTPUT);
  gpioSetPWMfrequency(pin, 50);
  gpioSetPWMrange(pin, 1000); // 20000us = 20ms
  // // std::cout << "dutycycle : " << gpioGetPWMdutycycle(pin);

  for (int i = 0; i < 4; ++i) {
    gpioPWM(pin, i * 200);
    sleep(3);
  }
  gpioPWM(pin, 0);
  
  // Heater heater(23u);
  // heater.turnOn();
  // for (int i = 0; i < 6; ++i ) {
	// 	heater.setPwmLevel(static_cast<unsigned int>(i));
  //   heater.turnOn();
	// 	sleep(3);
	// }

  // while (true) {
    // std::cout << "gpioGetPWM : " << heater.getPin() << "; dutycycle : " << heater.getDutycycle() << std::endl;
  // };
  // sleep(5);
  // while (true);3
  #endif
  gpioTerminate();
}