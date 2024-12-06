#include "autonomous.h"

using namespace vex;

void autonomous() {

  //Left rot


  //first push ball into circle
  move_certain_forward_distance(1219.2,6000);
  turn_right_certain_degree(30,4000);
  move_certain_backward_distance(800,6000);


  //then move to the other balls and shoot them










  //right rot









  while (1) {
    // allow other tasks to run
    this_thread::sleep_for(10);
  }

}
