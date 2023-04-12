#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <pigpio.h>
#include "heater.h"

Heater::Heater(unsigned int pin) : PwmController(pin) {}

Heater::Heater(unsigned int pin, unsigned int freq) : PwmController(pin, freq) {}

void Heater::turnOn() {
  gpioPWM(kPin_, dutycycle_);
}

void Heater::turnOff() {
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
	tempsInfo_ = std::move(std::make_tuple(average, *minmax.first, *minmax.second));
}

const std::tuple<double, double, double> &Heater::getTempsInfo() {
	return tempsInfo_;
}