/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
#ifndef PWMCTRL_H_
#define PWMCTRL_H_

#define TAG_PWMCTRL "pwmctrl : "
// Test only
// #define DEBUG_PWMCTRL

#include <atomic>

class PwmController {
public:
  PwmController() = delete;
  PwmController(PwmController&) = delete;
  PwmController(unsigned int pin);
  PwmController(unsigned int pin, unsigned int freq);
  ~PwmController();
  bool isRunning() const; // check equipment running status
  // set and start PWM on gpio
  virtual void set(char lvl) = 0;
  // proactively close equipment
  virtual void stop() = 0;
	
protected:
  const unsigned int kPin_; // output gpio pin
  const unsigned int kRange_; // control precision of dutycycle
  unsigned int freq_; // default device freq needs 50Hz = 20ms a period
  // because Raspberry 4B is a 64bis machine, we use u_int64_t type
  unsigned int dutycycle_; // default pwm level is ZeroLevel(0u)
  std::atomic_bool running_;  // equipment running status

  // just set dutycycle value, but not start PWM on the GPIO
	void setPwmLvl(char level);

  #ifdef DEBUG_PWMCTRL
  inline unsigned int getPin() const {
		return kPin_;
	}

	inline unsigned int getDutycycle() const {
		return dutycycle_;
	}
  #endif

private:
	// predefine 5 pwm levels
	enum class PwmLevel : u_int64_t {
		PwmLvl0 = 0u,
		PwmLvl1 = 333u,
		PwmLvl2 = 500u,
		PwmLvl3 = 666u,
		PwmLvl4 = 1000u,
	};

};

#endif
