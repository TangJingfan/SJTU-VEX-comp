#include "usercontrol.h"
#include "flywheel.h"
#include <iostream>

using namespace vex;

void usercontrol() {

  // define DEADZONE to ignore small joystick inputs
  const double DEADZONE = 10.0;
  // Threshold for small value
  const double threshold_for_movement = 20.0;
  // voltage const
  const double max_voltage = 8000.0;
  const double max_voltage_turn=4000.0;
  const double min_voltage = 2400.0;

  while (true) {
    // Get controller axis values(intaker as head)
    double forward_backward_axis_value_fwd = Controller.Axis3.position();
    double left_right_axis_value_fwd = Controller.Axis4.position();
    // Get controller axis values(lifter as head)
    double forward_backward_axis_value_rev = Controller.Axis2.position();
    double left_right_axis_value_rev = Controller.Axis1.position();

    // Get button information
    bool whether_transmitter_reverse = Controller.ButtonL1.pressing();
    bool whether_flywheel   =Controller.ButtonL2.pressing();
    bool whether_intake = Controller.ButtonR1.pressing();
    bool whether_rev = Controller.ButtonR2.pressing();
    // Scale axis values to motor voltage
    double forward_backward_voltage = 0;
    double left_right_voltage = 0;
    // Scale axis values to motor voltage

    if (!whether_rev) {
      if ((forward_backward_axis_value_fwd > DEADZONE &&
           forward_backward_axis_value_fwd < threshold_for_movement)) {
        forward_backward_voltage = min_voltage;
      } else {
        forward_backward_voltage =
            (forward_backward_axis_value_fwd * max_voltage) / 100;
      }

      if (left_right_axis_value_fwd > DEADZONE &&
          left_right_axis_value_fwd < threshold_for_movement) {
        left_right_voltage = min_voltage;
      } else {
        left_right_voltage = (left_right_axis_value_fwd * max_voltage_turn) / 100;
      }
    } else {
      if (forward_backward_axis_value_rev > DEADZONE &&
          forward_backward_axis_value_rev < threshold_for_movement) {
        forward_backward_voltage = -min_voltage;
      } else {
        forward_backward_voltage =
            -(forward_backward_axis_value_rev * max_voltage) / 100;
      }
      if (left_right_axis_value_rev > DEADZONE &&
          left_right_axis_value_rev < threshold_for_movement) {
        left_right_voltage = min_voltage;
      } else {
        left_right_voltage = (left_right_axis_value_rev * max_voltage_turn) / 100;
      }
    }

    // Check for DEADZONE
    bool within_DEADZONE = fabs(forward_backward_axis_value_fwd) < DEADZONE &&
                           fabs(left_right_axis_value_fwd) < DEADZONE &&
                           fabs(forward_backward_axis_value_rev) < DEADZONE &&
                           fabs(left_right_axis_value_rev) < DEADZONE;
    // control part
    if (within_DEADZONE) {
      // Stop all motors if within the DEADZONE
      stop(coast);
    } else {
      // Determine movement based on joystick inputs
      if (fabs(forward_backward_voltage) >= fabs(left_right_voltage)) {
        // Forward or backward movement
        if (forward_backward_voltage > 0) {
          drive_forward_control(forward_backward_voltage);
        } else {
          drive_backward_control(-forward_backward_voltage);
        }
      } else {
        // Turning movement
        if (left_right_voltage > 0) {
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

    } else if(!whether_intake && !whether_transmitter_reverse) {
     
      
      stop_intake();
      stop_transmit();
    }


    // flywheel (keep pressing L2 button)
    if (whether_flywheel) {
      //flywheel_motor.spin(directionType::fwd, MAXMOTOR_VOL, voltageUnits::mV);
      setFlyWheelSpeed(2);
      //   flywheel_motor.spin(directionType::fwd, 13000, voltageUnits::mV);
    } else {
      //flywheel_motor.stop(coast);
       //flywheel.stop();
      setFlyWheelSpeed(0);
    }
    // std::cout << getFlyWheelSpeed() << std::endl;


    //transmitter_reverse (keeping pressing L1 button)
    if(whether_transmitter_reverse) {
      transmit(-MAXMOTOR_VOL);
    }
    else if(!whether_transmitter_reverse && ! whether_intake)
    {
      stop_transmit();
    }
    // Delay for task scheduler
    vex::task::sleep(20);
  }
}