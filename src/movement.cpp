#include "movement.h"
#include "robot_config.h"
#include <vex.h>

using namespace vex;

void drive_forward_control(const double &voltage) {
  left_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void drive_backward_control(const double &voltage) {
  left_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
}

void turn_left_control(const double &voltage) {
  left_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void turn_right_control(const double &voltage) {
  left_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
  left_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
  right_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
}

void drive_forward_auto(const double &voltage) {
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

void drive_backward_auto(const double &voltage) {
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

// Unit : mm (positive for forwards,
// negative for backwards)
void move_certain_distance(int tr_distance) {
  bool forward = false;
  if (tr_distance >= 0) {
    forward = true;
  }
  tr_distance = sqrt(tr_distance);

  // need to be tested
  double kP = 0.5;
  double kI = 0.01;
  double kD = 0.2;

  double error = 0;
  double previous_error = 0;
  double integral = 0;
  double derivative = 0;

  double targetRotation = distance_to_degree(tr_distance);
  left_front_motor.resetPosition();
  right_front_motor.resetPosition();
  left_back_motor.resetPosition();
  right_back_motor.resetPosition();

  // Time limit
  double Time_limit = 20.0; // set bigger to test the coefficient
  vex::timer Timer;

  while (Timer.time(sec) < Time_limit) {

    double Motor1_position = left_front_motor.position(degrees);
    double Motor2_position = right_front_motor.position(degrees);
    double Motor3_position = left_back_motor.position(degrees);
    double Motor4_position = right_back_motor.position(degrees);

    double current_position = (Motor1_position + Motor2_position +
                               Motor3_position + Motor4_position) /
                              4.0;
    error = targetRotation - current_position;

    integral += error;
    derivative = error - previous_error;
    if (sqrt(error) < 5) {
      break;
    }
    double voltage = kP * error + kI * integral + kD * derivative;
    previous_error = error;

    if (forward) {
      drive_forward_auto(voltage);
    } else {
      drive_backward_auto(voltage);
    }
    vex::task::sleep(20);
  }
  stop(brake);
}

void turn_certain_degree(int tr_degree)
// Unit : degree (positive for turn right, negative for left)
{
  bool right = false;
  if (tr_degree >= 0) {
    right = true;
  }
  tr_degree = sqrt(tr_degree) + inertial_sensor.heading();

  // need to be tested
  double kP = 0.5;
  double kI = 0.01;
  double kD = 0.2;

  double error = 0;
  double previousError = 0;
  double integral = 0;
  double derivative = 0;

  left_front_motor.resetPosition();
  right_front_motor.resetPosition();
  left_back_motor.resetPosition();
  right_back_motor.resetPosition();

  // Time limit
  // set bigger to test the coefficient
  double Time_limit = 20.0;
  vex::timer Timer;

  while (Timer.time(sec) <= Time_limit) {

    double current_angle = inertial_sensor.heading();
    error = tr_degree - current_angle;

    integral += error;
    derivative = error - previousError;
    if (sqrt(error) < 1) {
      break;
    }
    double voltage = kP * error + kI * integral + kD * derivative;
    previousError = error;

    if (right) {
      turn_right_control(voltage);
    } else {
      turn_left_control(voltage);
    }
    vex::task::sleep(20);
  }

  stop(brake);
}

void stop(brakeType b_type) {
  left_front_motor.stop(b_type);
  right_front_motor.stop(b_type);
  left_back_motor.stop(b_type);
  right_back_motor.stop(b_type);
}

double distance_to_degree(double distance) // Unit : mm
{
  double wheel_radius; // Unit : mm
  double C = 2.0 * M_PI * wheel_radius;
  return distance / C * 360.0;
}