#ifndef WATERPUMP_H_
#define WATERPUMP_H_

#include "pwmctrl.h"

#include <tuple>
#include <vector>

class Waterpump : public PwmController {
public:
  Waterpump(unsigned int pin);
  Waterpump(unsigned int pin, unsigned int freq);
  ~Waterpump();
  void set();
  void stop();
};

#endif
