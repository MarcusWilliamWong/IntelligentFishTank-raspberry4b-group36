#include <iostream>
#include <memory>
#include <cstring>
#include <chrono>
#include <thread>
#include "heater.h"
#include "taskQueue.hpp"
#include "bluetooth.h"
#include "config.h"

// #include <stdlib.h>

// Test only
#define DEBUG_THREADTASK

Bluetooth::Bluetooth(std::string tty) : running_(true), tty_(tty), cmd_queue_() {
  // initialise, open serial device and get handle
  if ((handle_ = serOpen(&tty_[0], 9600, 0)) < 0) {
    throw std::runtime_error("serial cannot be opened!");
  }
}

Bluetooth::~Bluetooth() {
  if (running_) {
    this->stop();
  } 
}

void Bluetooth::stop() {
  if (running_) {
    running_ = false;
  }
  serClose(handle_);
}

//register heater
void Bluetooth::registerHeater(std::shared_ptr<Heater> &heater_ptr) {
  heater_ptr_ = heater_ptr;
}

// register airpump
void Bluetooth::registerAirpump(std::shared_ptr<Airpump> &airpump_ptr) {
  airpump_ptr_ = airpump_ptr;
}
// register waterpump
void Bluetooth::registerWaterpump(std::shared_ptr<Waterpump> &waterpump_ptr) {
  waterpump_ptr_ = waterpump_ptr;
}

// Callback function, get and run a cmd from bluetooth cmd queue
void Bluetooth::executeCmdQueue() {
  std::cout << TAG_BLUETOOTH << "running `CmdQueue` task..." << std::endl;

  while (running_) {
    // get one task from cmd queue
    Bluetooth::CmdType cmd{Bluetooth::CmdType::Unknown};
    cmd_queue_.DeTask(cmd);

    std::cout << TAG_WATERPUMP
              << "Execute cmd : " << static_cast<unsigned int>(cmd)
              << std::endl;

    switch (cmd) {
      // cmd to control heater
      case Bluetooth::CmdType::SetHeaterPwmLvl0:
        heater_ptr_->set('0');
        break;
      case Bluetooth::CmdType::SetHeaterPwmLvl1:
        heater_ptr_->set('1');
        break;
      case Bluetooth::CmdType::SetHeaterPwmLvl2:
        heater_ptr_->set('2');
        break;
      case Bluetooth::CmdType::SetHeaterPwmLvl3:
        heater_ptr_->set('3');
        break;
      case Bluetooth::CmdType::SetHeaterPwmLvl4:
        heater_ptr_->set('4');
        break;
      // cmd to control airpump
      case Bluetooth::CmdType::SetAirpumpPwmLvl0:
        airpump_ptr_->set('0');
        break;
      case Bluetooth::CmdType::SetAirpumpPwmLvl1:
        airpump_ptr_->set('1');
        break;
      case Bluetooth::CmdType::SetAirpumpPwmLvl2:
        airpump_ptr_->set('2');
        break;
      case Bluetooth::CmdType::SetAirpumpPwmLvl3:
        airpump_ptr_->set('3');
        break;
      case Bluetooth::CmdType::SetAirpumpPwmLvl4:
        airpump_ptr_->set('4');
        break;
      // cmd to control waterpump
      case Bluetooth::CmdType::SetWaterpumpPwmLvl0:
        waterpump_ptr_->set('0');
        break;
      case Bluetooth::CmdType::SetWaterpumpPwmLvl1:
        waterpump_ptr_->set('1');
        break;
      case Bluetooth::CmdType::SetWaterpumpPwmLvl2:
        waterpump_ptr_->set('2');
        break;
      case Bluetooth::CmdType::SetWaterpumpPwmLvl3:
        waterpump_ptr_->set('3');
        break;
      case Bluetooth::CmdType::SetWaterpumpPwmLvl4:
        waterpump_ptr_->set('4');
        break;
      default:
        std::cerr << TAG_BLUETOOTH
                  << "unknown cmd: " << static_cast<unsigned int>(cmd)
                  << " from cmd queue!"
                  << std::endl;
        break;
    }
  }
}

/*
 * to easily use the gpio library functions, e.g. serRead()
 * the 1st parameter is declared as `char*`, but not a smart ptr
*/
int Bluetooth::recvData(char *data, unsigned int len) const {
  int ret = 0 ;
  while (serDataAvailable(handle_) < len);
  ret = serRead(handle_, data, len);
  return ret;

  #ifdef DEBUG_OLD
  /*
  // after many test we think here need a milliseconds dely for transporting a complete cmd
  std::this_thread::sleep_for(std::chrono::milliseconds(25));
  // just wait for avaliable data
  // while (!serDataAvailable(handle_)) {}
  if ((ret = serDataAvailable(handle_)) < len) {
    // read and drop useless bytes
    while (serDataAvailable(handle_)) {
      serReadByte(handle_);
    }
    #ifdef DEBUG_BLUETOOTH
    std::cerr << TAG_BLUETOOTH
              << "received a short command, " 
              << "len " << ret
              << " clear it"
              << std::endl;
    #endif
  } else {
    #ifdef DEBUG_BLUETOOTH
    if (ret > len) {
      std::cerr << TAG_BLUETOOTH
                << "received a long command, drop rest bytes"
                << std::endl;
    }
    #endif
    int rest_len = ret - serDataAvailable(handle_);
    // read len bytes
    ret = serRead(handle_, data, len);
    #ifdef DEBUG_THREADTASK
    std::cout << "rest len -> " << serDataAvailable(handle_)
              << ", compute len -> " << rest_len << std::endl;
    #endif
    // if ret too long, receive valid len bytes
    for (int i = 0; i < rest_len; ++i) {
      // read and drop all rest of bytes
      serReadByte(handle_);
    }
    // #ifdef DEBUG_THREADTASK
    // std::cout << TAG_BLUETOOTH << "recvData here, cmd len->" << ret << std::endl;
    // // getchar();
    // #endif
  }
  */
  return ret;
  #endif
}

// send equipments running status to mobile 
int Bluetooth::sendData(char *data, unsigned int len) const {
  return serWrite(handle_, data, len);
}

// callback function, receive cmd from mobile via bluetooth(HC06)
// save cmd into cmd queue
void Bluetooth::executeRecvCmd() {
  std::cout << TAG_BLUETOOTH << "running `RecvCmd` task..." << std::endl;
  
  // a temp array to save current received cmd
  std::unique_ptr<char[]> data(new char[app_config::CMD_LEN]);
  // default cmd
  std::memcpy(data.get(), app_config::CMD_DEFUALT.c_str(), app_config::CMD_LEN);
  while (running_) {
    // default cmd
    std::memcpy(data.get(), app_config::CMD_DEFUALT.c_str(), app_config::CMD_LEN);
    int len = recvData(data.get(), app_config::CMD_LEN);
    // if a enough len cmd; if not continue to get next valid cmd
    if (len >= app_config::CMD_LEN) {
      // len >= CMD_LEN(9), only save CMD_LEN len data
      std::cout << TAG_BLUETOOTH << "current rcv cmd : ";
      for (int i = 0; i < app_config::CMD_LEN; ++i) { std::cout << data[i]; }
      std::cout << std::endl;

      // CMD format: single CMD includes 9 ASCII char
      // you can personalised your private Bluetooth CMD
      // head bit[0] & tail bit[8] are check bits
      // instruction bit is at [1] ->
      // when [1] = '1', means set Heater PWM as (0-4 level);
      // when [1] = '2', means set Airpump PWM as (0-4 level);
      // when [1] = '3', means set Waterpump PWM as (0-4 level);
      // when [1] belongs to {1, 2, 3}, bit [2] means PWM level from '0'-'4', 
      //          if more than '4' means unvalid cmd
      // In `Class PwmController`, there is `enum class PwmLevel`

      // when [1] = '4', bits [2],[3],[4], means a two-digits in decimal with one decimal digit
      // bits [5], [6], [7], as well.

      // CMD e.g. 012000000 -> set heater PWM as level2
      // CMD e.g. 024000000 -> set airpump PWM as level4
      // CMD e.g. 042642750 -> set temperature range from 26.4 °C to 27.5 °C
      
      // parse cmd
      char head = data[0];
      char instr = data[1];
      char lvl = data[2];
      char tail = data[8];
      // check received cmd head and tail flag is ok, if not, drop cmd and wait next valid cmd
      if (head != '0' || tail != '0') {
        #ifdef DEBUG_BLUETOOTH
        std::cerr << TAG_BLUETOOTH << "invalid cmd!" << std::endl;
        #endif
        continue;
      }
      // if (data[1] == 'g' && data[2] == 'o' && data[3] == 'o' 
      // && data[4] == 'd' && data[5] == 'b' && data[6] == 'y' && data[7] == 'e') { exit(0); }

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
        case '4': {
          // char to int
          auto char2Int = [](char c)->int{ return (c - '0'); };
          int min = char2Int(data[2]) * 100 + char2Int(data[3]) * 10 + char2Int(data[4]);
          int max = char2Int(data[5]) * 100 + char2Int(data[6]) * 10 + char2Int(data[7]);
          // call heater setMinMaxLimit
          heater_ptr_->setMinMaxLimit(min, max);
        } break;
        default: {
          std::cerr << TAG_BLUETOOTH << "unknown instr: " << instr << std::endl;
        } break;
      }
      // thread safely push valid cmd intp cmd queue
      if (Bluetooth::CmdType::Unknown != cmdType) {
        cmd_queue_.EnTask(cmdType);
        std::cout << TAG_BLUETOOTH << "successfully receiced cmd -> "
                  << static_cast<unsigned int>(cmdType) << "u" << std::endl;
        std::cout << TAG_BLUETOOTH << "current cmd number is " << cmd_queue_.size()
                  << std::endl;
      }
    } else {
      #ifdef DEBUG_BLUETOOTH
      std::cerr << TAG_BLUETOOTH << "failed to recv data!" << std::endl;
      #endif
    }
  }
}
