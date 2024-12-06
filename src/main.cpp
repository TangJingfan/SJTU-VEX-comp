#include "autonomous.h"
#include "robot_config.h"
#include "usercontrol.h"
#include <thread>

using namespace vex;

// define flywheel
// kp, ki, kd need to be modified
Flywheel flywheel(flywheel_motor, 0.1, 0.02, 0.01);

void update_flywheel() {
  flywheel.maintain_voltage();
}

int main() {
  // calibrate inertial seneor
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Inertial Sensor");
  inertial_sensor.calibrate(3);
  while (inertial_sensor.isCalibrating()) {
    vex::task::sleep(100);
  }
  Brain.Screen.clearScreen();

  thread flywheel_thread(update_flywheel);

  // thread flywheel_thread((void*)(flywheel.maintain_voltage));

  // Set up competition callbacks
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting
  while (true) {
    task::sleep(50);
  }
}
