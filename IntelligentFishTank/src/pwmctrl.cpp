#include <pigpio.h>
#include <memory>
#include "pwmctrl.h"

PwmController::PwmController(unsigned int pin) : PwmController(pin, 50u) {}

PwmController::PwmController(unsigned int pin, unsigned int freq) : kPin_(pin), freq_(freq), kRange_(1000u), dutycycle_(static_cast<unsigned int>(PwmLevel::ZeroLevel))  {
  // initiation, set pin, freq and range(precision)
  gpioSetMode(kPin_, PI_OUTPUT);
  gpioSetPWMfrequency(kPin_, freq_);
  gpioSetPWMrange(kPin_, kRange_);
}

void PwmController::setPwmLevel(unsigned int level) {
	switch (level) {
		case 0u: dutycycle_ = static_cast<unsigned int>(PwmLevel::ZeroLevel);
		case 1u: dutycycle_ = static_cast<unsigned int>(PwmLevel::LowLevel);
		case 2u: dutycycle_ = static_cast<unsigned int>(PwmLevel::MediumLevel);
		case 3u: dutycycle_ = static_cast<unsigned int>(PwmLevel::HighLevel);
		case 4u: dutycycle_ = static_cast<unsigned int>(PwmLevel::FullLevel);
		default: dutycycle_ = static_cast<unsigned int>(PwmLevel::ZeroLevel);
	}
}