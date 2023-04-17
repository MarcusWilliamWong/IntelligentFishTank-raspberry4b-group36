#include <pigpio.h>
#include <cstring>
#include <stdexcept>
#include "app.h"
#include "config.h"

// initialise threadpool, modules and bluetooth
App::App() : pool_ptr_(new ThreadPool()) {
  if (gpioInitialise() < 0) {
    throw std::runtime_error("failed to init PIGPIO!");
  }
  bluetooth_ptr_.reset(new Bluetooth(app_config::BLUETOOTH_DEV_PATH));
  thermalModule_ptr_.reset(new ThermalModule());
  pumpModule_ptr_.reset(new PumpModule());
  pumpModule_ptr_->registerBluetooth(bluetooth_ptr_);
  pumpModule_ptr_->registerHeaterFromThermalModule(thermalModule_ptr_);
}

void App::run() {
  if (!running_) {
    running_ = true;
    std::cout << TAG_APP << "running..." << std::endl;
    // add module tasks into thraed pool
    AddModuleTasks();
    // main thread do nothing just sleep
    while(running_) {
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  } else {
    std::cerr << TAG_APP << "already running!" << std::endl;
  }
}

// check app running status
bool App::isRunning() const { return running_; }

// stop all equipment and terminate pigpio lib
App::~App() {
  thermalModule_ptr_->stop();
  pumpModule_ptr_->stop();
  bluetooth_ptr_->stop();
  gpioTerminate();
}

// add module tasks into thraed pool
void App::AddModuleTasks() {
  // task from 
  pool_ptr_->AddTask([this]{ this->bluetooth_ptr_->executeRecvCmd(); });
  // task from pumpModule
  pool_ptr_->AddTask([this]{ this->pumpModule_ptr_->executeCmdControl(); });
  // task from thermalModule
  pool_ptr_->AddTask([this]{ this->thermalModule_ptr_->executeAutoControlHeater(); });
}

