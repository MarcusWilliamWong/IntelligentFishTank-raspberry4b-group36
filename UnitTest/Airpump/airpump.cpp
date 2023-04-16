#include <pigpio.h>
#include <iostream>
#include "airpump.h"

// Test only
#define DEBUG

Airpump::Airpump(unsigned int pin) : PwmController(pin) {}

Airpump::Airpump(unsigned int pin, unsigned int freq)
  : PwmController(pin, freq) {}

// change pwm level
void Airpump::set(char lvl) {
  // set pwm level
  setPwmLvl(lvl);
  // Starts PWM on the GPIO
  int ret = gpioPWM(kPin_, dutycycle_);
  if (ret != 0) {
    std::cerr << TAG_AIRPUMP
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}

void Airpump::stop() {
  // set pwm level
  setPwmLvl('0');
  int ret = gpioPWM(kPin_, 0);
  if (ret != 0) {
    std::cerr << TAG_AIRPUMP
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}

Airpump::~Airpump() { this->stop(); }