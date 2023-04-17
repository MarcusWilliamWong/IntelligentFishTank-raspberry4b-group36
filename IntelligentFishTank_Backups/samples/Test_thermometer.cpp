#include <pigpio.h>
#include "thermometer.h"
#include <unistd.h>
#include <iostream>
#include "config.h"

// typedef struct ThermoCallback {
// public:
//   void hasTemperature(const std::vector<double> &tempers) {
//     for (const auto &t : tempers) {
//       std::cout << t << " ";
//     }
//     std::cout << '\n';
//   }
// } ThermoCallback;

int main() {
	if (gpioInitialise() < 0) {
    std::cout << "Failed" << std::endl;
  } else {
    std::cout << "PIGPIO is ready" << std::endl;
  }

	{
		Thermometer thermo;
		auto v = thermo.get_dev();

		std::cout << TAG_THERMOMETER << "dev file path" << std::endl;
		for (auto x : v) {
			std::cout << x << std::endl;
		}

		std::shared_ptr<Heater> heater(new Heater(app_config::HEATER_PIN));
		thermo.registerHeater(heater);
		thermo.start();
		auto temps = thermo.get_temps();

		std::cout << TAG_THERMOMETER << "temperatures" << std::endl;
		for (auto t : temps) {
			std::cout << t << std::endl;
		}
	}



	#ifdef DEBUG_OUTDATE
	// ThermoCallback tc;
	// t.registerCallback(&tc);
	// t.start();
	// sleep(10);
	// t.stop();
	#endif

	gpioTerminate();
  return 0;
}