#include "main.h"
#include "robotConfigs.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include <cstdint>
/*


V1.1.3
TEST

Last change: 11/10/2026


*    - Debugging to see why robot screen shows DATA ABORT
TODO: - Find out whats causing DATA ABORT on robot


*/




/*
* a
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



void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    pros::delay(50);
    chassis.calibrate(false); // calibrate sensors
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
}


/*
static pros::Task screen_task([]() {
        while (true) {
            // Display robot coordinates
            pros::lcd::print(0, "X: %f", chassis.getPose().x);
            pros::lcd::print(1, "Y: %f", chassis.getPose().y);
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
            // Drivetrain motor temperatures
            pros::lcd::set_text(4, "LeftBackTemp: " +
                std::to_string(MotorTemps.leftBackTemp) + " C");

            pros::lcd::set_text(5, "LeftFrontTemp: " +
                std::to_string(MotorTemps.leftFrontTemp) + " C");

            pros::lcd::set_text(6, "RightBackTemp: " +
                std::to_string(MotorTemps.rightBackTemp) + " C");

            pros::lcd::set_text(7, "RightFrontTemp: " +
                std::to_string(MotorTemps.rightFrontTemp) + " C");


            // delay to save resources
            pros::delay(20);
        }
    });


*/




void autonomous() {
    pros::lcd::set_text(1, "Starting turn");

    chassis.turnToHeading(90, 3000);

    pros::lcd::set_text(2, "Turn completed");
    // chassis.turnToHeading(270, 4000); // turns the robot to face 270 degrees,
                                  // with a timeout of 4000 ms
}




void disabled(){}




void competition_initialize() {}




void opcontrol() {
    while (true) {
        // get left y and right x positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);


        // move the robot
        chassis.arcade(leftY, rightX, false, 0.5);


        // ! Change the trigger button to another button later
                // Intake controls
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intake.move(MaxSpeed);
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake.move(-MaxSpeed);
        }
        else {
            intake.move(Stop);
        }


          // delay to save resources
        pros::delay(25);
    }


}

