#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <pigpio.h>
#include "heater.h"

// Test only
#define DEBUG_THREADTASK


Heater::Heater(unsigned int pin) : PwmController(pin), average_(new double{0.0}) {}

Heater::Heater(unsigned int pin, unsigned int freq) 
	: PwmController(pin, freq) {}

Heater::~Heater() {
	if (running_) {
		this->stop(); 
	}
}

// bottom task, compute 4 temperatures return tuple including the average, minimum, maximum
void Heater::ProcessTempers(const std::vector<double> &tempers) {
	std::cout << "ProcessTempers() " << TAG_HEATER << " Average T(°C): " 
						<< *average_ << std::endl;
	
	double sum = 0.0;
	for (auto t : tempers) {
		sum += t;
	}
	{
		std::lock_guard<std::mutex> lock(mtx_);
		if (!tempers.empty()) {
			*(average_.get()) = sum / tempers.size();
		}
	}
	std::cout << "new average " << *average_ << std::endl;

	#ifdef DEBUG_THREADTASK
	std::cout << TAG_HEATER << "ProcessTempers here" << std::endl;
	#endif
}

// bottom task, automatically control heater on and off
void Heater::AutoControlHeater() {
	std::cout << "AutoControlHeater() " << TAG_HEATER
						<< "average(°C) = " << *average_
						<< std::endl;

	while (running_) {
		std::cout << "In AutoControlHeater while" << std::endl;

		// if tempsInfo is still not write by `ProcessTemps`
		// just sleep and wait for thermometer catch the first temperature
		if (!average_) {
			#ifdef DEBUG_THREADTASK
			std::cout << TAG_HEATER << "wait for thermo init" << std::endl;
			#endif
			continue;
		}
		// if current average temp lower than min threshold
		if (*average_ < std::get<0>(tempRange_)) {
			turnOn();
			std::cout << TAG_HEATER << " lower than min " << std::get<0>(tempRange_) 
								<< " open heater" << std::endl;
		} else if (*average_ > std::get<1>(tempRange_)) {
			turnOff();
			std::cout << " higher than max " << std::get<1>(tempRange_)
								<< " close heater" << std::endl;
		} else {
			#ifdef DEBUG_HEATER
			std::cout << "is between the range" << std::endl;
			#endif
		}
	}
}

// automatically turnOn
void Heater::turnOn() {
	#ifdef DEBUG_HEATER
	// setPwmLvl('3');
	#endif
	// start configed PWM level on GPIO, if configured as lvl0, automatically set lvl2
	if (0u == dutycycle_) {
		setPwmLvl('3');
	}
  gpioPWM(kPin_, dutycycle_);
	// heat until higher than max range
	while (*average_ < std::get<1>(tempRange_)) {
		if (!dutycycle_) {
			set('3');
		}
		#ifdef DEBUG_HEATER
		std::cout << TAG_HEATER << "Average T(°C): " << *average_
							<< " need heat to max threshold" << std::endl;
		#endif
	}
}

// automatically turnOff
void Heater::turnOff() {
  gpioPWM(kPin_, 0);
	// wait temper cool until lower than mmin range
	while (*average_ > std::get<1>(tempRange_)) {
		if (dutycycle_) {
			gpioPWM(kPin_, 0);
		}
		#ifdef DEBUG_HEATER
		std::cout << TAG_HEATER << "Average T(°C): " << *average_
							<< " need cool to than min threshold" << std::endl;
		#endif
	}
}

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




