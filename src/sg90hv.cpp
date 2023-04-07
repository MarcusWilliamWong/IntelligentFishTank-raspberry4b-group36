#include "sg90hv.h"

Motor::Motor() : Motor(12u, 50u) {}

Motor::Motor(unsigned int pin) : Motor(pin, 50u) {}

Motor::Motor(unsigned int pin, unsigned int freq) : kPin_(pin), freq_(freq) {
  // initiation, set pin, freq and range(precision)
  gpioSetMode(kPin_, PI_OUTPUT);
  gpioSetPWMfrequency(kPin_, freq_);
  gpioSetPWMrange(kPin_, kRange_);
}

void Motor::rotate(unsigned int dutycycle, unsigned int keep_sec = 0) {
  gpioPWM(kPin_, dutycycle);
  gpioSleep(PI_TIME_RELATIVE, keep_sec, keep_usec_);
  // set PWM 0, full off
  gpioPWM(kPin_, 0);
}

void Motor::start() {

}

void Motor::stop() {
}

Motor::~Motor() {
}