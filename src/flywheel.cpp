#include "flywheel.h"
#include <iomanip>
#include <iostream>

using namespace vex;

double target_voltage = 0;

double curr_speed = 0;
double tar_speed = 0;

void setFlyWheelSpeed(double speed) { tar_speed = speed; }

double getFlyWheelSpeed() { return curr_speed; }

void calcFlyWheelSpeed() {
  double start_pos = 0;
  double d_pos = 0;
  double tmp_spd = 0;
  while (true) {
    int start_time = Brain.Timer.time();
    vexDelay(10);
    d_pos = flywheel_motor.position(rev) - start_pos;
    start_pos = flywheel_motor.position(rev);
    int end_time = Brain.Timer.time();
    tmp_spd = -d_pos / (end_time - start_time) * 1000;
    if (tmp_spd > 3.9) {
      curr_speed = 3.9;
    } else if (tmp_spd < -3.9) {
      curr_speed = -3.9;
    } else {
      curr_speed = tmp_spd;
    }
    // std::cout << d_pos << " " << (end_time - start_time) << " " << tmp_spd
    //   << std::endl;
  }
}

void updateFlywheel() {
  double integral = 0;
  double derivative = 0;
  double previous_error = 0;
  double kP = 60000;
  double kI = 150.0;
  double kD = 75;
  while (true) {
    // calculate error
    double current_error = curr_speed - tar_speed;
    // calculate integral and derivative
    integral += current_error;
    derivative = current_error - previous_error;
    if (fabs(current_error) > 0.15)
      integral = 0;
    // PID control
    double voltage = kP * current_error + kI * integral + kD * derivative;
    previous_error = current_error;
    // set limit
    if (fabs(voltage) > MAXMOTOR_VOL) {
      voltage = MAXMOTOR_VOL * sign(voltage);
    }
    // if (voltage <= 0) {
    //   voltage = 0;
    // }
    // spin, maintain the voltage
    std::cout << std::fixed << "current voltage: " << voltage << " "
              << curr_speed << " " << current_error << std::endl;
    flywheel_motor.spin(vex::directionType::fwd, voltage,
                        vex::voltageUnits::mV);
    this_thread::sleep_for(20);
  }
}

double get_current_voltage() {
  // get power and current, then calculate voltage
  double power = flywheel_motor.power(vex::powerUnits::watt);
  double current = flywheel_motor.current(vex::currentUnits::amp);
  // deal with extreme values
  if (current > 0) {
    return power / current * 1000;
  } else {
    return 0;
  }
}

void stop_flywheel() { flywheel_motor.stop(coast); }