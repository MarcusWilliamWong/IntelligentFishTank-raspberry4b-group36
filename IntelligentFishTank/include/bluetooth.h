#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#define TAG_BLUETOOTH "bluetooth : "

// Test only
// #define DEBUG_BLUETOOTH

#include <pigpio.h>
#include <string>
#include <atomic>
#include "airpump.h"
#include "waterpump.h"
#include "taskQueue.hpp"

// use gpio 14(TXD), 15(RXD), 5v, GND
// device file path is "/dev/ttyS0"
class Bluetooth {
public:
  Bluetooth(std::string tty);
  ~Bluetooth();
  // register airpump
  void registerAirpump(std::shared_ptr<Airpump> &airpump_ptr);
  // register waterpump
	void registerWaterpump(std::shared_ptr<Waterpump> &waterpump_ptr);
  // Callback function for bluetooth receive cmd task
  void executeRecvCmd();
  // Callback function, execute bluetooth cmd queue
  void executeCmdQueue();
  /*
   * to easily use the gpio library functions: serRead() etc.
   * the 1st parameter of recvData and sendData is declared as `char*`, but not a smart ptr
  */
  int recvData(char *data, unsigned int len) const;
  // send equipments running status to mobile 
  int sendData(char *data, unsigned int len) const;

  void stop();
  // defien cmdtype
  enum class CmdType : unsigned int {
    Unknown,
    // set heater level
    SetHeaterPwmLvl0,
    SetHeaterPwmLvl1,
    SetHeaterPwmLvl2,
    SetHeaterPwmLvl3,
    SetHeaterPwmLvl4,
    // set airpump level
    SetAirpumpPwmLvl0,
    SetAirpumpPwmLvl1,
    SetAirpumpPwmLvl2,
    SetAirpumpPwmLvl3,
    SetAirpumpPwmLvl4,
    // set waterpump level
    SetWaterpumpPwmLvl0,
    SetWaterpumpPwmLvl1,
    SetWaterpumpPwmLvl2,
    SetWaterpumpPwmLvl3,
    SetWaterpumpPwmLvl4,
  };

private:
  std::atomic_bool running_;
  std::string tty_;
  // open device file
  int handle_ = -1;
  TaskQueue<CmdType> cmd_queue_;
  std::shared_ptr<Airpump> airpump_ptr_;
  std::shared_ptr<Waterpump> waterpump_ptr_;
};

#endif
