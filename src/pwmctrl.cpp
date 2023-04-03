#include "pwmctrl.h"
#include <iostream>

PwmContrller::PwmContrller() : PwmContrller(12u, 50u) {}

PwmContrller::PwmContrller(unsigned int pin) : PwmContrller(pin, 50u) {}

PwmContrller::PwmContrller(unsigned int pin, unsigned int freq) : kPin_(pin), freq_(freq) {
  // initiation, set pin, freq and range(precision)
  gpioSetMode(kPin_, PI_OUTPUT);
  gpioSetPWMfrequency(kPin_, freq_);
  gpioSetPWMrange(kPin_, kRange_);
}

void PwmContrller::start() {
	// t_ = thread();
}

void PwmContrller::stop() {
	if (t_.joinable()) {
		t_.join();
	} else {
		std::cerr << "Can't joint thread\n";
	}
}
