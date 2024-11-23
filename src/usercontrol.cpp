#include "movement.h"
#include "robot_config.h"
#include "vex.h"

using namespace vex;

void usercontrol() {
    while (1) {
        // get controller.axis value
        // axis 3 for moving forward and backward
        // axis 4 for turning left and right
        int speed = Controller.Axis3.position();
        int rotation = Controller.Axis4.position();

        // deadzone for improving sensitivity
        const int deadzone = 10;

        // determine what action motor should take
        if (abs(speed) < deadzone && abs(rotation) < deadzone) {
            // within deadzone, no movement
            stop();
        } else {
            // not in deadzone
            if (abs(speed) >= abs(rotation)) {
                // forward or backward
                if (speed > 0) {
                    drive_forward(speed);
                } else {
                    drive_backward(-speed);
                }
            } else {
                // turn left ot right
                if (rotation > 0) {
                    turn_right(rotation);
                } else {
                    turn_left(-rotation);
                }
            }
        }
        // delay 20ms, in order to keep every command clear to brain
        this_thread::sleep_for(20);
    }
}