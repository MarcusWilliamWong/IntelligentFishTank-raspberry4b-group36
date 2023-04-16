#ifndef PUMPMODULE_H_
#define PUMPMODULE_H_

#include <memory>
#include "bluetooth.h"
#include "waterpump.h"
#include "airpump.h"

// has bluetooth, waterpump and airpump objects, control pumps via bluetooth
class PumpModule {
public:
  PumpModule();
private:
  std::unique_ptr<Bluetooth> bluetooth_ptr_;
  std::unique_ptr<Waterpump> waterpump_ptr_;
  std::unique_ptr<Airpump> airpump_ptr_;
};

#endif