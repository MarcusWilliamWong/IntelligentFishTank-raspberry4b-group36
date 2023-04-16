#ifndef MYDS18B20_H_
#define MYDS18B20_H_

#include <vector>
#include <memory>
#include "heater.h"

// we use four thermometers connecting with GPIO 5, 6, 13, 19 using wire-1
class Thermometer {
public:
  Thermometer();
  ~Thermometer() = default;
  // register Heater object
  void registerHeater(std::unique_ptr<Heater> &heater_ptr);
  void turnOn();
  void turnOff();

	// Test use
  const std::vector<std::string> &get_dev() const;
  const std::vector<double> &get_temp() const;
	
private:
  bool running_;
  // see Heater as callback class, pointer to heater object to listen temperatures
  Heater *heater_ptr_;
  // save device file path
	std::vector<std::string> device_files_;
  // save temperatures
  std::vector<double> tempers_;


  // execute read temperature task
  void ReadAllTemp();
	// find and record thermometer files
  const std::vector<std::string> &FindTempDevices ();
};

#endif