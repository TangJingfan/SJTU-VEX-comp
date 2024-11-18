#include "vex.h"

using namespace vex;

// competition mode
competition Competition;

// controller entity
controller Controller;

// motor setup
motor left_front_motor(PORT1, gearSetting::ratio18_1, false);
motor right_front_motor(PORT2, gearSetting::ratio18_1, false);
motor left_back_motor(PORT3, gearSetting::ratio18_1, true);
motor right_back_motor(PORT4, gearSetting::ratio18_1, true);

brain Brain;

// Autonomous 模式
void autonomous() { Brain.Screen.print("Autonomous Mode"); }

// Driver Control 模式
void usercontrol() {
  while (1) {
    int speed = Controller.Axis3.position();
    int rotation = Controller.Axis4.position();
    if (speed >= 0) {
      left_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
      right_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
      left_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
      right_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
    }
    vex::task::sleep(20);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  return 0;
}
