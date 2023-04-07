#include <vector>
#include <algorithm>
#include <tuple>
#include <pigpio.h>
#include "heater.h"

Heater::Heater(unsigned int pin) : PwmController(pin) {}

Heater::Heater(unsigned int pin, unsigned int freq) : PwmController(pin, freq) {}

void Heater::start() {
  gpioPWM(this->kPin_, 500);
  gpioSleep(PI_TIME_RELATIVE, 6, 0);
}

void Heater::stop() {
  gpioPWM(this->kPin_, 0);
}

// compute 4 temperatures return tuple including the average, minimum, maximum
std::tuple<double, double, double> processTempersCallback(const std::vector<double> &tempers) {
	auto minmax = std::minmax_element(tempers.cbegin(), tempers.cend());
	double average = 0.0;
	if (!tempers.empty) {
		average = std::accumulate(tempers.cbegin(), tempers.cend()) / tempers.size();
	}
	return std::make_tuple(average, minmax.first, minmax.second);
}