#include "autonomous.h"


using namespace vex;

void autonomous() {

  inertial_sensor.calibrate();
  // The robot must stay still
  while (inertial_sensor.isCalibrating()) {
    Brain.Screen.clearScreen();
    Brain.Screen.print("Inertial Calibrating");
    wait(50, msec);
  }
  // Brain.Screen.setCursor(2, 5);
  // Brain.Screen.print("Autonomous Mode");

  // // Example autonomous sequence
  // drive_forward_auto(6000);
  // task::sleep(2000);
  // // Drive forward for 2 seconds

  // drive_backward_auto(6000);
  // task::sleep(2000);
  // // Drive backward for 2 seconds

  // Brain.Screen.setCursor(2, 6);
  // Brain.Screen.print("Autonomous complete");
  
}
