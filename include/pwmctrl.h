#ifndef PWMCTRL_H_
#define PWMCTRL_H_

class PwmController {
protected:
  const unsigned int kPin_; // output pin
  const unsigned int kRange_ = 1000u; // control precision of dutycycle
  
  unsigned int freq_ = 50u; // 5.0% = 50/1000
  unsigned int dutycycle_ = 0u;
  unsigned int keep_usec_ = 0u;

public:
  PwmController() = delete;
  PwmController(PwmController&) = delete;
  PwmController(unsigned int pin);
  PwmController(unsigned int pin, unsigned int freq);
  virtual void start() = 0;
  virtual void stop() = 0;
};

#endif
