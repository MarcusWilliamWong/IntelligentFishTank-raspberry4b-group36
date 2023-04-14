#ifndef PWMCTRL_H_
#define PWMCTRL_H_

#include <atomic>

class PwmController {
public:
  PwmController() = delete;
  PwmController(PwmController&) = delete;
  PwmController(unsigned int pin);
  PwmController(unsigned int pin, unsigned int freq);
	// cmd control pwm level
	void setPwmLevel(unsigned int level);
  // manually on and off equipment
  virtual void turnOn() = 0;
  virtual void turnOff() = 0;
	bool isRunning(); // check equipment running status

protected:
	// predefine 5 pwm levels
	enum class PwmLevel : unsigned int {
		ZeroLevel = 0u,
		LowLevel = 333u,
		MediumLevel = 500u,
		HighLevel = 666u,
		FullLevel = 1000u,
	};

  const unsigned int kPin_; // output gpio pin
  const unsigned int kRange_; // control precision of dutycycle
  unsigned int freq_; // default device freq needs 50Hz = 20ms a period
  unsigned int dutycycle_; // default pwm level is ZeroLevel(0u)
  std::atomic_bool running_;  // equipment running status
  std::atomic_bool needOn_flag_;  // if need close
  std::atomic_bool needOff_flag_;  // if need close
  // std::atomic_bool needStop;
};

#endif
