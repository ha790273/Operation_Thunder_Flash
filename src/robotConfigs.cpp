#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "robotConfigs.h" // IWYU pragma: keep
#include "pros/motors.hpp"


// TODO: Get track length, tune the PIDS and configure  IMU and test odom tracking
/*

            Cascade
Blue motors 
450rpm 
intake 5.5 
wrist 5.5w motor 100 rpm 
roller 5.5w 

cascade 22W
11W Intake 600 RPM

pnumatics 

Odom

IMEs



*/






// Motor Ports for the drivetrain.
int8_t leftFrontPort = 1;
int8_t leftBackPort = 2;

int8_t rightFrontPort = 3;
int8_t rightBackPort = 4;

// Cascade Motors

int8_t intakeMotorPort = 8;
int8_t wristMotorPort = 9;
int8_t rollerMotorPort = 20;




// General Motor Ports

pros::Motor intake(intakeMotorPort);
pros::Motor wrist(wristMotorPort);
pros::Motor roller(rollerMotorPort);




/*
void intaker(){
      intake.move(127);
}
*/



// Sensors + Odom stuff
pros::Imu imu(10);// create an imu on port 10
pros::Vision vision_sensor(7); // Initialize vision sensor on port 7
pros::Rotation vertical_sensor(5);
pros::Rotation horizontal_sensor(6);



// Drivetrain motor groups
pros::MotorGroup left_motors({leftFrontPort, leftBackPort}, pros::MotorGearset::blue); // left motors on ports 
pros::MotorGroup right_motors({rightFrontPort, rightBackPort}, pros::MotorGearset::blue); // right motors on ports 



// Drivetrain and odometry
lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 2.75" omni wheels
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);


lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor, lemlib::Omniwheel::NEW_2, -5.75);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_sensor, lemlib::Omniwheel::NEW_2, -2.75);


lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);



//                                          PID 

// lateral PID controller 
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);


// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors, // odometry sensors
                        &throttle_curve, 
                        &steer_curve
);









