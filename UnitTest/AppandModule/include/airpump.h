#ifndef AIRPUMP_H_
#define AIRPUMP_H_

#define TAG_AIRPUMP "airpump : "

// Test only
#define DEBUG_AIRPUMP

#include "pwmctrl.h"

class Airpump : public PwmController {
public:
  Airpump(unsigned int pin);
  Airpump(unsigned int pin, unsigned int freq);
  ~Airpump();

  // bottom callback task, set and start new PWM on GPIO 
  void set(char lvl) override;
  void stop() override;
};

#endif