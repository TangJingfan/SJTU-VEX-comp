#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "robot_config.h"

using namespace vex;

void drive_forward_control(const double &voltage);

void drive_forward_auto(const double &voltage, double target_angle);

void drive_backward_control(const double &voltage);

void turn_left_control(const double &voltage);

void turn_right_control(const double &voltage);

void drive_backward_auto(const double &voltage, double target_angle);

void stop(brakeType b_type);

void move_certain_forward_distance(double tr_distance, double max_voltage);

void move_certain_backward_distance(double tr_distance, double max_voltage);

void turn_right_certain_degree(double tr_degree ,double max_voltage );

void turn_left_certain_degree(double tr_degree,double max_voltage);

double distance_to_degree(double distance);

double abs_value(double num);


#endif