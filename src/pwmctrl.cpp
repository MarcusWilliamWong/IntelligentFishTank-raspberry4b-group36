#include "pwmctrl.h"
#include <pigpio.h>
#include <iostream>

PwmController::PwmController(unsigned int pin) : PwmController(pin, 50u) {}

PwmController::PwmController(unsigned int pin, unsigned int freq) : kPin_(pin), freq_(freq) {
  // initiation, set pin, freq and range(precision)
  gpioSetMode(this->kPin_, PI_OUTPUT);
  gpioSetPWMfrequency(this->kPin_, this->freq_);
  gpioSetPWMrange(this->kPin_, this->kRange_);
}

void PwmController::setDutycycle(unsigned int dutycycle) {
	this->dutycycle_ = dutycycle;
}