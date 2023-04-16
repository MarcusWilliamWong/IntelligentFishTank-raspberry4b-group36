#ifndef THERMALMODULE_H_
#define THERMALMODULE_H_

#include <tuple>
#include <memory>
#include "myds18b20.h"
#include "heater.h"
#include "threadPool.h"

// has heater and thermometer objects, and control heater via thermometer
class ThermalModule {
public:
	// ThermalModule(std::shared_ptr<ThreadPool> &pool_ptr);
	ThermalModule();
	~ThermalModule();
	void start();  // instantiation heater and thermometer, and register heater into thermometer
	void stop();   // stop module and release space
	// void controlHeater(); // according to real-time temperature to control heater open and close
	void execute(); // produce tasks and add tasks into thread pool

private:
	std::unique_ptr<Thermometer> thermometer_ptr_;
	std::unique_ptr<Heater> heater_ptr_;
	// std::shared_ptr<ThreadPool> pool_ptr_;
	bool running_;
	std::tuple<double, double> tempRange_;

	std::shared_ptr<std::thread> thermo_thread_ptr_;
	std::shared_ptr<std::thread> heater_thread_ptr_;
};

#endif