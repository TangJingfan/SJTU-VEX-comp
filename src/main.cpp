#include "movement.h"
#include "vex.h"

using namespace vex;

// Competition mode
competition Competition;

// Controller entity
controller Controller;

// Motor setup
motor left_front_motor(PORT1, gearSetting::ratio18_1, false);
motor right_front_motor(PORT2, gearSetting::ratio18_1, true);
motor left_back_motor(PORT3, gearSetting::ratio18_1, false);
motor right_back_motor(PORT4, gearSetting::ratio18_1, true);

// Brain for feedback
brain Brain;

// Autonomous mode
void autonomous() {
  Brain.Screen.print("Autonomous Mode");

  // Example autonomous sequence
  drive_forward(left_front_motor, left_back_motor, right_front_motor,
                right_back_motor, 6000);
  task::sleep(2000);
  // Drive forward for 2 seconds

  drive_backward(left_front_motor, left_back_motor, right_front_motor,
                 right_back_motor, 6000);
  task::sleep(2000);
  // Drive backward for 2 seconds

  Brain.Screen.print("Autonomous complete");
}

// Driver Control mode
void usercontrol() {
  const int deadzone = 10; // Define deadzone to ignore small joystick inputs

  while (true) {
    // Get controller axis values
    int forward_backward_axis_value = Controller.Axis3.position();
    int left_right_axis_value = Controller.Axis4.position();

    // Scale axis values to motor voltage
    int forward_backward_voltage = (forward_backward_axis_value * 12000) / 100;
    int left_right_voltage = (left_right_axis_value * 12000) / 100;

    // Check for deadzone
    bool within_deadzone = abs(forward_backward_axis_value) < deadzone &&
                           abs(left_right_axis_value) < deadzone;

    if (within_deadzone) {
      // Stop all motors if within the deadzone
      left_front_motor.stop(brakeType::brake);
      right_front_motor.stop(brakeType::brake);
      left_back_motor.stop(brakeType::brake);
      right_back_motor.stop(brakeType::brake);
    } else {
      // Determine movement based on joystick inputs
      if (abs(forward_backward_axis_value) >= abs(left_right_axis_value)) {
        // Forward or backward movement
        if (forward_backward_axis_value > 0) {
          drive_forward(left_front_motor, left_back_motor, right_front_motor,
                        right_back_motor, forward_backward_voltage);
        } else {
          drive_backward(left_front_motor, left_back_motor, right_front_motor,
                         right_back_motor, -forward_backward_voltage);
        }
      } else {
        // Turning movement
        if (left_right_axis_value > 0) {
          turn_right(left_front_motor, left_back_motor, right_front_motor,
                     right_back_motor, left_right_voltage);
        } else {
          turn_left(left_front_motor, left_back_motor, right_front_motor,
                    right_back_motor, -left_right_voltage);
        }
      }
    }

    // Delay for task scheduler
    vex::task::sleep(20);
  }
}

int main() {
  // Set up competition callbacks
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting
  while (true) {
    task::sleep(100);
  }
}
