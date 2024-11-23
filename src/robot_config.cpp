#include "robot_config.h"
#include "vex.h"

using namespace vex;

// competition mode
competition Competition;

// controller entity
controller Controller;

// motor setup
motor left_front_motor(PORT1, gearSetting::ratio18_1, false);
motor right_front_motor(PORT2, gearSetting::ratio18_1, true);
motor left_back_motor(PORT3, gearSetting::ratio18_1, false);
motor right_back_motor(PORT4, gearSetting::ratio18_1, true);

brain Brain;