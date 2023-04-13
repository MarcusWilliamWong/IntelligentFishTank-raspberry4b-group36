#include <pigpio.h>
#include <iostream>
#include <unistd.h>
#include "heater.h"
#include "config.h"

int main() {
  if (gpioInitialise() < 0) {
    std::cout << "Failed" << std::endl;
  } else {
    std::cout << "PIGPIO is ready" << std::endl;
  }
  // const unsigned int pin = 23u;
  // unsigned int dutycycle = 300;
  // gpioSetMode(pin, PI_ALT5);
  // // gpioSetMode(pin, PI_OUTPUT);
  // gpioSetPWMfrequency(pin, 50);
  // gpioSetPWMrange(pin, 1000); // 20000us = 20ms
  // // std::cout << "dutycycle : " << gpioGetPWMdutycycle(pin);
  // gpioPWM(pin, dutycycle);
  
  Heater heater(23u);
  heater.turnOn();
  // while (true) {
    // std::cout << "gpioGetPWM : " << heater.getPin() << "; dutycycle : " << heater.getDutycycle() << std::endl;
  // };
  // sleep(5);
  // while (true);3
  // gpioTerminate();
}