#include "autonomous.h"
#include "movement.h"
#include "robot_config.h"
#include "usercontrol.h"
#include "vex.h"

using namespace vex;

int main() {
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    return 0;
}
