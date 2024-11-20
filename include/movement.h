#include <vex.h>

using namespace vex;

void drive_forward(motor &left_front_motor, motor &left_back_motor,
                   motor &right_front_motor, motor &right_back_motor,
                   int &speed) {
  left_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
  right_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
  left_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
  right_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
}

void drive_backward(motor &left_front_motor, motor &left_back_motor,
                    motor &right_front_motor, motor &right_back_motor,
                    int speed) {
  left_front_motor.spin(directionType::rev, speed, percentUnits::pct);
  right_front_motor.spin(directionType::rev, speed, percentUnits::pct);
  left_back_motor.spin(directionType::rev, speed, percentUnits::pct);
  right_back_motor.spin(directionType::rev, speed, percentUnits::pct);
}

void turn_left(motor &left_front_motor, motor &left_back_motor,
               motor &right_front_motor, motor &right_back_motor, int speed) {
  left_front_motor.spin(directionType::rev, speed, percentUnits::pct);
  right_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
  left_back_motor.spin(directionType::rev, speed, percentUnits::pct);
  right_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
}

void turn_right(motor &left_front_motor, motor &left_back_motor,
                motor &right_front_motor, motor &right_back_motor, int speed) {
  left_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
  right_front_motor.spin(directionType::rev, speed, percentUnits::pct);
  left_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
  right_back_motor.spin(directionType::rev, speed, percentUnits::pct);
}
