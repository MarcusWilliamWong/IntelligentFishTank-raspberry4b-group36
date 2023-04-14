#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <pigpio.h>

#include <string>

class Bluetooth {
public:
  Bluetooth(std::string tty);
  ~Bluetooth();

  int recvData(char *data, unsigned int len) const;
  int sendData(char *data, unsigned int len) const;

private:
  std::string tty_;
  int handle_ = -1;
};

#endif
