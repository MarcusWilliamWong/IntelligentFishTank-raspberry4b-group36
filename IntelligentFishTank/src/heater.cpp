#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <mutex>
#include <pigpio.h>
#include "heater.h"

#include <iostream>
#include <unistd.h>

Heater::Heater(unsigned int pin) : PwmController(pin) {}

Heater::Heater(unsigned int pin, unsigned int freq) : PwmController(pin, freq) {}

void Heater::turnOn() {
	running_ = true;
	std::cout << "heater turn on" << std::endl;
	std::cout << "gpioGetPWM : " << kPin_ << "; before set dutycycle : " << dutycycle_ << std::endl;
	// gpioSetMode(kPin_, PI_ALT5);
  // gpioSetPWMfrequency(kPin_, freq_);
  // gpioSetPWMrange(kPin_, kRange_);
	std::cout << "gpioGetPWM : " << kPin_ << "; after set dutycycle : " << dutycycle_ << std::endl;
  gpioPWM(kPin_, dutycycle_);
	for (int i = 0; i < 5; ++i ) {
		setPwmLevel(static_cast<unsigned int>(i));
		gpioPWM(kPin_, dutycycle_);
		sleep(5);
	}
	// turnOff();
	// while(true) {
		
	// };
	// std::cout << "gpioGetPWM : " << gpioGetPWMdutycycle(kPin_) << "; dutycycle : " << dutycycle_ << std::endl;
}

void Heater::turnOff() {
	running_ = false;
	std::cout << "heater turn off" << std::endl;
	setPwmLevel(0);
  gpioPWM(kPin_, 0);
}

// compute 4 temperatures return tuple including the average, minimum, maximum
void Heater::ProcessTempers(const std::vector<double> &tempers) {
	auto minmax = std::minmax_element(tempers.cbegin(), tempers.cend());
	double average = 0.0;
	if (!tempers.empty()) {
		average = std::accumulate(tempers.cbegin(), tempers.cend(), 0.0) / tempers.size();
	}
	{
		std::lock_guard<std::mutex> lock(mtx_);
		tempsInfo_ = std::move(std::make_tuple(average, *minmax.first, *minmax.second));
		std::cout << "Task1 is ok! Average : " << std::get<0>(tempsInfo_) << std::endl;
	}
	
}

// conditional n off heater
void Heater::ControlHeater() {
	bool turnOn_flag = true;
	bool turnOff_flag = true;
	while (running_) {
		std::lock_guard<std::mutex> lock(mtx_);
		// std::cout << std::get<0>(tempsInfo_) << "`C\n" << std::endl;
		// if current average temp lower than min threshold
		if (std::get<0>(tempsInfo_) < std::get<0>(tempRange_)) {
			std::cout << "current average t = " << std::get<0>(tempsInfo_) << ", lower than min" << std::endl;
			if (turnOn_flag) {
				turnOn();
				~turnOn_flag;
				turnOff_flag = true;
			}
		} else if (std::get<0>(tempsInfo_) > std::get<1>(tempRange_)) {
			std::cout << "current average t = " << std::get<0>(tempsInfo_) << ", higher than max" << std::endl;
			if (turnOff_flag) {
				turnOff();
				~turnOff_flag;
				turnOn_flag = true;
			}
		}
	}
}

