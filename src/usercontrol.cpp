#include "movement.h"
#include "robot_config.h"
#include "vex.h"

using namespace vex;

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
            forward_backward_voltage = (forward_backward_axis_value * max_voltage) / 100;
        }
        if (left_right_axis_value > DEADZONE &&
            left_right_axis_value < threshold_for_movement) {
            left_right_voltage = min_voltage;
        } else {
            left_right_voltage = (left_right_axis_value * max_voltage) / 100;
        }
        // Check for DEADZONE
        bool within_DEADZONE = fabs(forward_backward_axis_value) < DEADZONE &&
                               fabs(left_right_axis_value) < DEADZONE;
        // control part
        if (within_DEADZONE) {
            // Stop all motors if within the DEADZONE

        } else {
            // Determine movement based on joystick inputs
            if (fabs(forward_backward_axis_value) >= fabs(left_right_axis_value)) {
                // Forward or backward movement
                if (forward_backward_axis_value > 0) {
                    drive_forward_control(forward_backward_voltage);
                } else {
                    drive_backward_control(-forward_backward_voltage);
                }
            } else {
                // Turning movement
                if (left_right_axis_value > 0) {
                    turn_right_control(left_right_voltage);
                } else {
                    turn_left_control(-left_right_voltage);
                }
            }
        }

        // Delay for task scheduler
        vex::task::sleep(20);
    }
}