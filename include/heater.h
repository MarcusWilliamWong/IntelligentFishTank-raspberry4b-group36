#ifndef HEATER_H_
#define HEATER_H_

#include "pwmctrl.h"

// we use GPIO 26 to connect heater pwm
class Heater : public PwmController {
public:
	Heater(unsigned int pin);
	Heater(unsigned int pin, unsigned int freq);
	void processTempersCallback(const std::vector<double> &tempers);
	void start();
	void stop();
};

#endif