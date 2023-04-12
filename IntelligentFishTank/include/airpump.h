#ifndef AIRPUMP_H_
#define AIRPUMP_H_
#include "pwmctrl.h"

// we use gpio 
class Airpump : public PwmController {
public:
  Airpump(unsigned int pin);
  Airpump(unsigned int pin, unsigned int freq);
  void turnOn() override;
  void turnOff() override;
};

#endif