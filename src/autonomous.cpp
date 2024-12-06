#include "autonomous.h"

using namespace vex;

void autonomous() {

  move_certain_distance(1000); // 609.5mm per foam plate
  intake(MAXMOTOR_VOL);
  task::sleep(1000);
  stop_intake();
  turn_certain_degree(153);
  task::sleep(100);
  move_certain_distance(1300);
  intake(MAXMOTOR_VOL);
  task::sleep(1000);
  stop_intake();
  turn_certain_degree(180);
  task::sleep(100);
  move_certain_distance(60);


  // while (1) {
  //   // allow other tasks to run
  //   this_thread::sleep_for(10);
  // }

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
