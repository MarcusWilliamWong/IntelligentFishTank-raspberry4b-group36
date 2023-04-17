/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
#include <pigpio.h>
#include <iostream>
#include "airpump.h"

Airpump::Airpump(unsigned int pin) : PwmController(pin) {}

Airpump::Airpump(unsigned int pin, unsigned int freq)
  : PwmController(pin, freq) {}

Airpump::~Airpump() { 
  if (running_) {
		this->stop(); 
	}
}

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
  running_ = false;
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
