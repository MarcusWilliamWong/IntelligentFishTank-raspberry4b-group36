#ifndef HEATER_H_
#define HEATER_H_

#include "pwmctrl.h"

class Heater : public PwmController {
public:
	Heater(unsigned int pin);
  Heater(unsigned int pin, unsigned int freq);
	void hasTemperature(const std::vector<double> &tempers);
  void start();
  void stop();
};

#endif