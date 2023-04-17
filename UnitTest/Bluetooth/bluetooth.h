#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#define TAG_BLUETOOTH "bluetooth : "

#include <pigpio.h>
#include <string>
#include "taskQueue.hpp"

// use gpio 14(TXD), 15(RXD), 5v, GND
// device file path is "/dev/ttyS0"
class Bluetooth {
public:
  Bluetooth(std::string tty);
  ~Bluetooth();

  // callback function for bluetooth receive cmd task
  void executeRecvCmd();

  /*
   * to easily use the gpio library functions: serRead() etc.
   * the 1st parameter of recvData and sendData is declared as `char*`, but not a smart ptr
  */
  int recvData(char *data, unsigned int len) const;
  // send equipments running status to mobile 
  int sendData(char *data, unsigned int len) const;

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
  std::string tty_;
  // open device file
  int handle_ = -1;
  TaskQueue<CmdType> cmd_queue_;
};

#endif
