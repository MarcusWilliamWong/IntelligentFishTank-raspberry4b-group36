#include <pigpio.h>
#include "heater.h"


Heater::Heater(unsigned int pin) : PwmController(pin) {}

Heater::Heater(unsigned int pin, unsigned int freq) : PwmController(pin, freq) {}

void Heater::start() {
  gpioPWM(this->kPin_, 500);
  gpioSleep(PI_TIME_RELATIVE, 6, 0);
}

void Heater::stop() {
  gpioPWM(this->kPin_, 0);
}

void hasTemperature(const std::vector<double> &tempers) {
  for (const auto &t : tempers) {
    std::cout << t << " ";
  }
  std::cout << '\n';
}