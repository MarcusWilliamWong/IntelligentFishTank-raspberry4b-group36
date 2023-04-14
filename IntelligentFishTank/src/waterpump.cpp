#include "waterpump.h"

#include <pigpio.h>

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#define TAG_WATERPUMP_CTRL "waterpump-ctrl"

Waterpump::Waterpump(unsigned int pin) : PwmController(pin) {}

Waterpump::Waterpump(unsigned int pin, unsigned int freq)
  : PwmController(pin, freq) {}

void Waterpump::set() {
  int ret = gpioPWM(kPin_, dutycycle_);
  if (ret != 0) {
    std::cerr << TAG_WATERPUMP_CTRL
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}

void Waterpump::stop() {
  int ret = gpioPWM(kPin_, 0);
  if (ret != 0) {
    std::cerr << TAG_WATERPUMP_CTRL
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}

Waterpump::~Waterpump() { this->stop(); }