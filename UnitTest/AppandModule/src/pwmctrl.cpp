#include <pigpio.h>
#include <memory>
#include <iostream>
#include "pwmctrl.h"

PwmController::PwmController(unsigned int pin) : PwmController(pin, 50u) {}

PwmController::PwmController(unsigned int pin, unsigned int freq) 
	: kPin_(pin), kRange_(1000u), freq_(freq), 
	dutycycle_(static_cast<u_int64_t>(0)), running_(true) 
{
  // initiation, set pin, freq and range(precision)
  gpioSetMode(kPin_, PI_ALT5);
  gpioSetPWMfrequency(kPin_, freq_);
  gpioSetPWMrange(kPin_, kRange_);
	gpioPWM(kPin_, 0u);
}

PwmController::~PwmController() {
	if (running_) {
		running_ = false;
	}
	// close PWM on GPIO
	gpioPWM(kPin_, 0u);
}

void PwmController::setPwmLvl(char lvl) {
	switch (lvl) {
		case '0': 
			dutycycle_ = static_cast<u_int64_t>(PwmLevel::PwmLvl0); 
			break;
		case '1': 
			dutycycle_ = static_cast<u_int64_t>(PwmLevel::PwmLvl1); 
			break;
		case '2': 
			dutycycle_ = static_cast<u_int64_t>(PwmLevel::PwmLvl2); 
			break;
		case '3': 
			dutycycle_ = static_cast<u_int64_t>(PwmLevel::PwmLvl3); 
			break;
		case '4': 
			dutycycle_ = static_cast<u_int64_t>(PwmLevel::PwmLvl4); 
			break;
		default: 
			std::cerr << TAG_PWMCTRL << "unknown level :" << lvl
								<< " keep original pwm level" << std::endl;
			break;
	}

	#ifdef DEBUG_PWMCTRL
	std::cout << TAG_PWMCTRL << "set PWM dutycycle as " 
						<< dutycycle_ << "/" << kRange_ << std::endl;
	#endif
}

bool PwmController::isRunning() const { return running_; }