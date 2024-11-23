#include <vex.h>

using namespace vex;

void drive_forward(int& speed);
void drive_backward(int speed);
void turn_left(int speed);
void turn_right(int speed);
void stop(brakeType b_type = brakeType::brake);
