#include <pigpio.h>
#include "airpump.h"

Airpump::Airpump(unsigned int pin) : PwmController(pin) {}

Airpump::Airpump(unsigned int pin, unsigned int freq) : PwmController(pin, freq) {}

void Airpump::start() {
  gpioPWM(kPin_, 500);
  gpioSleep(PI_TIME_RELATIVE, 6, 0);
}

void Airpump::stop() {
  gpioPWM(kPin_, 0);
}