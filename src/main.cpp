#include "main.h"
#include "pros/misc.hpp"
#include "math.h"
#include <string>
#include <cmath>
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "robotConfigs.h" // IWYU pragma: keep
#include "coloursVision.h" // IWYU pragma: keep




/*

V1.1.4

Last change: 6/22/2026 

    - Added a WIP (Work In Progress) auton selector. ps still in the works
    - removed the defines with #pragma once 
*/



// Assets for path(s) reworking to use the META path.
ASSET(BlueAllence_txt);


pros::Controller master(pros::E_CONTROLLER_MASTER);


// Variables and constants



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

void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate();
    while (true) { // infinite loop
        // print measurements from the rotation sensor
        pros::lcd::print(1, "Vertical Sensor: %i", vertical_sensor.get_position());
        pros::lcd::print(1, "Horizontal Sensor: %i", horizontal_sensor.get_position());
        pros::delay(10); // delay to save resources. DO NOT REMOVE

        // Add this code later to figure out if its negative or positive.
    } 
}



*/


// initialize function. Runs on program startup
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




void disabled(){}


void competition_initialize() {}


void autonomous() {
    chassis.follow(BlueAllence_txt, 10, 1000000);
    // remove after tuning PID
    

}






void opcontrol() {
    while (true) {
        // get left y and right x positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX, false, 0.5);

      


        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        
    
        }  else{

        }

          // delay to save resources
        pros::delay(25);
    }

}



