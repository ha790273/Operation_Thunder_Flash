#include "lemlib/chassis/chassis.hpp"
#include "pros/rotation.hpp"
#include "pros/imu.hpp"
#include "pros/vision.hpp"

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



// Vision
extern pros::Vision vision_sensor;

#endif // _ROBOT_CONFIGS_H_