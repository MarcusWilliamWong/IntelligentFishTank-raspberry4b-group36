#include <pigpio.h>
#include "myds18b20.h"
#include <unistd.h>
#include <iostream>

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
  // std::string fp = "/sys/bus/w1/devices/28-082220836ef0";
  Thermometer t;
	auto v = t.get_dev();
	while (true) {
		for (auto x : v) {
			std::cout << x << std::endl;
		}
		getchar();
	}
	
	// ThermoCallback tc;
	// t.registerCallback(&tc);
	// t.start();
	// sleep(10);
	// t.stop();

  return 0;
}