#include <pigpio.h>
#include <memory>
#include "pwmctrl.h"

#include <iostream>

PwmController::PwmController(unsigned int pin) : PwmController(pin, 50u) {}

PwmController::PwmController(unsigned int pin, unsigned int freq) : kPin_(pin), kRange_(1000u), freq_(freq), dutycycle_(static_cast<unsigned int>(PwmLevel::ZeroLevel)), running_(true) {
  // initiation, set pin, freq and range(precision)
  gpioSetMode(kPin_, PI_ALT5);
  gpioSetPWMfrequency(kPin_, freq_);
  gpioSetPWMrange(kPin_, kRange_);
}

void PwmController::setPwmLevel(unsigned int level) {
	switch (level) {
		case 0u: dutycycle_ = static_cast<unsigned int>(PwmLevel::ZeroLevel); break;
		case 1u: dutycycle_ = static_cast<unsigned int>(PwmLevel::LowLevel); break;
		case 2u: dutycycle_ = static_cast<unsigned int>(PwmLevel::MediumLevel); break;
		case 3u: dutycycle_ = static_cast<unsigned int>(PwmLevel::HighLevel); break;
		case 4u: dutycycle_ = static_cast<unsigned int>(PwmLevel::FullLevel); break;
		default: dutycycle_ = static_cast<unsigned int>(PwmLevel::ZeroLevel); break;
	}
	std::cout << "set dutycycle : " << dutycycle_ << std::endl;
}


bool PwmController::isRunning() {
	return running_;
}