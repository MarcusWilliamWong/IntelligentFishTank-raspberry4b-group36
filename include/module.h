/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
#ifndef MODULE_H_
#define MODULE_H_

#define TAG_MODULE "module : "
// Test only
// #define DEBUG_MODULE

#include <atomic>

class Module {
public:
  Module();
  bool isRunning() const;  // check module running status
  virtual void stop() = 0;  // stop all module tasks 

protected:
  std::atomic_bool running_;
};

#endif