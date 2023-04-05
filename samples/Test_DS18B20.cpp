#include <pigpio.h>
#include "myds18b20.h"
#include <unistd.h>

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