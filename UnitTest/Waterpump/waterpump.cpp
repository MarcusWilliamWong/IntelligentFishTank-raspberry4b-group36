#include <pigpio.h>
#include <iostream>
#include "waterpump.h"

// Test only
#define DEBUG

Waterpump::Waterpump(unsigned int pin) : PwmController(pin) {}

Waterpump::Waterpump(unsigned int pin, unsigned int freq)
  : PwmController(pin, freq) {}

// change pwm level
void Waterpump::set(char lvl) {
  // set pwm level
  setPwmLvl(lvl);
  // Starts PWM on the GPIO
  int ret = gpioPWM(kPin_, dutycycle_);
  if (ret != 0) {
    std::cerr << TAG_WATERPUMP
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}

void Waterpump::stop() {
  // set pwm level
  setPwmLvl('0');
  int ret = gpioPWM(kPin_, 0);
  if (ret != 0) {
    std::cerr << TAG_WATERPUMP
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}

Waterpump::~Waterpump() { this->stop(); }