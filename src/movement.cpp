#include "movement.h"

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

void drive_forward_auto(const double& voltage, double target_angle) {
    // set const for error correction
    const double kp = 1.5;
    
        // get current angle
        double current_angle = inertial_sensor.rotation();
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
        right_front_motor.spin(directionType::fwd, right_voltage, voltageUnits::mV);
        left_back_motor.spin(directionType::fwd, left_voltage, voltageUnits::mV);
        right_back_motor.spin(directionType::fwd, right_voltage, voltageUnits::mV);
        // avoid endless loop
        vex::task::sleep(20);
    
}

void drive_backward_auto(const double& voltage, double target_angle) {
    // set const for correction
    const double kp = 1.5;
    
        // get current angle
        double current_angle = inertial_sensor.rotation();
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
        left_front_motor.spin(directionType::rev, left_voltage, voltageUnits::mV);
        right_front_motor.spin(directionType::rev, right_voltage, voltageUnits::mV);
        left_back_motor.spin(directionType::rev, left_voltage, voltageUnits::mV);
        right_back_motor.spin(directionType::rev, right_voltage, voltageUnits::mV);
        // avoid endless loop
        vex::task::sleep(20);
    
}

// Unit : mm 
void move_certain_forward_distance(double tr_distance, double max_voltage,double time) {
    // need to be tested
    double kP = 50;
    double kI = 0.0;
    double kD = 0.0;

    double error = 0;
    double previous_error = 0;
    double integral = 0;
    double derivative = 0;

    double targetRotation = distance_to_degree(tr_distance);
    left_front_motor.resetPosition();
    right_front_motor.resetPosition();
    left_back_motor.resetPosition();
    right_back_motor.resetPosition();


    //set current angle to move straight
    inertial_sensor.resetRotation();
    double angle=inertial_sensor.rotation();


    // Time limit
    
    vex::timer Timer;

    while (Timer.time(sec) < time) {

        double Motor1_position = left_front_motor.position(degrees);
        double Motor2_position = right_front_motor.position(degrees);
        double Motor3_position = left_back_motor.position(degrees);
        double Motor4_position = right_back_motor.position(degrees);

        double current_position =
            (Motor1_position + Motor2_position + Motor3_position + Motor4_position) / 4.0;
        error = targetRotation - current_position;

        integral += error;
        derivative = error - previous_error;
        if (abs_value(error) < 10) {
            break;
        }
        double voltage = kP * error + kI * integral + kD * derivative;
        if (abs_value(voltage) > max_voltage) {
            voltage = max_voltage;
        }
        previous_error = error;
        // intake(8000);
        drive_forward_auto(voltage,angle);
        vex::task::sleep(20);
    }
    stop(coast);
}

void move_certain_forward_distance_and_intake(double tr_distance, double max_voltage,double time) {
    // need to be tested
    double kP = 50;
    double kI = 0.0;
    double kD = 0.0;

    double error = 0;
    double previous_error = 0;
    double integral = 0;
    double derivative = 0;

    double targetRotation = distance_to_degree(tr_distance);
    left_front_motor.resetPosition();
    right_front_motor.resetPosition();
    left_back_motor.resetPosition();
    right_back_motor.resetPosition();


    //set current angle to move straight
    inertial_sensor.resetRotation();
    double angle=inertial_sensor.rotation();


    // Time limit
    
    vex::timer Timer;

    while (Timer.time(sec) < time) {

        double Motor1_position = left_front_motor.position(degrees);
        double Motor2_position = right_front_motor.position(degrees);
        double Motor3_position = left_back_motor.position(degrees);
        double Motor4_position = right_back_motor.position(degrees);

        double current_position =
            (Motor1_position + Motor2_position + Motor3_position + Motor4_position) / 4.0;
        error = targetRotation - current_position;

        integral += error;
        derivative = error - previous_error;
        if (abs_value(error) < 10) {
            break;
        }
        double voltage = kP * error + kI * integral + kD * derivative;
        if (abs_value(voltage) > max_voltage) {
            voltage = max_voltage;
        }
        previous_error = error;

        drive_forward_auto(voltage,angle);
        intake(MAXMOTOR_VOL);
        transmit(MAXMOTOR_VOL);
        vex::task::sleep(20);
    }
    stop(coast);
    vex::task::sleep(2000);
    stop_intake();
    stop_transmit();
}

void move_certain_backward_distance(double tr_distance, double max_voltage,double time){
    // need to be tested
    double kP = 50;
    double kI = 0.0;
    double kD = 0.0;

    double error = 0;
    double previous_error = 0;
    double integral = 0;
    double derivative = 0;

    double targetRotation = distance_to_degree(tr_distance);
    left_front_motor.resetPosition();
    right_front_motor.resetPosition();
    left_back_motor.resetPosition();
    right_back_motor.resetPosition();


    //set current angle to move straight
    inertial_sensor.resetRotation();
    double angle=inertial_sensor.rotation();


    // Time limit
    vex::timer Timer;

    while (Timer.time(sec) <time ) {

        double Motor1_position = left_front_motor.position(degrees);
        double Motor2_position = right_front_motor.position(degrees);
        double Motor3_position = left_back_motor.position(degrees);
        double Motor4_position = right_back_motor.position(degrees);

        double current_position =
            (Motor1_position + Motor2_position + Motor3_position + Motor4_position) / 4.0;
        error = targetRotation + current_position;

        integral += error;
        derivative = error - previous_error;
        if (abs_value(error) < 5) {
            break;
        }
        double voltage = kP * error + kI * integral + kD * derivative;
        if (abs_value(voltage) > max_voltage) {
            voltage = max_voltage;
        }
        previous_error = error;

        drive_backward_auto(voltage,angle);
        vex::task::sleep(20);
    }
    stop(coast);

}

//normally max_voltage set 4000
void turn_right_certain_degree(double tr_degree, double max_voltage)
{
    inertial_sensor.resetRotation();
    
    
    // need to be tested
    double kP = 100;
    double kI = 0;
    double kD = 0;

    double error = 0;
    double previous_error = 0;
    double integral = 0;
    double derivative = 0;

    left_front_motor.resetPosition();
    right_front_motor.resetPosition();
    left_back_motor.resetPosition();
    right_back_motor.resetPosition();

    // Time limit
    // set bigger to test the coefficient
    double Time_limit = 1.5;
    vex::timer Timer;
    double current_angle;
    while (Timer.time(sec) <= Time_limit) {
    

        
        current_angle = inertial_sensor.rotation();


        error = tr_degree - current_angle;

        integral += error;
        derivative = error - previous_error;
         if (abs_value(error)<8 ) {
            break;
        } 
        double voltage = kP * error + kI * integral + kD * derivative;
        if (abs_value(voltage) > max_voltage) {
            voltage = max_voltage;
        }
        previous_error = error;

        
        turn_right_control(voltage);

        vex::task::sleep(20);
    }

    stop(coast);
}

void turn_left_certain_degree(double tr_degree,double max_voltage)
{
    inertial_sensor.resetRotation();
    
    
    // need to be tested
    double kP = 100;
    double kI = 0.1;
    double kD = 0.1;

    double error = 0;
    double previous_error = 0;
    double integral = 0;
    double derivative = 0;

    left_front_motor.resetPosition();
    right_front_motor.resetPosition();
    left_back_motor.resetPosition();
    right_back_motor.resetPosition();

    // Time limit
    // set bigger to test the coefficient
    double Time_limit = 1.5;
    vex::timer Timer;
    double current_angle;
    while (Timer.time(sec) <= Time_limit) {
    

        
        current_angle = inertial_sensor.rotation();


        error = tr_degree + current_angle;

        integral += error;
        derivative = error - previous_error;
         if (abs_value(error)<8 ) {
            break;
        } 
        double voltage = kP * error + kI * integral + kD * derivative;
        if (abs_value(voltage) > max_voltage) {
            voltage = max_voltage;
        }
        previous_error = error;

        
        turn_left_control(voltage);

        vex::task::sleep(20);
    }

    stop(coast);

}

void stop(brakeType b_type) {
    left_front_motor.stop(b_type);
    right_front_motor.stop(b_type);
    left_back_motor.stop(b_type);
    right_back_motor.stop(b_type);
}

// Unit : mm
double distance_to_degree(double distance) {
    // Unit : mm
    double wheel_radius = 34.925;
    double C = 2.0 * M_PI * wheel_radius;
    return distance / C * 360.0;
}

double abs_value(double num) {
    if (num <=0) {
    num = -num;
    } 
    return num;
}