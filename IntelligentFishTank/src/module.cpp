#include "module.h"

Module::Module() : running_(true) {}

bool Module::isRunning() const { return running_; }