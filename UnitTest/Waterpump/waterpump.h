#ifndef WATERPUMP_H_
#define WATERPUMP_H_

#define TAG_WATERPUMP "waterpump : "

#include "pwmctrl.h"

class Waterpump : public PwmController {
public:
  Waterpump(unsigned int pin);
  Waterpump(unsigned int pin, unsigned int freq);
  ~Waterpump();
  // set gpiopwm, cmd control pwm level, call setPwmLvl()
  void set(char lvl) override;
  void stop() override;
};

#endif
