#include <vex.h>

using namespace vex;

void drive_forward_control(motor &left_front_motor, motor &left_back_motor,
                           motor &right_front_motor, motor &right_back_motor,
                           const int &voltage) {
  left_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void drive_backward_control(motor &left_front_motor, motor &left_back_motor,
                            motor &right_front_motor, motor &right_back_motor,
                            const int &voltage) {
  left_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
}

void turn_left_control(motor &left_front_motor, motor &left_back_motor,
                       motor &right_front_motor, motor &right_back_motor,
                       const int &voltage) {
  left_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void turn_right_control(motor &left_front_motor, motor &left_back_motor,
                        motor &right_front_motor, motor &right_back_motor,
                        const int &voltage) {
  left_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
}

void drive_forward_auto(motor &left_front_motor, motor &left_back_motor,
                        motor &right_front_motor, motor &right_back_motor,
                        const int &voltage, inertial &inertial_sensor) {
  // get initial direction
  double target_angle = inertial_sensor.heading();
  // set const for error correction
  const double kp = 1.5;
  while (true) {
    // get current angle
    double current_angle = inertial_sensor.heading();
    // calculate error
    double error = current_angle - target_angle;
    // set error to -180 degree to 180 degree
    if (error > 180) {
      error -= 360;
    }
    if (error < -180) {
      error += 360;
    }
    // calculate correction term
    double correction = error * kp;
    // add correction to voltage
    double left_voltage = voltage - correction;
    double right_voltage = voltage + correction;
    // run the motor
    left_front_motor.spin(directionType::fwd, left_voltage, voltageUnits::mV);
    right_front_motor.spin(directionType::rev, right_voltage, voltageUnits::mV);
    left_back_motor.spin(directionType::fwd, left_voltage, voltageUnits::mV);
    right_back_motor.spin(directionType::rev, right_voltage, voltageUnits::mV);
    // avoid endless loop
    vex::task::sleep(20);
  }
}

void drive_backward_auto(motor &left_front_motor, motor &left_back_motor,
                         motor &right_front_motor, motor &right_back_motor,
                         const int &voltage, inertial &inertial_sensor) {
  // get initial direction
  double target_angle = inertial_sensor.heading();
  // set const for correction
  const double kp = 1.5;
  while (true) {
    // get current angle
    double current_angle = inertial_sensor.heading();
    // calculate error
    double error = current_angle - target_angle;
    // set error to -180 degree to 180 degree
    if (error > 180) {
      error -= 360;
    }
    if (error < -180) {
      error += 360;
    }
    // calculate correction term
    double correction = error * kp;
    // add correction to voltage
    double left_voltage = voltage + correction;
    double right_voltage = voltage - correction;
    // run the motor
    left_front_motor.spin(directionType::fwd, left_voltage, voltageUnits::mV);
    right_front_motor.spin(directionType::rev, right_voltage, voltageUnits::mV);
    left_back_motor.spin(directionType::fwd, left_voltage, voltageUnits::mV);
    right_back_motor.spin(directionType::rev, right_voltage, voltageUnits::mV);
    // avoid endless loop
    vex::task::sleep(20);
  }
}