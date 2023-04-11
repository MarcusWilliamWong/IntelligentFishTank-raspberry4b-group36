#ifndef HEATER_H_
#define HEATER_H_

#include <tuple>
#include "pwmctrl.h"

// we use GPIO 26 to connect heater pwm
class Heater : public PwmController {
public:
	Heater(unsigned int pin);
	Heater(unsigned int pin, unsigned int freq);
	// compute 4 temperatures return tuple including the average, minimum, maximum
	std::tuple<double, double, double> processTempersCallback(const std::vector<double> &tempers);
	void start();
	void stop();
};

#endif