#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#include "robot_config.h"

using namespace vex;

class Flywheel {
private:
  vex::motor& flywheel;
  double target_voltage;
  double kP, kI, kD;
  double current_error, previous_error, integral, derivative;

public:
  Flywheel(vex::motor motor, double kp, double ki, double kd);

  void set_target_voltage(double voltage);

  void maintain_voltage();

  double get_current_voltage();

  void stop();
};

#endif