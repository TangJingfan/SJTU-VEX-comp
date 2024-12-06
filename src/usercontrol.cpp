#include "usercontrol.h"

using namespace vex;


void usercontrol() {

    // define DEADZONE to ignore small joystick inputs
    const double DEADZONE = 10.0;
    // Threshold for small value
    const double threshold_for_movement = 20.0;
    // voltage const
    const double max_voltage = 6000.0;
    const double min_voltage = 2400.0;

    while (true) {
        // Get controller axis values(intaker as head)
        double forward_backward_axis_value_1 = Controller.Axis3.position();
        double left_right_axis_value_1 = Controller.Axis4.position();
        // Get controller axis values(lifter as head)
        double forward_backward_axis_value_2 = Controller.Axis2.position();
        double left_right_axis_value_2 = Controller.Axis1.position();


        // Get button information
        bool whether_shoot = Controller.ButtonL1.pressing();
        bool whether_intake = Controller.ButtonR1.pressing();

        // Scale axis values to motor voltage
        double forward_backward_voltage;
        double left_right_voltage;
        // Scale axis values to motor voltage
        if ((forward_backward_axis_value_1 > DEADZONE &&
            forward_backward_axis_value_1 < threshold_for_movement) 
            && !(forward_backward_axis_value_2 > DEADZONE &&
            forward_backward_axis_value_2 < threshold_for_movement)) {
            forward_backward_voltage = min_voltage;
        } else {
            forward_backward_voltage = (forward_backward_axis_value_1 * max_voltage) / 100;
        }
        if (left_right_axis_value_1 > DEADZONE &&
            left_right_axis_value_1 < threshold_for_movement) {
            left_right_voltage = min_voltage;
        } else {
            left_right_voltage = (left_right_axis_value_1 * max_voltage) / 100;
        }
        if (forward_backward_axis_value_2 > DEADZONE &&
            forward_backward_axis_value_2 < threshold_for_movement) {
            forward_backward_voltage = min_voltage;
        } else {
            forward_backward_voltage = (forward_backward_axis_value_2 * max_voltage) / 100;
        }
        if (left_right_axis_value_2 > DEADZONE &&
            left_right_axis_value_2 < threshold_for_movement) {
            left_right_voltage = min_voltage;
        } else {
            left_right_voltage = (left_right_axis_value_2 * max_voltage) / 100;
        }


        // Check for DEADZONE
        bool within_DEADZONE_1 = fabs(forward_backward_axis_value_1) < DEADZONE &&
                               fabs(left_right_axis_value_1) < DEADZONE;
        // control part
        if (within_DEADZONE_1) {
            // Stop all motors if within the DEADZONE
            stop(coast);
        } else {
            // Determine movement based on joystick inputs
            if (fabs(forward_backward_axis_value_1) >= fabs(left_right_axis_value_1)) {
                // Forward or backward movement
                if (forward_backward_axis_value_1 > 0) {
                    drive_forward_control(forward_backward_voltage);
                } else {
                    drive_backward_control(-forward_backward_voltage);
                }
            } else {
                // Turning movement
                if (left_right_axis_value_1 > 0) {
                    turn_right_control(left_right_voltage);
                } else {
                    turn_left_control(-left_right_voltage);
                }
            }
        }


        // Check for DEADZONE
        bool within_DEADZONE_2 = fabs(forward_backward_axis_value_2) < DEADZONE &&
                               fabs(left_right_axis_value_2) < DEADZONE;
        // control part
        if (within_DEADZONE_2) {
            // Stop all motors if within the DEADZONE
            stop(coast);
        } else {
            // Determine movement based on joystick inputs
            if (fabs(forward_backward_axis_value_2) >= fabs(left_right_axis_value_2)) {
                // Forward or backward movement
                if (forward_backward_axis_value_2 > 0) {
                    drive_backward_control(forward_backward_voltage);
                } else {
                    drive_forward_control(-forward_backward_voltage);
                }
            } else {
                // Turning movement
                if (left_right_axis_value_2 > 0) {
                    turn_right_control(left_right_voltage);
                } else {
                    turn_left_control(-left_right_voltage);
                }
            }
        }







        // intake (keep pressing R1 button)
        if (whether_intake) {
            intake(MAXMOTOR_VOL);
            transmit(MAXMOTOR_VOL);
        } else {
            stop_intake();
            stop_transmit();
        }

        // shoot (keep pressing L1 button)
        if (whether_shoot) {
            flywheel.set_target_voltage(MAXMOTOR_VOL);
        } else {
            // flywheel.stop();
            flywheel.set_target_voltage(0);
        }

        // Delay for task scheduler
        vex::task::sleep(20);
    }
}