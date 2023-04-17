/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
#ifndef THERMALMODULE_H_
#define THERMALMODULE_H_

#define TAG_THERMALMODULE "thermalModule : "
// Test only
// #define DEBUG

#include <tuple>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "module.h"
#include "thermometer.h"
#include "pumpModule.h"
#include "heater.h"
#include "bluetooth.h"


// has heater and thermometer objects, and control heater via thermometer
class ThermalModule : public Module {
public:
	ThermalModule();
	~ThermalModule();
	// register bluetooth
	void registerBluetooth(std::shared_ptr<Bluetooth> &bluetooth_ptr);
	// register heater from `Class Thermometer`
  // to add Bluetooth cmd to control Heater, need to regiester heater to bluetooth
  // without breaking the encapsulation of `Class ThermalModule` and `Class PumpModule`
  friend void PumpModule::registerHeaterFromThermalModule(std::shared_ptr<ThermalModule> &thermalModule_ptr);
	void stop() override; // stop module task
	// Callback function
	// automatically according to real-time temperature to control heater open and close
	void executeAutoControlHeater();

private:
	std::unique_ptr<Thermometer> thermometer_ptr_;
	std::shared_ptr<Heater> heater_ptr_;
	std::shared_ptr<Bluetooth> bluetooth_ptr_;
	std::tuple<double, double> tempRange_;
};

#endif