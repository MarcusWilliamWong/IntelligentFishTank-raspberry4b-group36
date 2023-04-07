#ifndef SG90HV_H_
#define SG90HV_H_t_;

class Motor {
public:
  Motor();
  Motor(unsigned int pin);
  Motor(unsigned int pin, unsigned int freq);
  void start();
  void stop();
  ~Motor();
  // motor rotate heater button by sleep seconds
  void rotate(unsigned int dutycycle, unsigned int keep_usec);

private:
  const unsigned int kPin_ = 12u; // motor pin
  const unsigned int kRange_ = 1000u; // control precision of dutycycle
  unsigned int freq_ = 50u; // 5.0% = 50/1000
  unsigned int dutycycle_ = 0u;
  unsigned int keep_usec_ = 0u;
};
#endif
