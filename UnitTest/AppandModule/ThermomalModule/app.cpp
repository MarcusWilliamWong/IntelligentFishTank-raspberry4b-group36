#include <pigpio.h>
#include <cstring>
#include "app.h"
#include "config.h"


// #define DEBUG

// initialise threadpool, modules and bluetooth
App::App() : pool_ptr_(new ThreadPool()) {
  if (gpioInitialise() < 0) {
    throw std::runtime_error("failed to init PIGPIO!");
  }
  // thermalModule_ptr_.reset(new ThermalModule());
  // pumpModule_ptr_.reset(new PumpModule());
  bluetooth_ptr_.reset(new Bluetooth(app_config::BLUETOOTH_DEV_PATH));
  waterpump_ptr_.reset(new );

  run();
}

// add tasks to threadpool
void App::run() {
  if (!running_) {
    running_ = true;
    std::cout << TAG_APP << "running..." << std::endl;

    // add tasks into thraed pool
    pool_ptr_->AddTask([this]{ this->bluetooth_ptr_->executeRecvCmd(); });
    // pool_ptr_->AddTask([this]{ });

    // main thread do nothing just sleep
    while(true) {
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  } else {
    std::cerr << TAG_APP << "already running!" << std::endl;
  }
}

// // run bluetooth receive cmd thread task
// void App::runBluetooth() {
//   std::cout << TAG_BLUETOOTH << "running..." << std::endl;
//   // a temp array to save current received cmd
//   std::unique_ptr<char[]> data(new char[app_config::CMD_LEN]);
//   // default cmd
//   std::memcpy(data.get(), app_config::CMD_DEFUALT.c_str(), app_config::CMD_LEN);
//   while (true) {
//     // default cmd
//     std::memcpy(data.get(), app_config::CMD_DEFUALT.c_str(), app_config::CMD_LEN);
//     int len = bluetooth_ptr_->recvData(data.get(), app_config::CMD_LEN);
//     // if a enough len cmd; if not continue to get next valid cmd
//     if (len >= app_config::CMD_LEN) {
//       // len >= CMD_LEN(9), only save CMD_LEN len data
//       std::cout << TAG_BLUETOOTH << "current rcv cmd : ";
//       for (int i = 0; i < app_config::CMD_LEN; ++i) { std::cout << data[i]; }
//       std::cout << std::endl;

//       // parse cmd
//       char head = data[0];
//       char instr = data[1];
//       char lvl = data[2];
//       char tail = data[8];
//       // check received cmd head and tail flag is ok, if not, drop cmd and wait next valid cmd
//       if (head != '0' || tail != '0') {
//         #ifdef DEBUG
//         std::cerr << TAG_BLUETOOTH << "invalid cmd!" << std::endl;
//         #endif
//         continue;
//       }

//       // judge cmd type
//       Bluetooth::CmdType cmdType(Bluetooth::CmdType::Unknown);
//       switch (instr) {
//         case '1': {
//           // set heater cmd type
//           switch (lvl) {
//             case '0':
//               cmdType = Bluetooth::CmdType::SetHeaterPwmLvl0; 
//               break;
//             case '1':
//               cmdType = Bluetooth::CmdType::SetHeaterPwmLvl1; 
//               break;
//             case '2':
//               cmdType = Bluetooth::CmdType::SetHeaterPwmLvl2; 
//               break;
//             case '3':
//               cmdType = Bluetooth::CmdType::SetHeaterPwmLvl3; 
//               break;
//             case '4':
//               cmdType = Bluetooth::CmdType::SetHeaterPwmLvl4; 
//               break;
//             default:
//               cmdType = Bluetooth::CmdType::Unknown;
//               std::cerr << TAG_BLUETOOTH << "unknown lvl: " << lvl << std::endl; 
//               break;
//           }
//         } break;
//         case '2': {
//           // set airpump cmd type 
//           switch (lvl) {
//             case '0':
//               cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl0; 
//               break;
//             case '1':
//               cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl1; 
//               break;
//             case '2':
//               cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl2; 
//               break;
//             case '3':
//               cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl3; 
//               break;
//             case '4':
//               cmdType = Bluetooth::CmdType::SetAirpumpPwmLvl4; 
//               break;
//             default:
//               cmdType = Bluetooth::CmdType::Unknown;
//               std::cerr << TAG_BLUETOOTH << "unknown lvl: " << lvl << std::endl; 
//               break;
//           }
//         } break;
//         case '3': {
//           // set waterpump cmd type
//           switch (lvl) {
//             case '0':
//               cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl0; 
//               break;
//             case '1':
//               cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl1; 
//               break;
//             case '2':
//               cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl2; 
//               break;
//             case '3':
//               cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl3; 
//               break;
//             case '4':
//               cmdType = Bluetooth::CmdType::SetWaterpumpPwmLvl4; 
//               break;
//             default:
//               cmdType = Bluetooth::CmdType::Unknown;
//               std::cerr << TAG_BLUETOOTH << "unknown lvl: " << lvl << std::endl; 
//               break;
//           }
//         } break;
//         default: {
//           std::cerr << TAG_BLUETOOTH << "unknown instr: " << instr << std::endl;
//         } break;
//       }
//       // thread safely push valid cmd intp cmd queue
//       if (cmdType != Bluetooth::CmdType::Unknown) {
//         cmd_queue_.EnTask(cmdType);
//         std::cout << TAG_BLUETOOTH << "successfully receiced cmd: "
//                   << static_cast<unsigned int>(cmdType) << "u "
//                   << "current cmd number is " << cmd_queue_.size()
//                   << std::endl;
//         // after many test we think here need a milliseconds dely for stable transport cmd
//         std::this_thread::sleep_for(std::chrono::milliseconds(20));
//       }
//     } else {
//       #ifdef DEBUG
//       std::cerr << TAG_BLUETOOTH << "failed to recv data!" << std::endl;
//       #endif
//     }
//     // after many test we think here need a milliseconds dely for stable transport cmd
//     std::this_thread::sleep_for(std::chrono::milliseconds(20));
//   }
// }

/*
void App::runWaterpump() {
  std::cout << TAG_WATERPUMP << "running..." << std::endl;
    while (true) {
        std::unique_lock<std::mutex> lock(this->cmd_mut_);
        while (this->cmd_que_.empty()) {
            this->cmd_cond_.wait(lock);
        }
        CmdType cmd(this->cmd_que_.front());
        this->cmd_que_.pop();
        std::cout << TAG_WATERPUMP
                  << "received cmd: " << static_cast<unsigned int>(cmd)
                  << std::endl;

        bool valid_cmd(true);
        switch (cmd) {
        case CmdType::SetWaterPumpLvl0:
            this->waterpump_->setPwmLevel(0);
            break;
        case CmdType::SetWaterPumpLvl1:
            this->waterpump_->setPwmLevel(1);
            break;
        case CmdType::SetWaterPumpLvl2:
            this->waterpump_->setPwmLevel(2);
            break;
        case CmdType::SetWaterPumpLvl3:
            this->waterpump_->setPwmLevel(3);
            break;
        case CmdType::SetWaterPumpLvl4:
            this->waterpump_->setPwmLevel(4);
            break;
        default:
            valid_cmd = false;
            std::cerr << TAG_WATERPUMP
                      << "unknown cmd: " << static_cast<unsigned int>(cmd)
                      << std::endl;
            break;
        }
        if (valid_cmd) {
            this->waterpump_->set();
        }
    }
}*/


// check app running status
bool App::isRunning() const { return running_; }

// terminate pigpio
App::~App() {
  gpioTerminate();
}

