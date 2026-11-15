#include "motorTemp.hpp"
#include "robotConfigs.h"


void MotorMonitor::update() {

    // Get temperatures from both motor groups
    auto leftTemps = left_motors.get_temperature_all();
    auto rightTemps = right_motors.get_temperature_all();

    // Left drivetrain
    leftFrontTemp = leftTemps[0];
    leftBackTemp = leftTemps[1];

    // Right drivetrain
    rightFrontTemp = rightTemps[0];
    rightBackTemp = rightTemps[1];
}