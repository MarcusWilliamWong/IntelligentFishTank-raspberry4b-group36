#ifndef PWMCTRL_H_
#define PWMCTRL_H_

#include <atomic>
#define TAG_PWMCTRL "pwmctrl : "

class PwmController {
public:
  PwmController() = delete;
  PwmController(PwmController&) = delete;
  PwmController(unsigned int pin);
  PwmController(unsigned int pin, unsigned int freq);

  bool isRunning(); // check equipment running status
  // set and start PWM on gpio
  virtual void set(char lvl) = 0;
  // proactively close equipment
  virtual void stop() = 0;
	
protected:
  const unsigned int kPin_; // output gpio pin
  const unsigned int kRange_; // control precision of dutycycle
  unsigned int freq_; // default device freq needs 50Hz = 20ms a period
  unsigned int dutycycle_; // default pwm level is ZeroLevel(0u)
  std::atomic_bool running_;  // equipment running status
  std::atomic_bool needOn_flag_;  // if need close
  std::atomic_bool needOff_flag_;  // if need close

  // just set dutycycle value, but not start PWM on the GPIO
	void setPwmLvl(char level);

private:
	// predefine 5 pwm levels
	enum class PwmLevel : unsigned int {
		PwmLvl0 = 0u,
		PwmLvl1 = 333u,
		PwmLvl2 = 500u,
		PwmLvl3 = 666u,
		PwmLvl4 = 1000u,
	};

};

#endif
