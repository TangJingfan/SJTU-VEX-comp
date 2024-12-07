#include "autonomous.h"
#include "flywheel.h"
#include "robot_config.h"
#include "usercontrol.h"
#include <iostream>
#include <thread>

using namespace vex;

int main() {
  // calibrate inertial seneor
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Inertial Sensor");
  inertial_sensor.calibrate(3);
  while (inertial_sensor.isCalibrating()) {
    vex::task::sleep(100);
  }
  Brain.Screen.clearScreen();

  thread flywheel_thread(updateFlywheel);
  thread flywheel_calcSpd(calcFlyWheelSpeed);

  // thread flywheel_thread((void*)(flywheel.maintain_voltage));

  // Set up competition callbacks
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting
  while (true) {
    task::sleep(20);
  }
}
