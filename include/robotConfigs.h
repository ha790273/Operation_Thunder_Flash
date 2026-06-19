#include "lemlib/chassis/chassis.hpp"
#include "pros/rotation.hpp"

#ifndef _ROBOT_CONFIGS_H_
#define _ROBOT_CONFIGS_H_


// Drivetrian stuff
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;
extern lemlib::Chassis chassis;


// Odometry stuff
extern lemlib::OdomSensors sensors;
extern pros::Rotation vertical_sensor;
extern pros::Rotation horizontal_sensor;

// Other motors for the bot



#endif // _ROBOT_CONFIGS_H_