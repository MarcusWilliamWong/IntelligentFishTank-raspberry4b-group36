#ifndef MYDS18B20_H_
#define MYDS18B20_H_

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include "heater.h"

// we use four thermometers connecting with GPIO 5, 6, 13, 19 using wire-1
class Thermometer {
public:
  Thermometer();
  void registerHeater(Heater *heater);
	void start();
	void stop();

	// Test use
  // const std::vector<std::string> &get_dev() const;
  // const std::vector<double> &get_temp() const;
	
private:
  // save device file path
	std::vector<std::string> device_files_;
  // save temperatures
  std::vector<double> tempers_;
	// bind heater object to listen temperatures
  std::shared_ptr<Heater> heater_ptr_;
  std::unique_ptr<std::thread> thread_ptr_;
	bool running_;
  void ReadAllTemp();
	// find and record thermometer files
  const std::vector<std::string> &FindTempDevices ();
};

#endif