#include "movement.h"
#include "robot_config.h"
#include "vex.h"

using namespace vex;

void drive_forward(int& speed) {
    left_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
    right_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
    left_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
    right_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
}

void drive_backward(int speed) {
    left_front_motor.spin(directionType::rev, speed, percentUnits::pct);
    right_front_motor.spin(directionType::rev, speed, percentUnits::pct);
    left_back_motor.spin(directionType::rev, speed, percentUnits::pct);
    right_back_motor.spin(directionType::rev, speed, percentUnits::pct);
}

void turn_left(int speed) {
    left_front_motor.spin(directionType::rev, speed, percentUnits::pct);
    right_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
    left_back_motor.spin(directionType::rev, speed, percentUnits::pct);
    right_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
}

void turn_right(int speed) {
    left_front_motor.spin(directionType::fwd, speed, percentUnits::pct);
    right_front_motor.spin(directionType::rev, speed, percentUnits::pct);
    left_back_motor.spin(directionType::fwd, speed, percentUnits::pct);
    right_back_motor.spin(directionType::rev, speed, percentUnits::pct);
}

void stop(brakeType b_type){
    left_front_motor.stop(b_type);
    right_front_motor.stop(b_type);
    left_back_motor.stop(b_type);
    right_back_motor.stop(b_type);
}
