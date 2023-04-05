#ifndef MYDS18B20_H_
#define MYDS18B20_H_

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

typedef struct ThermoCallback {
public:
  void hasTemperature(const std::vector<double> &tempers) {
    for (const auto &t : tempers) {
      std::cout << t << " ";
    }
    std::cout << '\n';
  }
} ThermoCallback;


// we use four thermometers connecting with GPIO 23 24 25 12 using wire-1
class Thermometer {
private:
  // save device file path
	std::vector<std::string> device_files;
  // save temperatures
  std::vector<double> tempers_;
  ThermoCallback *tc;
  std::thread t_;
  std::mutex mtx;
	bool running_;
  void ReadAllTemp();
  const std::vector<std::string> &FindTempDevices();
	
public:
  Thermometer();
  void registerCallback(ThermoCallback *tc);
	void start();
	void stop();
  // const std::vector<std::string> &get_dev() const;
  // const std::vector<double> &get_temp() const;
};

#endif