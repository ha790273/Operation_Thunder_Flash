#ifndef MOTOR_MONITOR_H
#define MOTOR_MONITOR_H

#include "main.h"


// Motor Monitor
class MotorMonitor {
public:
    void update();

    double leftFrontTemp = 0;
    double leftBackTemp = 0;
    double rightFrontTemp = 0;
    double rightBackTemp = 0;
};



#endif
