#include <pigpio.h>
#include <iostream>
#include <unistd.h>

int main() {
  if (gpioInitialise() < 0) {
    std::cout << "Init PIGPIO failed\n";
  } else {
    std::cout << "PIGPIO is ready\n";
  }
  sleep(4);
  // terminate pigpio
  gpioTerminate();
}