#include <iostream>
#include <pigpio.h>
#include <memory>
#include "app.h"
#include "threadPool.h"
#include "thermalModule.h"

#include <unistd.h>

App::App() : pool_ptr_(nullptr), running_(true) {
  init();
}

void App::init() {
  if (gpioInitialise() < 0) {
    std::cout << "Init PIGPIO failed\n";
  } else {
    std::cout << "PIGPIO is ready\n";
  }
  // pool_ptr_.use_count() -> 0;
  pool_ptr_ = std::make_shared<ThreadPool>();
  // pool_ptr_.use_count() -> 1;
  thermalModule_ptr_ = std::make_shared<ThermalModule>(pool_ptr_);
  // std::cout << "pool_ptr " <<pool_ptr_.use_count() << std::endl;
  // pool_ptr_.use_count() -> 2 (include this.pool_ptr_ and thermalModule.pool_ptr_)

  sleep(9); // wait for pigpio initialising
  std::cout << "initialisation completes" <<std::endl;
}

void App::run() {
  // pool_ptr_.use_count() -> 2
  // thermalModule starts working
	thermalModule_ptr_->execute();
  std::cout << "modules have run" << std::endl;
}

bool App::isRunning() const{
	return running_;
}

App::~App() {
  // terminate pigpio
  gpioTerminate();
}