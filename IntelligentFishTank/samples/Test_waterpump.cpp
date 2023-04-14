#include <pigpio.h>
#include <iostream>
#include <unistd.h>


int main() {
  if (gpioInitialise() < 0) {
    std::cout << "Failed" << std::endl;
  } else {
    std::cout << "PIGPIO is ready" << std::endl;
  }
  
  const unsigned int pin = 26u;
  unsigned int dutycycle = 500;
  dutycycle = 0;
  gpioSetMode(pin, PI_ALT5);
  // // gpioSetMode(pin, PI_OUTPUT);
  gpioSetPWMfrequency(pin, 50);
  gpioSetPWMrange(pin, 1000); // 20000us = 20ms
  // // std::cout << "dutycycle : " << gpioGetPWMdutycycle(pin);
  gpioPWM(pin, dutycycle);
  sleep(5);
  gpioTerminate();
}