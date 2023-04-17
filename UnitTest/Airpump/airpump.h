#ifndef AIRPUMP_H_
#define AIRPUMP_H_

#define TAG_AIRPUMP "airpump : "

#include "pwmctrl.h"

class Airpump : public PwmController {
public:
  Airpump(unsigned int pin);
  Airpump(unsigned int pin, unsigned int freq);
  ~Airpump();
  // set gpiopwm, cmd control pwm level, call setPwmLvl()
  void set(char lvl) override;
  void stop() override;
};

#endif