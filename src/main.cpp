#include "main.h"
#include "robotConfigs.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include <cstdint>
#include "motorTemp.hpp"
#include <string>

/*
V0.1.4

Last change: 11/15/2026


*    - Debugging to see why robot screen shows DATA ABORT
TODO: - Find out whats causing DATA ABORT on robot?? 
! Idk if the issue has been fixed?

TODO: - Test and fix Yahyas code? 11/13/2026 - Person didn't show up


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




// Speeds for motors
const int MaxSpeed = 127;
const int HalfSpeed = 64;
const int Stop = 0;


//? Maybe remove this since this really isn't necessary to have


// Time Limits for auton 15s period and 1:45 for driver control
const uint32_t DRIVER_TIME_LIMIT_MS = 105000; // 1 minute and 45 seconds in milliseconds
const uint32_t AUTON_TIME_LIMIT_MS = 15000; // 15 seconds in milliseconds


MotorMonitor MotorTemps;



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
    pros::delay(50);
    chassis.calibrate(); // calibrate sensors
    
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::screen::print(pros::E_TEXT_MEDIUM, 0, "X: %f", chassis.getPose().x); // x
            pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Y: %f", chassis.getPose().y); // y
            pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Theta: %f", chassis.getPose().theta); // heading
            // Drivetrain motor temperatures
            pros::screen::print(pros::E_TEXT_MEDIUM, 4, "LeftBackTemp: %s F",
                std::to_string(MotorTemps.leftBackTemp).c_str());

            pros::screen::print(pros::E_TEXT_MEDIUM, 5, "LeftFrontTemp: %s F",
                std::to_string(MotorTemps.leftFrontTemp).c_str());

            pros::screen::print(pros::E_TEXT_MEDIUM, 6, "RightBackTemp: %s F",
                std::to_string(MotorTemps.rightBackTemp).c_str());

            pros::screen::print(pros::E_TEXT_MEDIUM, 7, "RightFrontTemp: %s F",
                std::to_string(MotorTemps.rightFrontTemp).c_str());
            
            // delay to save resources

            pros::delay(20);
        }
    });
}


/*
void initialize() {
    pros::delay(50);  bnm,.bnm,./ghjkl;SSASDFtrtt0-=-0890-=0---=
    chassis.calibrate(false); // calibrate sensors
    
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::screen::print(pros::E_TEXT_MEDIUM, 0, "X: %f", chassis.getPose().x); // x
            pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Y: %f", chassis.getPose().y); // y
            pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Theta: %f", chassis.getPose().theta); // heading
            // Drivetrain motor temperatures
            pros::screen::print(pros::E_TEXT_MEDIUM, 4, "LeftBackTemp: %s F",
                std::to_string(MotorTemps.leftBackTemp).c_str());

            pros::screen::print(pros::E_TEXT_MEDIUM, 5, "LeftFrontTemp: %s F",
                std::to_string(MotorTemps.leftFrontTemp).c_str());

            pros::screen::print(pros::E_TEXT_MEDIUM, 6, "RightBackTemp: %s F",
                std::to_string(MotorTemps.rightBackTemp).c_str());

            pros::screen::print(pros::E_TEXT_MEDIUM, 7, "RightFrontTemp: %s F",
                std::to_string(MotorTemps.rightFrontTemp).c_str());
            
            // delay to save resources

            pros::delay(20);
        }
    });
}
*/




void disabled(){}




void competition_initialize() {}





void autonomous() {
    pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Starting turn");
    chassis.turnToHeading(90, 10000);
    chassis.waitUntilDone();
    chassis.getPose();


}



void opcontrol() {
    while (true) {
        // get left y and right x positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);


        // move the robot
        chassis.arcade(-leftY, rightX, false, 0.5);

        MotorTemps.update();
   
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