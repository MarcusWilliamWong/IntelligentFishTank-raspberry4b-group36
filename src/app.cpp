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



bool isRun() const{
	return this.running;
}

App::~App() {
  // terminate pigpio
  gpioTerminate();
}