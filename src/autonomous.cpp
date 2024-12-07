#include "autonomous.h"

using namespace vex;

void autonomous() {

  //  auto_rot1();
  //  auto_rot2();
  //  auto_rot3();
  //  auto_rot4();

  while (1) {
    // allow other tasks to run
    this_thread::sleep_for(10);
  }
}


void auto_rot1(){
  move_certain_forward_distance(1469,MAXMOTOR_VOL,10);
  turn_right_certain_degree(36,4000);
  move_certain_backward_distance(1630,8000,7);


  move_certain_forward_distance(1000,4000,7);
}


void auto_rot2(){
  move_certain_forward_distance(1489,MAXMOTOR_VOL,10);
  turn_left_certain_degree(34,4000);
  move_certain_backward_distance(1630,8000,7);

}

void auto_rot3(){
  move_certain_forward_distance(1489,MAXMOTOR_VOL,10);
  turn_right_certain_degree(34,4000);
  move_certain_backward_distance(1630,8000,7);

}


void auto_rot4(){
  move_certain_forward_distance(1489,MAXMOTOR_VOL,10);
  turn_left_certain_degree(34,4000);
  move_certain_backward_distance(1630,8000,7);

}