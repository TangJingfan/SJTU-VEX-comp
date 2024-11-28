#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include "vex.h"

const int MAXMOTOR_VOL=12000;             //set max voltage for motor is 12000mv




using namespace vex;

extern competition Competition;
extern controller Controller;
extern brain Brain;

extern motor left_front_motor;
extern motor right_front_motor;
extern motor left_back_motor;
extern motor right_back_motor;

extern motor flywheel_motor;

extern motor intaker_motor;

extern inertial inertial_sensor;

#endif