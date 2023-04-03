#include <pigpio.h>
#include <iostream>
#include <string>
#include "myds18b20.h"

int main() {
    // std::string fp = "/sys/bus/w1/devices/28-082220836ef0";
    Thermometer t;
		int i = 0;
		while (i++ < 5) {
			for (auto t : t.get_temp()) {
				std::cout << t;
			}
			std::cout << '\n';
		}
    

    return 0;
}