#include <iostream>
#include <pigpio.h>
#include "app.h"

App::App() {
  if (gpioInitialise() < 0) {
    std::cout << "Init PIGPIO failed\n";
  } else {
    std::cout << "PIGPIO is ready\n";
  }
}



bool isRunning() const{
	return this.running;
}

App::~App() {
  // terminate pigpio
  gpioTerminate();
}