
#ifndef ROBOT_CONFIGS_H
#define ROBOT_CONFIGS_H

#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "pros/imu.hpp"


// Drivetrain
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

// LemLib
extern lemlib::Chassis chassis;
extern lemlib::Drivetrain drivetrain;

// Odometry
extern lemlib::OdomSensors sensors;
// extern pros::Imu imu;


/*
extern pros::Rotation vertical_sensor;
extern pros::Rotation horizontal_sensor;


*/

// PID controllers
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

// Other motors
extern pros::Motor intake;
extern pros::Motor wrist;
extern pros::Motor roller;
extern pros::Motor CascadeLift;



#endif
