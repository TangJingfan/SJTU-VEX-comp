#include "robot_config.h"


using namespace vex;

// Competition mode
competition Competition;

// Controller entity
controller Controller;

// Motor setup
motor left_front_motor(PORT12, gearSetting::ratio18_1, false);
motor right_front_motor(PORT3, gearSetting::ratio18_1, true);
motor left_back_motor(PORT11, gearSetting::ratio18_1, false);
motor right_back_motor(PORT4, gearSetting::ratio18_1, true);

// Flywheel
motor flywheel_motor(PORT10, gearSetting::ratio18_1, false);

// Intaker
motor intaker_motor(PORT15, gearSetting::ratio18_1, false);

// Transmitter
motor transmitter_motor(PORT16, gearSetting::ratio18_1, false);

// inertial sensor setup
inertial inertial_sensor(PORT5);

// Brain for feedback
brain Brain;