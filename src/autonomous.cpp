#include "autonomous.h"

using namespace vex;

void autonomous() {
  auto_rot_blue_left();
  //auto_rot_blue_right();
  //auto_rot_red_left();
  //auto_rot_red_right();
  

  while (1) {
    // allow other tasks to run
    this_thread::sleep_for(10);
  }
}


void auto_rot_blue_left(){
  move_certain_forward_distance(1280,8000,10);
  turn_right_certain_degree(180,4000);
  move_certain_backward_distance(170,4000,2);
  turn_left_certain_degree(70,4000);
  move_certain_backward_distance(1520,6000,7);


  move_certain_forward_distance(500,4000,7);
}


void auto_rot_blue_right(){
  move_certain_forward_distance(1489,MAXMOTOR_VOL,10);
  turn_left_certain_degree(34,4000);
  move_certain_backward_distance(1630,8000,7);

}

void auto_rot_red_left(){
  move_certain_forward_distance(1439,MAXMOTOR_VOL,10);
  turn_right_certain_degree(38,4000);
  move_certain_backward_distance(1630,8000,7);

}


void auto_rot_red_right(){
  move_certain_forward_distance(1489,MAXMOTOR_VOL,10);
  turn_left_certain_degree(34,4000);
  move_certain_backward_distance(1630,8000,7);

}