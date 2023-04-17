#ifndef WATERPUMP_H_
#define WATERPUMP_H_

#define TAG_WATERPUMP "waterpump : "
// Test only
#define DEBUG_WATERPUMP

#include "pwmctrl.h"

class Waterpump : public PwmController {
public:
  Waterpump(unsigned int pin);
  Waterpump(unsigned int pin, unsigned int freq);
  ~Waterpump();
  // bottom callback task, set and start new PWM on GPIO 
  void set(char lvl) override;
  void stop() override;
};

#endif
