#ifndef THERMALMODULE_H_
#define THERMALMODULE_H_
#include "myds18b20.h"

class ThermalModule {
public:
	ThermalModule();
	void execute();

private:
	Thermometer thermometer_;
	Heater heater_;
};

#endif