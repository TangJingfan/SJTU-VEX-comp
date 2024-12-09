#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#include "robot_config.h"

using namespace vex;
void updateFlywheel();

double getFlyWheelSpeed();
void setFlyWheelSpeed(double speed);

void calcFlyWheelSpeed();

double get_current_voltage();

void stop_flywheel();

#endif