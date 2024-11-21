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
  // define DEADZONE to ignore small joystick inputs
  const double DEADZONE = 10.0;
  // Threshold for small value
  const double threshold_for_movement = 20.0;
  // voltage const
  const double max_voltage = 12000.0;
  const double min_voltage = 2400.0;

  while (true) {
    // Get controller axis values
    double forward_backward_axis_value = Controller.Axis3.position();
    double left_right_axis_value = Controller.Axis4.position();

    // Scale axis values to motor voltage
    double forward_backward_voltage;
    double left_right_voltage;
    // Scale axis values to motor voltage
    if (forward_backward_axis_value > DEADZONE &&
        forward_backward_axis_value < threshold_for_movement) {
      forward_backward_voltage = min_voltage;
    } else {
      forward_backward_voltage =
          (forward_backward_axis_value * max_voltage) / 100;
    }
    if (left_right_axis_value > DEADZONE &&
        left_right_axis_value < threshold_for_movement) {
      left_right_voltage = min_voltage;
    } else {
      left_right_voltage = (left_right_axis_value * max_voltage) / 100;
    }
    // Check for DEADZONE
    bool within_DEADZONE = abs(forward_backward_axis_value) < DEADZONE &&
                           abs(left_right_axis_value) < DEADZONE;
    // control part
    if (within_DEADZONE) {
      // Stop all motors if within the DEADZONE
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
