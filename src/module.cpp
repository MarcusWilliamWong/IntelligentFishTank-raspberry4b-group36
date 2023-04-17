/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
#include "module.h"

Module::Module() : running_(true) {}

bool Module::isRunning() const { return running_; }