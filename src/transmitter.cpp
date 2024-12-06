#include "transmitter.h"

void transmit(const double &voltage) {
  transmitter_motor.spin(directionType::fwd, voltage, voltageUnits::mV);
}

void stop_transmit() { transmitter_motor.stop(coast); }