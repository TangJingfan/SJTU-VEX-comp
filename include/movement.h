#include <vex.h>

using namespace vex;

void drive_forward_control(const double &voltage);

void drive_forward_auto(const double &voltage);

void drive_backward_control(const double &voltage);

void turn_left_control(const double &voltage);

void turn_right_control(const double &voltage);

void drive_backward_auto(const double &voltage);

void turn_left_auto_certain_degree(double &voltage,
                                   const double &target_degree);

// void turn_right_auto_certain_degree(double& voltage, const double&
// target_degree);

void stop(brakeType b_type);