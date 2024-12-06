#include "autonomous.h"

using namespace vex;

void autonomous() {

  //rot 1


  //first push ball into circle
  move_certain_forward_distance(1469,MAXMOTOR_VOL,10);
  turn_right_certain_degree(36,4000);
  move_certain_backward_distance(1630,8000,7);


  move_certain_forward_distance(1000,4000,7);


 /*  move_certain_forward_distance(1000,6000);
  turn_right_certain_degree(20,4000);
  move_certain_forward_distance(40,4000); */
  //then move to the other balls and shoot them

  //rot 2
  /* move_certain_forward_distance(1489,MAXMOTOR_VOL,10);
  turn_left_certain_degree(34,4000);
  move_certain_backward_distance(1630,8000,7); */






  //rot 3

  /* move_certain_forward_distance(1419.2,MAXMOTOR_VOL,10);
  turn_right_certain_degree(35,4000);
  move_certain_backward_distance(1510,6000,7); */



  //rot 4








  //right rot
 








  while (1) {
    // allow other tasks to run
    this_thread::sleep_for(10);
  }

}
