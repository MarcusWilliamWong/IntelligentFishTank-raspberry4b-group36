#include <iostream>
#include <pigpio.h>
#include "app.h"
#include "threadPool.h"
#include "thermalModule.h"

App::App() : pool_() {
  if (gpioInitialise() < 0) {
    std::cout << "Init PIGPIO failed\n";
  } else {
    std::cout << "PIGPIO is ready\n";
  }
}

void App::run() {
  ThermalModule tm(&pool_);
	tm.execute();
}

bool App::isRunning() const{
	return running_;
}

App::~App() {
  // terminate pigpio
  gpioTerminate();
}