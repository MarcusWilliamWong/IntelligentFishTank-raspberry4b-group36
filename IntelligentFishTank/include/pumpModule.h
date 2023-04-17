#ifndef PUMPMODULE_H_
#define PUMPMODULE_H_

// Test only
#define TAG_PUMPMODULE "pumpmodule : "
#define DEBUG_PUMPMODULE

#include <memory>
#include "bluetooth.h"
#include "waterpump.h"
#include "airpump.h"

class ThermalModule;

// has bluetooth, waterpump and airpump objects, control pumps via bluetooth
class PumpModule : public Module {
public:
  // initialise aripump and waterpump object, and register them to bluetooth
  PumpModule();
  ~PumpModule();
	void stop() override; // stop module tasks
  // register bluetooth
  void registerBluetooth(std::shared_ptr<Bluetooth> &bluetooth_ptr);
  // register heater from ThermalModule
  // as friend memeber function of ThermalModule
  void registerHeaterFromThermalModule(std::shared_ptr<ThermalModule> &thermalModule_ptr);
  // Callback function
  // accoring to cmd from bluetooth cmd queue to control pump/heater PWM
  void executeCmdControl();
  
private:
  std::shared_ptr<Bluetooth> bluetooth_ptr_;
  std::shared_ptr<Waterpump> waterpump_ptr_;
  std::shared_ptr<Airpump> airpump_ptr_;
};

#endif