#ifndef THERMALMODULE_H_
#define THERMALMODULE_H_

#include <tuple>
#include <memory>
#include "myds18b20.h"
#include "heater.h"
#include "threadPool.h"

class ThermalModule {
public:
	ThermalModule(std::shared_ptr<ThreadPool> &pool_ptr);
	~ThermalModule();
	void start();  // instantiation heater and thermometer, and register heater into thermometer
	void stop();   // stop module and release space
	// void controlHeater(); // according to real-time temperature to control heater open and close
	void execute(); // produce tasks and add tasks into thread pool

private:
	Thermometer thermometer_;
	Heater heater_;
	std::shared_ptr<ThreadPool> pool_ptr_;
	bool running_;
	std::tuple<double, double> tempRange_;
};

#endif