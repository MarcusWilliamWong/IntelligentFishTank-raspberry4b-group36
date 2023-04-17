/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
#include <functional>
#include "thermalModule.h"
#include "config.h"
#include "threadPool.h"

// initialise heater, thermometer, and register heater to thermometer
ThermalModule::ThermalModule() : Module(), tempRange_(24.0, 25.0) {
	thermometer_ptr_.reset(new Thermometer());
	heater_ptr_.reset(new Heater(app_config::HEATER_PIN));
	thermometer_ptr_->registerHeater(heater_ptr_);
}

ThermalModule::~ThermalModule() {
	if (running_) {
		this->stop(); 
	}
}

void ThermalModule::registerBluetooth(std::shared_ptr<Bluetooth> &bluetooth_ptr) {
	bluetooth_ptr_ = bluetooth_ptr;
}

// Callback function, automatically control heater via thermometer
void ThermalModule::executeAutoControlHeater() {
	std::cout << TAG_THERMOMETER << "running `AutoControlHeater` task..."
						<< std::endl;

	thermometer_ptr_->AutoControlHeater();
}

// stop all related equipments
void ThermalModule::stop() {
	if (running_) {
		running_ = false;
	}
	thermometer_ptr_->stop();
	heater_ptr_->stop();
}