#include <iostream>
#include "bluetooth.h"

#include <memory>
#include <cstring>
#include <chrono>
#include <thread>
#include "config.h"

// Test only
// #define DEBUG

Bluetooth::Bluetooth(std::string tty) : tty_(tty), cmd_queue_() {
  // initialise, open serial device and get handle
  if ((handle_ = serOpen(&tty_[0], 9600, 0)) < 0) {
    throw std::runtime_error("serial cannot be opened!");
  }
}

Bluetooth::~Bluetooth() { serClose(handle_); }

/*
 * to easily use the gpio library functions, e.g. serRead()
 * the 1st parameter is declared as `char*`, but not a smart ptr
*/
int Bluetooth::recvData(char *data, unsigned int len) const {
  int ret;
  if ((ret = serDataAvailable(handle_)) < len) {
    // read and drop useless bytes
    while (serDataAvailable(handle_)) {
      serReadByte(handle_);
    }
    #ifdef DEBUG
    std::cerr << TAG_BLUETOOTH
              << "received a short command, " 
              << "len " << ret
              << " clear it"
              << std::endl;
    #endif
    // return ret;
  } else {
    #ifdef DEBUG
    if (ret > len) {
      std::cerr << TAG_BLUETOOTH
                << "received a long command, drop rest bytes"
                << std::endl;
    }
    #endif
    // read len bytes
    ret = serRead(handle_, data, len);
    #ifdef DEBUG
    std::cout << "rest len " << serDataAvailable(handle_) << std::endl;
    #endif
    // if ret too long, receive valid len bytes
    while (serDataAvailable(handle_)) {
      // read and drop all rest of bytes
      serReadByte(handle_);
    }
    // return ret;
  }

  return ret;
}

// send equipments running status to mobile 
int Bluetooth::sendData(char *data, unsigned int len) const {
  return serWrite(handle_, data, len);
}

void Bluetooth::executeRecvCmd() {
  std::cout << TAG_BLUETOOTH << "running..." << std::endl;
  // a temp array to save current received cmd
  std::unique_ptr<char[]> data(new char[app_config::CMD_LEN]);
  // default cmd
  std::memcpy(data.get(), app_config::CMD_DEFUALT.c_str(), app_config::CMD_LEN);
  while (true) {
    // default cmd
    std::memcpy(data.get(), app_config::CMD_DEFUALT.c_str(), app_config::CMD_LEN);
    int len = recvData(data.get(), app_config::CMD_LEN);
    // if a enough len cmd; if not continue to get next valid cmd
    if (len >= app_config::CMD_LEN) {
      // len >= CMD_LEN(9), only save CMD_LEN len data
      std::cout << TAG_BLUETOOTH << "current rcv cmd : ";
      for (int i = 0; i < app_config::CMD_LEN; ++i) { std::cout << data[i]; }
      std::cout << std::endl;

      // parse cmd
      char head = data[0];
      char instr = data[1];
      char lvl = data[2];
      char tail = data[8];
      // check received cmd head and tail flag is ok, if not, drop cmd and wait next valid cmd
      if (head != '0' || tail != '0') {
        #ifdef DEBUG
        std::cerr << TAG_BLUETOOTH << "invalid cmd!" << std::endl;
        #endif
        continue;
      }

      // judge cmd type
      Bluetooth::CmdType cmdType(Bluetooth::CmdType::Unknown);
      switch (instr) {
        case '1': {
          // set heater cmd type
          switch (lvl) {
            case '0':
              cmdType = Bluetooth::CmdType::SetHeaterPwmLvl0; 
              break;
            case '1':
              cmdType = Bluetooth::CmdType::SetHeaterPwmLvl1; 
              break;
            case '2':
              cmdType = Bluetooth::CmdType::SetHeaterPwmLvl2; 
              break;
            case '3':
              cmdType = Bluetooth::CmdType::SetHeaterPwmLvl3; 
              break;
            case '4':
              cmdType = Bluetooth::CmdType::SetHeaterPwmLvl4; 
              break;
            default:
              cmdType = Bluetooth::CmdType::Unknown;
              std::cerr << TAG_BLUETOOTH << "unknown lvl: " << lvl << std::endl; 
              break;
          }
        } break;
        case '2': {
          // set airpump cmd type 
          switch (lvl) {
            case '0':
              cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl0; 
              break;
            case '1':
              cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl1; 
              break;
            case '2':
              cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl2; 
              break;
            case '3':
              cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl3; 
              break;
            case '4':
              cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl4; 
              break;
            default:
              cmdType = Bluetooth::CmdType::Unknown;
              std::cerr << TAG_BLUETOOTH << "unknown lvl: " << lvl << std::endl; 
              break;
          }
        } break;
        case '3': {
          // set waterpump cmd type
          switch (lvl) {
            case '0':
              cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl0; 
              break;
            case '1':
              cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl1; 
              break;
            case '2':
              cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl2; 
              break;
            case '3':
              cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl3; 
              break;
            case '4':
              cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl4; 
              break;
            default:
              cmdType = Bluetooth::CmdType::Unknown;
              std::cerr << TAG_BLUETOOTH << "unknown lvl: " << lvl << std::endl; 
              break;
          }
        } break;
        default: {
          std::cerr << TAG_BLUETOOTH << "unknown instr: " << instr << std::endl;
        } break;
      }
      // thread safely push valid cmd intp cmd queue
      if (cmdType != Bluetooth::CmdType::Unknown) {
        cmd_queue_.EnTask(cmdType);
        std::cout << TAG_BLUETOOTH << "successfully receiced cmd: "
                  << static_cast<unsigned int>(cmdType) << "u "
                  << "current cmd number is " << cmd_queue_.size()
                  << std::endl;
        // after many test we think here need a milliseconds dely for stable transport cmd
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
      }
    } else {
      #ifdef DEBUG
      std::cerr << TAG_BLUETOOTH << "failed to recv data!" << std::endl;
      #endif
    }
    // after many test we think here need a milliseconds dely for stable transport cmd
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
}
