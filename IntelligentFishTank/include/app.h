#ifndef APP_H_
#define APP_H_

#include "threadPool.h"
#include "thermalModule.h" 

class App {
public:
  App();
  ~App();
	void run();  // modules produce task and add them into thread pool
	bool isRunning() const; // check app running status
private:
	std::shared_ptr<ThreadPool> pool_ptr_;
	std::shared_ptr<ThermalModule> thermalModule_ptr_;
	bool running_;

	void init();  // initialise modules and thread pool
};

#endif