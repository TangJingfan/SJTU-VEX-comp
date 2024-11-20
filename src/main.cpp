#include "movement.h"
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

// Autonomous mode
void autonomous() { Brain.Screen.print("Autonomous Mode"); }

// Driver Control mode
void usercontrol() {
  while (1) {
    // get controller.axis value
    // axis 3 for moving forward and backward
    // axis 4 for turning left and right
    int speed = Controller.Axis3.position();
    int rotation = Controller.Axis4.position();

    // deadzone for improving sensitivity
    const int deadzone = 10;

    // determine what action motor should take
    if (abs(speed) < deadzone && abs(rotation) < deadzone) {
      // within deadzone, no movement
      left_front_motor.stop(brakeType::brake);
      right_front_motor.stop(brakeType::brake);
      left_back_motor.stop(brakeType::brake);
      right_back_motor.stop(brakeType::brake);
    } else {
      // not in deadzone
      if (abs(speed) >= abs(rotation)) {
        // forward or backward
        if (speed > 0) {
          drive_forward(left_front_motor, left_back_motor, right_front_motor,
                        right_back_motor, speed);
        } else {
          drive_backward(left_front_motor, left_back_motor, right_front_motor,
                         right_back_motor, -speed);
        }
      } else {
        // turn left ot right
        if (rotation > 0) {
          turn_right(left_front_motor, left_back_motor, right_front_motor,
                     right_back_motor, rotation);
        } else {
          turn_left(left_front_motor, left_back_motor, right_front_motor,
                    right_back_motor, -rotation);
        }
      }
    }

    // delay 20ms, in order
    vex::task::sleep(20);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  return 0;
}
