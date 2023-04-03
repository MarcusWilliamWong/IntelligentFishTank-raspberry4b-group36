#include <pigpio.h>
#include <iostream>
#include <string>
#include "ds18b20_.h"

int main() {
    // std::string fp = "/sys/bus/w1/devices/28-082220836ef0";
    Thermometer t;
    std::cout << t.get_temp();

    return 0;
}