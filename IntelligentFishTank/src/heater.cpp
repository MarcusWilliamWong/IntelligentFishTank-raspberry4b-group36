#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <iostream>
#include <chrono>
#include <pigpio.h>
#include "heater.h"

// Test only
// #define DEBUG_THREADTASK


Heater::Heater(unsigned int pin) : PwmController(pin){}

Heater::Heater(unsigned int pin, unsigned int freq) 
	: PwmController(pin, freq) {}

Heater::~Heater() {
	if (running_) {
		this->stop(); 
	}
}

// bottom task, compute the average temperature, and conditionally call turnOn and turnOff
void Heater::ConditionalOnOff(const std::vector<double> &tempers) {
	// compute the average temperature
	double sum = 0.0;
	for (auto t : tempers) {
		sum += t;
	}
	double average = 0.0;
	if (auto len = tempers.size()) {
		average = sum / len;
	}
	std::cout << TAG_HEATER << "Average T(°C): " 
						<< average << std::endl;
	// if average is 0.0, return and wait for thermometer initialise
	if (!average) return;
	// average T lower than min threshold
	if (average < std::get<0>(tempRange_)) {
		// heat until higher than max range
		if (needOn_) {
			needOn_ = false;
			needOff_ = true;
			autoTurnOn(average);
		}
	} else if (average > std::get<1>(tempRange_)) {
		// wait temper cool until lower than mmin range
		if (needOff_) {
			needOff_ = false;
			needOn_ = true;
			// average T higher than max threshold
			autoTurnOff(average);
		}
	} else {
		#ifdef DEBUG_HEATER
		std::cout << TAG_HEATER << "suitable temperature" << std::endl;
		#endif
	}
}

void Heater::autoTurnOn(int average) {
	std::cout << TAG_HEATER << "auto start Heater" << std::endl;
	// start configed PWM level on GPIO, if configured as lvl0, automatically set lvl3
	if (!dutycycle_) {
		setPwmLvl('3');
	} else {
		// if dutycycle not lvl0, keep original dutycycle
		gpioPWM(kPin_, dutycycle_);
	}
}

void Heater::autoTurnOff(int average) {
	std::cout << TAG_HEATER << "auto stop Heater" << std::endl;
  gpioPWM(kPin_, 0);
}

// set and start other PWM level
void Heater::set(char lvl) {
  // set pwm level
  setPwmLvl(lvl);
  // Starts PWM on the GPIO
  int ret = gpioPWM(kPin_, dutycycle_);
  if (ret != 0) {
    std::cerr << TAG_HEATER
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}

void Heater::stop() {
	running_ = false;
  // set pwm level
  setPwmLvl('0');
  int ret = gpioPWM(kPin_, 0);
  if (ret != 0) {
    std::cerr << TAG_HEATER
              << "failed to set dutycycle: " << dutycycle_
              << " on gpio: " << kPin_ << " with err code: " << ret
              << std::endl;
  }
}




