#include <vex.h>

using namespace vex;

void drive_forward_control(motor &left_front_motor, motor &left_back_motor,
                           motor &right_front_motor, motor &right_back_motor,
                           const int &voltage);

void drive_forward_auto(motor &left_front_motor, motor &left_back_motor,
                        motor &right_front_motor, motor &right_back_motor,
                        const int &voltage, inertial &inertial_sensor);

void drive_backward_control(motor &left_front_motor, motor &left_back_motor,
                            motor &right_front_motor, motor &right_back_motor,
                            const int &voltage);

void turn_left_control(motor &left_front_motor, motor &left_back_motor,
                       motor &right_front_motor, motor &right_back_motor,
                       const int &voltage);

void turn_right_control(motor &left_front_motor, motor &left_back_motor,
                        motor &right_front_motor, motor &right_back_motor,
                        const int &voltage);

void drive_backward_auto(motor &left_front_motor, motor &left_back_motor,
                         motor &right_front_motor, motor &right_back_motor,
                         const int &voltage, inertial &inertial_sensor);