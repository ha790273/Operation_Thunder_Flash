#pragma once


#include "lemlib/chassis/chassis.hpp"
#include "pros/rotation.hpp"
#include "pros/imu.hpp"
#include "pros/vision.hpp"
#include "pros/motors.hpp"

// * #pragma once (use if feeling lazy at times)

// Drive train stuff
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;
extern lemlib::Chassis chassis;


// Odometry headers for main file
extern lemlib::OdomSensors sensors;
extern pros::Imu imu;
extern pros::Rotation vertical_sensor;
extern pros::Rotation horizontal_sensor;
extern lemlib::ControllerSettings lateral_controller; // lateral PID Controller settings
extern lemlib::ControllerSettings angular_controller; // angular PID Controller settings

// Other motors for the bot

extern pros::Motor intake;
extern pros::Motor wrist;
extern pros::Motor roller;



// Vision
extern pros::Vision vision_sensor;

