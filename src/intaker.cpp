#include "intaker.h"

void intake(const double &voltage) {
  intaker_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void stop_intake() { intaker_motor.stop(coast); }