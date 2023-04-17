#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <thread>
#include "waterpump.h"
#include "config.h"

int main() {
  if (gpioInitialise() < 0) {
    std::cout << "Failed" << std::endl;
  } else {
    std::cout << "PIGPIO is ready" << std::endl;
  }

  std::unique_ptr<char[]> pwmLvl(new char[8]{'0', '1', '2', '3', '4', '5', '2', '0'});
  {
    Waterpump wp(app_config::WATERUMP_PIN);
    for (int i = 0; i < 8; ++i) {
      wp.set(pwmLvl[i]);
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
  }
  

  
  // const unsigned int pin = 26u;
  // unsigned int dutycycle = 500;
  // dutycycle = 0;
  // gpioSetMode(pin, PI_ALT5);
  // // // gpioSetMode(pin, PI_OUTPUT);
  // gpioSetPWMfrequency(pin, 50);
  // gpioSetPWMrange(pin, 1000); // 20000us = 20ms
  // // // std::cout << "dutycycle : " << gpioGetPWMdutycycle(pin);
  // gpioPWM(pin, dutycycle);
  // sleep(5);

  gpioTerminate();
}