#ifndef SG90HV_H_
#define SG90HV_H_t_;

#include <thread>
#include <vector>
#include <pigpio.h>
#include "ds18b20_.h"


class Motor {
private:
  const unsigned int kPin_ = 12; // motor pin
  const unsigned int kRange_ = 1000; // control precision of dutycycle
  
  unsigned int freq_ = 50; // 5.0% = 50/1000
  unsigned int dutycycle_ = 0;
  unsigned int keep_usec_ = 0;
  std::thread t_;
  std::vector<Thermometer> therms_;
  void ControlHeater();

public:
  Motor() = default;
  Motor(unsigned int pin);
  Motor(unsigned int pin, unsigned int freq);
  void start();
  void stop();
  ~Motor();
  // motor rotate heater button by sleep seconds
  void rotate(unsigned int dutycycle, unsigned int keep_usec);

};
#endif
