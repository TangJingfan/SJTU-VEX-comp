#include "robot_config.h"


using namespace vex;

// Competition mode
competition Competition;

// Controller entity
controller Controller;

// Motor setup
motor left_front_motor(PORT10, gearSetting::ratio18_1, false);
motor right_front_motor(PORT6, gearSetting::ratio18_1, true);
motor left_back_motor(PORT19, gearSetting::ratio18_1, false);
motor right_back_motor(PORT13, gearSetting::ratio18_1, true);

// Flywheel
motor flywheel_motor(PORT1, gearSetting::ratio18_1, false);

// Intaker
motor intaker_motor(PORT2, gearSetting::ratio18_1, false);

// Transmitter
motor transmitter_motor(PORT3, gearSetting::ratio18_1, false);

// inertial sensor setup
inertial inertial_sensor(PORT9);

// Brain for feedback
brain Brain;