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
	std::cout << "Task2 is ok!" << std::get<0>(tempsInfo_) << std::endl;
	std::cout << "heater turn on" << std::endl;
	setPwmLevel(3);
  gpioPWM(kPin_, dutycycle_);
	// std::cout << "gpioGetPWM : " << gpioGetPWMdutycycle(kPin_) << "; dutycycle : " << dutycycle_ << std::endl;
	// while (true);
	// need while(true) to start heater
	std::cout << "needOn_flag_ is" << needOn_flag_ << std::endl;
	while (needOn_flag_) {
		// if current water temperature is  higher than max threshold
		if (std::get<0>(tempsInfo_) > std::get<1>(tempRange_)) {
			std::cout << "current temp detected :" << std::get<0>(tempsInfo_) << std::endl;
			// change flags and exit loop
			needOn_flag_ = false;
			needOff_flag_ = true;
			break;
		}
	}
	// reset needOn_flag_
	needOn_flag_ = true;
	// std::cout << "gpioGetPWM : " << gpioGetPWMdutycycle(kPin_) << "; dutycycle : " << dutycycle_ << std::endl;
}

void Heater::turnOff() {
	std::cout << "heater turn off" << std::endl;
  gpioPWM(kPin_, 0);
	while (needOff_flag_) {
		// if current water temperatur is higher than max threshold
		if (std::get<0>(tempsInfo_) < std::get<0>(tempRange_)) {
			// change flags and exit loop
			needOn_flag_ = true;
			needOff_flag_ = false;
			break;
		}
	}
	// reset needOff_flag_
	needOff_flag_ = true;
}

// 1st Callback func, compute 4 temperatures return tuple including the average, minimum, maximum
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

// 2nd Callback func, conditional n off heater
void Heater::ControlHeater() {
	// std::cout << "Task2 is ok!" << std::get<0>(tempsInfo_) << std::endl;
	// initialise two flags
	needOn_flag_ = true;
	needOff_flag_ = true;
	while (running_) {
		if (!std::get<0>(tempsInfo_)) {
			continue;
		}
		// std::cout << std::get<0>(tempsInfo_) << "`C\n" << std::endl;

		// if current average temp lower than min threshold
		if (std::get<0>(tempsInfo_) < std::get<0>(tempRange_)) {
			std::cout << "current average t = " << std::get<0>(tempsInfo_) << ", lower than min" << std::endl;
			turnOn();
		} else if (std::get<0>(tempsInfo_) > std::get<1>(tempRange_)) {
			std::cout << "current average t = " << std::get<0>(tempsInfo_) << ", higher than max" << std::endl;
			turnOff();
		} else {
			std::cout << "current average t = " << std::get<0>(tempsInfo_) << " is between the range" << std::endl;
		}
	}
}

