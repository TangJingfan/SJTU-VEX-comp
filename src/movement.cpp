#include <vex.h>

using namespace vex;

void drive_forward(motor &left_front_motor, motor &left_back_motor,
                   motor &right_front_motor, motor &right_back_motor,
                   int &voltage) {
  left_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void drive_backward(motor &left_front_motor, motor &left_back_motor,
                    motor &right_front_motor, motor &right_back_motor,
                    int voltage) {
  left_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
}

void turn_left(motor &left_front_motor, motor &left_back_motor,
               motor &right_front_motor, motor &right_back_motor, int voltage) {
  left_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void turn_right(motor &left_front_motor, motor &left_back_motor,
                motor &right_front_motor, motor &right_back_motor,
                int voltage) {
  left_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
}
