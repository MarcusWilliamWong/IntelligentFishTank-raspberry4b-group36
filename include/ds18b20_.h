#ifndef DS18B20_H_
#define DS18B20_H_

#include <string>
#include <thread>

class Thermometer {
private:
  // save once temperature per minute
  double temp_;
  bool ReadTemp();
  std::string FindTempDevices();
public:
  Thermometer();
  double get_temp() const;
  // ~Thermometer();
};

#endif