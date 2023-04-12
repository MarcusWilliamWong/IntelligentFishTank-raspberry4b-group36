#include <functional>
#include <tuple>
// #include <future>
#include "thermalModule.h"
#include "config.h"
#include "threadPool.h"

ThermalModule::ThermalModule(ThreadPool *pool_ptr) : thermometer_(), heater_(app_config::HEATER_PIN), pool_ptr_(pool_ptr), tempRange_(29.0, 29.5) {
	start();
}

void ThermalModule::start() {
	thermometer_.registerHeater(&heater_);
}

void ThermalModule::stop() {
	heater_.turnOff();
	thermometer_.turnOff();
}

void ThermalModule::execute() {
	auto task1 = std::bind(&Thermometer::turnOn, std::ref(thermometer_));
	// std::packaged_task<void()> f(task);
	// pool_ptr_->AddTask(std::move(f));
	pool_ptr_->AddTask(task1);

	while (true) {
		auto task2 = std::bind(&ThermalModule::controlHeater, std::ref(*this));
		pool_ptr_->AddTask(task2);
	}
}

void ThermalModule::controlHeater() {
	// if current average temp lower than min threshold
	if (std::get<0>(heater_.getTempsInfo()) < std::get<0>(tempRange_)) {
		std::cout << "current average t = " << std::get<0>(heater_.getTempsInfo()) << " and heater turn on" << std::endl;
		// heater_.turnOn();
	} else if (std::get<0>(heater_.getTempsInfo()) > std::get<0>(tempRange_)) {
		std::cout << "current average t = " << std::get<0>(heater_.getTempsInfo()) << " and heater turn on" << std::endl;
		// heater_.turnOff();
	}
}