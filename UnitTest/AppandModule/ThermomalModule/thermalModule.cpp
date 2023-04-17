#include <functional>
#include <tuple>
// #include <future>
#include "thermalModule.h"
#include "config.h"
#include "threadPool.h"

#include "unistd.h"

// ThermalModule::ThermalModule(std::shared_ptr<ThreadPool> &pool_ptr) : 
// 	thermometer_(), 
// 	heater_(app_config::HEATER_PIN), 
// 	pool_ptr_(pool_ptr), 
// 	running_(true), 
// 	tempRange_(24.0, 40.0),
// 	thermo_thread_ptr_(nullptr),
// 	heater_thread_ptr_(nullptr) {
// 	// pool_ptr_.use_count() -> 2;
// 	start();
// }

ThermalModule::ThermalModule() :// pool_ptr_(pool_ptr), 
	running_(true), 
	tempRange_(24.0, 40.0){
	thermometer_ptr_.reset(new Thermometer());
	heater_ptr_.reset(new Heater(app_config::HEATER_PIN));
	// pool_ptr_.use_count() -> 2;
	start();
}

ThermalModule::~ThermalModule() {
	stop();
}

void ThermalModule::start() {
	if (!running_) {
		running_ = true;
		thermometer_ptr_->registerHeater(&heater_);
	}
	
	
}

void ThermalModule::stop() {
	running_ = false;
	heater_.turnOff();
	thermometer_.turnOff();
}

void ThermalModule::execute() {
	std::cout << "----- ThermalModule execute -----\n";
	// while (true) {
		// auto task1 = std::bind(&Thermometer::turnOn, std::ref(thermometer_));

	// std::packaged_task<void()> f(task);
	// pool_ptr_->AddTask(std::move(f));
	pool_ptr_->AddTask([this]{ });

	// thermo_thread_ptr_ = std::make_shared<std::thread>(&Thermometer::turnOn, &thermometer_);

	// std::tuple<double, double> tempRange_ = std::make_tuple<double, double>(24.0, 40.0);
	// auto task2 = std::bind(&Heater::ControlHeater, std::ref(heater_));
	pool_ptr_->AddTask([this]{  });
	// heater_thread_ptr_ = std::make_shared<std::thread>(&Heater::ControlHeater, &heater_);
	// }
	
	// thermo_thread_ptr_->detach();
	// heater_thread_ptr_->detach();
}

// void ThermalModule::controlHeater() {
// 	bool turnOn_flag = true;
// 	bool turnOff_flag = true;
// 	while (running_) {
// 		// std::cout << std::get<0>(heater_.getTempsInfo()) << "`C\n" << std::endl;
// 		// if current average temp lower than min threshold
// 		if (std::get<0>(heater_.getTempsInfo()) < std::get<0>(tempRange_)) {
// 			std::cout << "current average t = " << std::get<0>(heater_.getTempsInfo()) << ", lower than min" << std::endl;
// 			// if (turnOn_flag) {
// 			// 	heater_.turnOn();
// 			// 	~turnOn_flag;
// 			// 	turnOff_flag = true;
// 			// }
// 		} else if (std::get<0>(heater_.getTempsInfo()) > std::get<1>(tempRange_)) {
// 			std::cout << "current average t = " << std::get<0>(heater_.getTempsInfo()) << ", higher than max" << std::endl;
// 			// if (turnOff_flag) {
// 			// 	heater_.turnOff();
// 			// 	~turnOff_flag;
// 			// 	turnOn_flag = true;
// 			// }
// 		}
// 	}
// }