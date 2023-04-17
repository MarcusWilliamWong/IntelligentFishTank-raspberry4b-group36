#ifndef APP_H_
#define APP_H_
#define TAG_APP "app : "

#include <queue>
#include "threadPool.h"
// #include "bluetooth.h"
#include "taskQueue.hpp"
// #include "waterpump.h"
// #include "thermalModule.h"
// #include "pumpModule.h"



// program entry class, has modules objects, and initialise/terminate `pigpio` lib
class App {
public:
  App();
  ~App();  // terminate pigpio
	// void run();  // modules produce tasks and add them into thread pool; sleep main thread if running
	bool isRunning() const; // check app running status

	
	void runWaterpump();
private:
	std::unique_ptr<ThreadPool> pool_ptr_;
	// TaskQueue<Bluetooth::CmdType> cmd_queue_;  // default save 80 cmd
	// mutable std::mutex cmd_mtx_;
	// std::condition_variable cmd_cv_;
	// std::queue<Bluetooth::CmdType> cmd_queue_;
	std::unique_ptr<Bluetooth> bluetooth_ptr_;
	std::unique_ptr<Waterpump> waterpump_ptr_;

	void run();  // // add tasks to threadpool; for lambda expression catch private member

	// std::unique_ptr<ThermalModule> thermalModule_ptr_;
	// std::unique_ptr<PumpModule> pumpModule_ptr_;
	bool running_;

	
};

#endif