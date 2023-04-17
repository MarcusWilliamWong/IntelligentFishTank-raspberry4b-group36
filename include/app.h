/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
#ifndef APP_H_
#define APP_H_

#define TAG_APP "app : "
// Test only
// #define DEBUG_APP

#include "threadPool.h"
#include "bluetooth.h"
#include "taskQueue.hpp"
#include "thermalModule.h"
#include "pumpModule.h"

// program entry class, has modules objects, and initialise/terminate `pigpio` lib
class App {
public:
  App();
  ~App();  // terminate pigpio
	void run();  // run sleep main thread if running
	bool isRunning() const; // check app running status

private:
	std::unique_ptr<ThreadPool> pool_ptr_;
	std::shared_ptr<Bluetooth> bluetooth_ptr_;
	std::shared_ptr<ThermalModule> thermalModule_ptr_;
	std::unique_ptr<PumpModule> pumpModule_ptr_;
	// modules produce tasks and add them into thread pool;
	// for lambda expression catch `App` private members
	void AddModuleTasks();
	bool running_ = false;;
};

#endif