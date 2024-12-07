#include "flywheel.h"
#include <iostream>

using namespace vex;

void set_voltage(double voltage)
{
    target_voltage = voltage;
}

void maintain_voltage() {
    double integral = 0;
    double derivative = 0;
    double previous_error = 0;
    double kP = 0.5;
    double kI = 0.5;
    double kD = 0.5;
    while (true) {
        // get current voltage
        double current_voltage = get_current_voltage();
        // calculate error
        double current_error = target_voltage - current_voltage;
        // calculate integral and derivative
        integral += current_error;
        derivative = current_error - previous_error;
        // PID control
        double voltage = kP * current_error + kI * integral + kD * derivative;
        previous_error = current_error;
        // set limit
        if (voltage > MAXMOTOR_VOL) {
            voltage = MAXMOTOR_VOL;
        }
        if (voltage <= 0) {
            voltage = 0;
        }
        // spin, maintain the voltage
        std::cout << "current voltage: " << current_voltage << std::endl;
        flywheel_motor.spin(vex::directionType::fwd, voltage, vex::voltageUnits::mV);
        this_thread::sleep_for(10);
    }
}

double get_current_voltage() {
    // get power and current, then calculate voltage
    double power = flywheel_motor.power(vex::powerUnits::watt);
    double current = flywheel_motor.current(vex::currentUnits::amp);
    // deal with extreme values
    if (current > 0) {
        return power / current * 1000;
    } else {
        return 0;
    }
}

void stop_flywheel() { flywheel_motor.stop(coast); }