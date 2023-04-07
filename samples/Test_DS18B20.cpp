#include <pigpio.h>
#include "myds18b20.h"
#include <unistd.h>

typedef struct ThermoCallback {
public:
  void hasTemperature(const std::vector<double> &tempers) {
    for (const auto &t : tempers) {
      std::cout << t << " ";
    }
    std::cout << '\n';
  }
} ThermoCallback;

int main() {
  // std::string fp = "/sys/bus/w1/devices/28-082220836ef0";
  Thermometer t;
	ThermoCallback tc;
	t.registerCallback(&tc);
	t.start();
	sleep(10);
	t.stop();

  return 0;
}