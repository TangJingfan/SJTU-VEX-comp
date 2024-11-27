#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "vex.h"

using namespace vex;

extern competition Competition;
extern controller Controller;
extern brain Brain;

extern motor left_front_motor;
extern motor right_front_motor;
extern motor left_back_motor;
extern motor right_back_motor;

extern motor flywheel;

extern motor intaker;

extern inertial inertial_sensor;

#endif