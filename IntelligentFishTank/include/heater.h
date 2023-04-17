#ifndef HEATER_H_
#define HEATER_H_

#define TAG_HEATER "heater : "
// Test only
#define DEBUG_HEATER

#include <tuple>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "pwmctrl.h"


// we use GPIO 26 to connect heater pwm
class Heater : public PwmController {
public:
	Heater(unsigned int pin);
	Heater(unsigned int pin, unsigned int freq);
	~Heater();
	// bottom task, compute the average temperature, and automatically control heater on and off
	void ConditionalOnOff(const std::vector<double> &tempers);
	// set and start PWM level on GPIO
  void set(char lvl) override;
  void stop() override;

private:
	std::tuple<double, double> tempRange_ = std::make_tuple<double, double>(31.0, 32.0);
	bool needOn_ = true;  // flag for need to call `turnOn`
	bool needOff_ = true; // flag for need to call `turnOff`
	void autoTurnOn(int average); // automatically turnOn
	void autoTurnOff(int average); // automatically turnOff
};

#endif