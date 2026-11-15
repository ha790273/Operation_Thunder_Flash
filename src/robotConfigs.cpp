#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "robotConfigs.h" // IWYU pragma: keep
#include "pros/motors.hpp"
#include <cstdint>








// Drivetrain Motors
constexpr std::int8_t leftFrontPort = 1;
constexpr std::int8_t leftBackPort = 2;
constexpr std::int8_t rightFrontPort = -3;
constexpr std::int8_t rightBackPort = -4;




// Cascade Motors
constexpr std::int8_t intakeMotorPort = 8;
constexpr std::int8_t wristMotorPort = 9;
constexpr std::int8_t rollerMotorPort = 20;
constexpr std::int8_t CascadeLiftMotorPort = 16;
constexpr std::int8_t CascadeLiftMotorPort2 = 17;


/*




*/

// Motor Temperatures



// Intakes and rollers
pros::Motor intake(intakeMotorPort);
pros::Motor wrist(wristMotorPort);
pros::Motor roller(rollerMotorPort);


// Cascade Motors
pros::Motor CascadeLeft(CascadeLiftMotorPort);
pros::Motor CascadeRight(CascadeLiftMotorPort2);










// Imu and Sensors


/*


pros::Imu imu(21);// create an imu on port 10
pros::Rotation vertical_sensor(5);
pros::Rotation horizontal_sensor(6);
*/








// Drivetrain motor groups
pros::MotorGroup left_motors({leftFrontPort, leftBackPort}, pros::MotorGearset::blue); // left motors on ports
pros::MotorGroup right_motors({rightFrontPort, rightBackPort}, pros::MotorGearset::blue); // right motors on ports






// Drivetrain and odometry
lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              12, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 2.75" omni wheels
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);


/*
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor, lemlib::Omniwheel::NEW_2, -5.75);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_sensor, lemlib::Omniwheel::NEW_2, -2.75);


// Odom Sensors [Vertical Tracking Wheel, Horizontal and IMU]
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr // inertial sensor
);



*/
// Create tracking wheels from your drivetrain motor groups (required when not using an IMU)
// Note: Offset is half of your track width (-6.0 and 6.0 for a 12" track width, or -5.0 and 5.0 for 10")
lemlib::TrackingWheel left_tracking_wheel(&left_motors, lemlib::Omniwheel::NEW_275, -6.0, 450);
lemlib::TrackingWheel right_tracking_wheel(&right_motors, lemlib::Omniwheel::NEW_275, 6.0, 450);

// Odom Sensors [Vertical Tracking Wheels, Horizontal Tracking Wheels, and IMU]
lemlib::OdomSensors sensors(&left_tracking_wheel,  // vertical tracking wheel 1
                            &right_tracking_wheel, // vertical tracking wheel 2
                            nullptr,               // horizontal tracking wheel 1
                            nullptr,               // horizontal tracking wheel 2
                            nullptr                // inertial sensor (disabled)
);









//!                                          PID


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


//! Tuning this first
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);




// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, //3 joystick deadband out of 127
                                     10, // 10minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);




// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, //3 joystick deadband out of 127
                                  10, // 10minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
); // raise to 18 or 20 for both and deadband form 3 to 5 




// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors, // odometry sensors
                        &throttle_curve,
                        &steer_curve
);





