
#include "coloursVision.h"
#include "main.h"


// Signatures for the scoreing blocks | Red, Yelllow, Blue, Clear, Gray |


pros::vision_signature_s_t RED_SIG =
    pros::Vision::signature_from_utility(
        1,
        11343, 13171, 12257,
        -2019, -1355, -1687,
        3.000,
        0




    );  // THIS IS A PAIN TO LEARN :sob:




pros::vision_signature_s_t BLUE_SIG =
    pros::Vision::signature_from_utility(
        2,
        -2849, -2437, -2643,
        3837, 4229, 4033,
        3.000,
        0


    );


pros::vision_signature_s_t YELLOW_SIG =
    pros::Vision::signature_from_utility(
        3,
        2059, 2369, 2214,
        -4805, -4593, -4699,
        3.000,
        0
    );


pros::vision_signature_s_t GREY_SIG =
    pros::Vision::signature_from_utility(
        4,
        -51 , 51, 0,
        -51, -51, 0,
        3.000,
        0
    );


pros::vision_signature_s_t CLEAR_SIG =
    pros::Vision::signature_from_utility(
        5,
        83, 181, 132,
        835, 1025, 930,
        3.000,
        0
    );







