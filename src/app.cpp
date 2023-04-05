#include "app.h"
#include <iostream>
#include <pigpio.h>

App::App() {
  if (gpioInitialise() < 0) {
    std::cout << "Init PIGPIO failed\n";
  } else {
    std::cout << "PIGPIO is ready\n";
  }
}

App::~App() {
  // terminate pigpio
  gpioTerminate();
}