#ifndef HEATER_H_
#define HEATER_H_

#define TAG_HEATER "heater : "
// Test only
#define DEBUG_HEATER

#include <tuple>
#include <mutex>
#include <vector>
#include "pwmctrl.h"

// we use GPIO 26 to connect heater pwm
class Heater : public PwmController {
public:
	Heater(unsigned int pin);
	Heater(unsigned int pin, unsigned int freq);
	~Heater();
	// bottom task, automatically control heater on and off
	void AutoControlHeater();
	// bottom task, compute the average, minimum, maximum for 4 temperatures 
	void ProcessTempers(const std::vector<double> &tempers);
	// set gpiopwm, cmd control pwm level, call setPwmLvl()
  void set(char lvl) override;
  void stop() override;

private:
	std::mutex mtx_;
	std::unique_ptr<double> average_;
	std::tuple<double, double> tempRange_ = std::make_tuple<double, double>(26.0, 26.5);

	void turnOn(); // automatically turnOn
	void turnOff(); // automatically turnOff
};

#endif