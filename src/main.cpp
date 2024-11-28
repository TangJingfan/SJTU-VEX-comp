#include "robot_config.h"
#include "usercontrol.h"
#include "autonomous.h"



using namespace vex;

int main() {

    // calibrate inertial seneor

    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Calibrating Inertial Sensor");
    inertial_sensor.calibrate();
    while (inertial_sensor.isCalibrating()) {
        vex::task::sleep(100);
    }
    Brain.Screen.clearScreen();

    // Set up competition callbacks
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Prevent main from exiting
    while (true) {
        task::sleep(50);
    }
}
