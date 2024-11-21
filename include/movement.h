#include <vex.h>

using namespace vex;

void drive_forward(motor &left_front_motor, motor &left_back_motor,
                   motor &right_front_motor, motor &right_back_motor,
                   int &speed);

void drive_backward(motor &left_front_motor, motor &left_back_motor,
                    motor &right_front_motor, motor &right_back_motor,
                    int speed);

void turn_left(motor &left_front_motor, motor &left_back_motor,
               motor &right_front_motor, motor &right_back_motor, int speed);

void turn_right(motor &left_front_motor, motor &left_back_motor,
                motor &right_front_motor, motor &right_back_motor, int speed);
