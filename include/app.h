#ifndef APP_H_
#define APP_H_

class App {
public:
  App();
	bool isRunning const();
  ~App();
private:
	bool running_;
};

#endif