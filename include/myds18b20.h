#ifndef MYDS18B20_H_
#define MYDS18B20_H_

#include <string>
#include <vector>
#include <thread>

class Thermometer {
private:
	std::vector<std::string> device_files;
  // save four temperature
  std::vector<double> temp_;
  void ReadTemp();
  const std::vector<std::string> FindTempDevices();
	std::thread t_;
	bool running_;
public:
  Thermometer();
	void start();
	void stop();
  const std::vector<double> &get_temp() const;
  ~Thermometer();
};

#endif