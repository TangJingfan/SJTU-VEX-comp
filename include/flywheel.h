#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#include "robot_config.h"

using namespace vex;

double target_voltage;

void maintain_voltage();

void set_voltage(double voltage);

double get_current_voltage();

void stop_flywheel();

#endif