#ifndef PWMCTRL_H_
#define PWMCTRL_H_
#include <pigpio.h>
#include <thread>

class PwmContrller {
private:
  const unsigned int kPin_ = 12u; // output pin
  const unsigned int kRange_ = 1000u; // control precision of dutycycle
  
  unsigned int freq_ = 50u; // 5.0% = 50/1000
  unsigned int dutycycle_ = 0u;
  unsigned int keep_usec_ = 0u;
	bool running_;
	std::thread t_;

public:
  PwmContrller();
  PwmContrller(unsigned int pin);
  PwmContrller(unsigned int pin, unsigned int freq);
  void start();
  void stop();
  ~PwmContrller() = default;
  // motor rotate heater button by sleep seconds
  void rotate(unsigned int dutycycle, unsigned int keep_usec);

};

#endif
