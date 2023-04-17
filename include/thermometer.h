#ifndef THERMOMETER_H_
#define THERMOMETER_H_
// Device type : DS18B20

#define TAG_THERMOMETER "thermometer : "

// Test only
// #define DEBUG_THERMOMETER

#include <vector>
#include <memory>
#include <mutex>
#include "heater.h"

// we use four thermometers connecting with GPIO 5, 6, 13, 19 using wire-1
class Thermometer {
public:
  Thermometer();
  ~Thermometer();
  // register Heater
  void registerHeater(std::shared_ptr<Heater> &heater_ptr);
  // bottom callback task, automatically conditionally control heater via thermometer
  void AutoControlHeater();
  void stop();

	// Test use
  #ifdef DEBUG_THERMOMETER
  // const std::vector<std::string> &get_dev() const;
  // const std::vector<double> &get_temps() const;
  #endif
	
private:
  bool running_;
  // see Heater as callback class, pointer to heater object to listen temperatures
  std::shared_ptr<Heater> heater_ptr_;
  // save device file path
	std::vector<std::string> device_files_;
  // save temperatures
  std::vector<double> tempers_;

	// find and record thermometer files
  void FindTempDevices();
};

#endif