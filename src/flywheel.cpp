#include "flywheel.h"
#include "robot_config.h"
#include "vex.h"

using namespace vex;

Flywheel::Flywheel(vex::motor motor, double kp, double ki, double kd)
    : flywheel(motor), target_voltage(0), kP(kp), kI(ki), kD(kd),
      current_error(0), previous_error(0), integral(0), derivative(0) {};

void Flywheel::set_target_voltage(double voltage) { target_voltage = voltage; }

void Flywheel::maintain_woltage() {
  // get current voltage
  double current_voltage = get_current_voltage();
  // calculate error
  current_error = current_voltage - target_voltage;
  // calculate integral and derivative
  integral += current_error;
  derivative = current_error - previous_error;
  // PID control
  double voltage = kP * current_error + kI * integral + kD * derivative;
  previous_error = current_error;
  // set limit
  if (voltage > MAXMOTOR_VOL) {
    voltage = MAXMOTOR_VOL;
  }
  if (voltage < 0) {
    voltage = 0;
  }
  // spin, maintain the voltage
  flywheel.spin(vex::directionType::fwd, voltage, vex::voltageUnits::mV);
}

double Flywheel::get_current_voltage() {
  double power = flywheel.power(vex::powerUnits::watt);
  double current = flywheel.current(vex::currentUnits::amp);

  if (current > 0) {
    return power / current * 1000;
  } else {
    return 0;
  }
}

void Flywheel::stop() { flywheel.stop(coast); }