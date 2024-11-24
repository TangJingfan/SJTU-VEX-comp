#include "movement.h"
#include "robot_config.h"
#include <vex.h>

using namespace vex;

void drive_forward_control(const double& voltage) {
    left_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
    right_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
    left_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
    right_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void drive_backward_control(const double& voltage) {
    left_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
    right_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
    left_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
    right_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
}

void turn_left_control(const double& voltage) {
    left_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
    right_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
    left_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
    right_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void turn_right_control(const double& voltage) {
    left_front_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
    right_front_motor.spin(directionType::rev, voltage, voltageUnits::mV);
    left_back_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
    right_back_motor.spin(directionType::rev, voltage, voltageUnits::mV);
}

void drive_forward_auto(const double& voltage) {
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

void drive_backward_auto(const double& voltage) {
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

void turn_left_auto_certain_degree(double& voltage, const double& target_degree) {
    // get destination
    double destination_degree = inertial_sensor.heading() + target_degree;
    const double kp = 1.5;
    while (true) {
        // get current degree
        double current_degree = inertial_sensor.heading();
        double error = current_degree - destination_degree;
        if (error > 180) {
            error -= 360;
        }
        if (error < -180) {
            error += 360;
        }
        double correction = error * kp;
    }
}

void stop(brakeType b_type) {
    left_front_motor.stop(b_type);
    right_front_motor.stop(b_type);
    left_back_motor.stop(b_type);
    right_back_motor.stop(b_type);
}