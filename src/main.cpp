#include "main.h"
#include "pros/misc.hpp"
#include "math.h"
#include <string>
#include <cmath>
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "robotConfigs.h" // IWYU pragma: keep
#include "coloursVision.h" // IWYU pragma: keep




/*

V1.1.3

Last change: 9/18/2026 

*    - Added notes about the Cascade bot    

*/


/*
* 
! Alerts
? Query 
TODO: 
*/



// Assets for path(s) reworking to use the META path.
ASSET(BlueAlliance_txt);

pros::Controller master(pros::E_CONTROLLER_MASTER);


// Variables and constants
const int MaxSpeed = 127;
const int HalfSpeed = 64;
const int Stop = 0; 

//? Maybe remove the Time Limits in general?? or not

// Time Limits for auton 15s period and 1:45 for driver control
const uint32_t DRIVER_TIME_LIMIT_MS = 105000; // 1 minute and 45 seconds in milliseconds
const uint32_t AUTON_TIME_LIMIT_MS = 15000; // 15 seconds in milliseconds


void on_center_button() {
    static bool pressed = false;
    pressed = !pressed;
    if (pressed) {
        pros::lcd::set_text(2, "I was pressed!");
    } else {
        pros::lcd::clear_line(2);
    }
}


/*
! ADD THIS initialize function if the rotation sensors are figured out to be negative or positive.
void initialize() {

    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
    
    // sets sigs for the vision sensor
    vision_sensor.set_signature(1, &RED_SIG);
    vision_sensor.set_signature(2, &BLUE_SIG);
    vision_sensor.set_signature(3, &YELLOW_SIG);
    vision_sensor.set_signature(4, &GREY_SIG);
    vision_sensor.set_signature(5, &CLEAR_SIG);
}


*/


// initialize function. Runs on program startup
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate();
    while (true) { // infinite loop
        //! prints measurements from the rotation sensor
        pros::lcd::print(1, "Vertical Sensor: %i", vertical_sensor.get_position());
        pros::lcd::print(1, "Horizontal Sensor: %i", horizontal_sensor.get_position());
        pros::delay(10); // delay to save resources. DO NOT REMOVE

        // Add this code later to figure out if its negative or positive.
    } 
}




void disabled(){}


void competition_initialize() {}

/*

void autonomous() {


    
    chassis.setPose(30, 40, 0); // Sets the starting position of the robot
    chassis.moveToPoint(49.451, 0.137, 2000); // Back and forth to change the quadrant color
    chassis.moveToPoint(69.609,-1.483, 2000);
    pros::delay(750);
    
    

    chassis.follow(BlueAlliance_txt, 10, 1000000);
    // remove after tuning PID
    

}


*/

void autonomous() {
    //! Tune the turning PID!!
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 100000);
}






void opcontrol() {
    while (true) {
        // get left y and right x positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX, false, 0.5);

        // ! Change the trigger button to another button later
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            intake.move(MaxSpeed);
        
    
        }else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake.move(HalfSpeed);

        }else {
            intake.move(Stop);
        }

          // delay to save resources
        pros::delay(25);
    }

}



