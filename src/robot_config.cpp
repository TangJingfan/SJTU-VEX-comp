#include "robot_config.h"


using namespace vex;

// Competition mode
competition Competition;

// Controller entity
controller Controller;

// Motor setup
motor left_front_motor(PORT17, gearSetting::ratio18_1, false);
motor right_front_motor(PORT18, gearSetting::ratio18_1, true);
motor left_back_motor(PORT4, gearSetting::ratio18_1, false);
motor right_back_motor(PORT9, gearSetting::ratio18_1, true);

// Flywheel
motor flywheel_motor(PORT7, gearSetting::ratio18_1, true);

// Intaker
motor intaker_motor(PORT20, gearSetting::ratio18_1, false);

// Transmitter
motor transmitter_motor(PORT10, gearSetting::ratio18_1, false);

// inertial sensor setup
inertial inertial_sensor(PORT11);

// Brain for feedback
brain Brain;