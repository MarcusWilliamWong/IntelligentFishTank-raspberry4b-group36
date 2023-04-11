#ifndef PWMCTRL_H_
#define PWMCTRL_H_

class PwmController {
public:
  PwmController() = delete;
  PwmController(PwmController&) = delete;
  PwmController(unsigned int pin);
  PwmController(unsigned int pin, unsigned int freq);
	// cmd control pwm level
	void setPwmLevel(unsigned int level);
  virtual void set() = 0;
  virtual void stop() = 0;

protected:
	// predefine 5 pwm levels
	enum class PwmLevel :unsigned int {
		ZeroLevel = 0u,
		LowLevel = 333u,
		MediumLevel = 500u,
		HighLevel = 666u,
		FullLevel = 1000u,
	};
  const unsigned int kPin_; // output gpio pin
  const unsigned int kRange_ = 1000u; // control precision of dutycycle
  unsigned int freq_ = 50u; // default device freq needs 50Hz = 20ms a period
	// default pwm level is ZeroLevel
  unsigned int dutycycle_ = static_cast<unsigned int>(PwmLevel::ZeroLevel);
  // unsigned int keep_usec_ = 0u;
};

#endif
