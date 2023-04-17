#include "module.h"
#include "pumpModule.h"
#include "config.h"
#include "thermalModule.h"


// initialise aripump and waterpump object
PumpModule::PumpModule() : Module(){
  airpump_ptr_.reset(new Airpump(app_config::AIRPUMP_PIN));
  waterpump_ptr_.reset(new Waterpump(app_config::WATERPUMP_PIN));
}

PumpModule::~PumpModule() {
  if (running_) {
		this->stop(); 
	}
}

// register bluetooth to pumpModule
// register waterpump, airpump to bluetooth
void PumpModule::registerBluetooth(std::shared_ptr<Bluetooth> &bluetooth_ptr) {
  bluetooth_ptr_ = bluetooth_ptr;
  bluetooth_ptr_->registerWaterpump(waterpump_ptr_);
  bluetooth_ptr_->registerAirpump(airpump_ptr_);
}

// register heater from ThermalModule
// as friend memeber function of ThermalModule
void PumpModule::registerHeaterFromThermalModule(std::shared_ptr<ThermalModule> &thermalModule_ptr) {
  bluetooth_ptr_->registerHeater(thermalModule_ptr->heater_ptr_);
}

// Callback function, accoring to bluetooth cmd queue to control waterpump/airpump PWM
void PumpModule::executeCmdControl() {
  std::cout << TAG_PUMPMODULE << "running `ManualControlpump` task..."
            << std::endl;

  bluetooth_ptr_->executeCmdQueue();
}

// stop waterpump and airpump
void PumpModule::stop() {
	if (running_) {
		running_ = false;
	}
	waterpump_ptr_->stop();
  airpump_ptr_->stop();
}