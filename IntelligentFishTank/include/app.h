#ifndef APP_H_
#define APP_H_

#include "threadPool.h"

class App {
public:
  App();
	void run();
	bool isRunning() const;
  ~App();
private:
	bool running_;
	ThreadPool pool_;
};

#endif