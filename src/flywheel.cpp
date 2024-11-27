#include "flywheel.h"
#include "robot_config.h"
#include "vex.h"

using namespace vex;

void shooting_blue_ball() {
  if (Controller.ButtonL1.pressing()) {
    flywheel.spin(directionType::fwd, 12000, voltageUnits::mV);
  } else {
    flywheel.stop(brakeType::coast);
  }
}