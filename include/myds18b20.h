#ifndef MYDS18B20_H_
#define MYDS18B20_H_

#include <iostream>
#include <vector>
#include <thread>
#include "heater.h"

// we use four thermometers connecting with GPIO 23 24 25 12 using wire-1
class Thermometer {
private:
  // save device file path
	std::vector<std::string> device_files_;
  // save temperatures
  std::vector<double> tempers_;
  Heater *heater_;
  std::thread t_;
	bool running_;
  void ReadAllTemp();
  const std::vector<std::string> &FindTempDevices ();
	
public:
  Thermometer();
  void registerHeater(Heater *heater);
	void start();
	void stop();

	// Test use
  // const std::vector<std::string> &get_dev() const;
  // const std::vector<double> &get_temp() const;
};

#endif