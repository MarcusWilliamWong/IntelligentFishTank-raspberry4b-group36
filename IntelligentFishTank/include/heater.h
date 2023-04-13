#ifndef HEATER_H_
#define HEATER_H_

#include <tuple>
#include <mutex>
#include <vector>
#include "pwmctrl.h"

// we use GPIO 26 to connect heater pwm
// see Heater as callback class
class Heater : public PwmController {
public:
	Heater(unsigned int pin);
	Heater(unsigned int pin, unsigned int freq);

	void turnOn() override;
	void turnOff() override;
	// callback function, compute the average, minimum, maximum for 4 temperatures 
	void ProcessTempers(const std::vector<double> &tempers);
	// callback function, control heater on and off
	void ControlHeater();

	// Test
	// const unsigned int getPin() {
	// 	return kPin_;
	// }

	// unsigned int getDutycycle() {
	// 	return dutycycle_;
	// }

private:
	std::mutex mtx_;
	// average, minimum, maximum
	std::tuple<double, double, double> tempsInfo_;
	std::tuple<double, double> tempRange_ = std::make_tuple<double, double>(28.0, 40.0);
};

#endif