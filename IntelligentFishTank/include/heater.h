#ifndef HEATER_H_
#define HEATER_H_

#include <tuple>
#include "pwmctrl.h"

// we use GPIO 26 to connect heater pwm
// see Heater as callback class
class Heater : public PwmController {
public:
	Heater(unsigned int pin);
	Heater(unsigned int pin, unsigned int freq);

	void turnOn() override;
	void turnOff() override;
	// compute 4 temperatures return tuple including the average, minimum, maximum
	void ProcessTempers(const std::vector<double> &tempers);
	// average, minimum, maximum
	const std::tuple<double, double, double> &getTempsInfo();

private:
	// average, minimum, maximum
	std::tuple<double, double, double> tempsInfo_;
};

#endif