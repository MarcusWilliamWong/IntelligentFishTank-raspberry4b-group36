#ifndef HEATER_H_
#define HEATER_H_

#define TAG_HEATER "heater : "
// Test only
#define DEBUG_HEATER

#include <tuple>
#include <mutex>
#include <vector>
#include <atomic>
#include <string>
#include "pwmctrl.h"

// we use GPIO 26 to connect heater pwm
class Heater : public PwmController {
public:
	Heater(unsigned int pin);
	Heater(unsigned int pin, unsigned int freq);
	~Heater();
	// bottom callback task, compute the average temperature, and automatically control heater on and off
	void ConditionalOnOff(const std::vector<double> &tempers);
	// bottom callback task, use blue cmd to set suitable temperature
	void setMinMaxLimit(int min, int max);
	// set and start PWM level on GPIO
  void set(char lvl) override;
  void stop() override;

private:
	double minLimit_{27.0};  // max Range
	double maxLimit_{28.0};  // min Range
	bool needOn_ = true;  // flag for need to call `turnOn`
	bool needOff_ = true; // flag for need to call `turnOff`
	void autoTurnOn(int average); // automatically turnOn
	void autoTurnOff(int average); // automatically turnOff
};

#endif