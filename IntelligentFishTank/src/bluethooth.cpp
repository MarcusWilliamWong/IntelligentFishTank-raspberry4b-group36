#include "bluetooth.h"

#include <iostream>

Bluetooth::Bluetooth(std::string tty) : tty_(tty) {
  if ((handle_ = serOpen(&tty_[0], 9600, 0)) < 0) {
    throw std::runtime_error("serial cannot be opened!");
  }
}

Bluetooth::~Bluetooth() { serClose(handle_); }

int Bluetooth::recvData(char *data, unsigned int len) const {
  int ret;
  if ((ret = serDataAvailable(this->handle_)) < len) {
    return ret;
  }
  if ((ret = serRead(this->handle_, data, len)) != len) {
    return ret;
  }
  return len;
}

int Bluetooth::sendData(char *data, unsigned int len) const {
  return serWrite(this->handle_, data, len);
}
