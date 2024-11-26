#include <vex.h>

using namespace vex;

void drive_forward_control(const double &voltage);

void drive_forward_auto(const double &voltage);

void drive_backward_control(const double &voltage);

void turn_left_control(const double &voltage);

void turn_right_control(const double &voltage);

void drive_backward_auto(const double &voltage);

void stop(brakeType b_type);

void move_certain_distance(int tr_distance);

void turn_certain_degree(int tr_degree);

double distance_to_degree(double distance);