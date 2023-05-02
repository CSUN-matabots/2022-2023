#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

pros::ADIDigitalOut wall = pros::ADIDigitalOut('G');
pros::ADIDigitalOut expand1 = pros::ADIDigitalOut('E');
pros::ADIDigitalOut expand2 = pros::ADIDigitalOut('F');

int counted = 0;

void open_wall(){
    wall.set_value(true);
    pros::delay(500);
    wall.set_value(false);
    pros::delay(500);
    wall.set_value(true);
    pros::delay(500);
    wall.set_value(false);
    pros::delay(500);
    wall.set_value(true);
    pros::delay(500);
    wall.set_value(false);
    pros::delay(500);
    
    
}
void close_wall(){
    wall.set_value(false);
}

void expand(){
    expand1.set_value(true);
    expand2.set_value(true);
    pros::delay(400);
    expand1.set_value(false);
    expand2.set_value(false);
    pros::delay(400);
    expand1.set_value(true);
    expand2.set_value(true);
    pros::delay(400);
    expand1.set_value(false);
    expand2.set_value(false);
    pros::delay(400);
    expand1.set_value(true);
    expand2.set_value(true);
    pros::delay(400);
    expand1.set_value(false);
    expand2.set_value(false);
}

void close_expand(){
    expand1.set_value(false);
    expand2.set_value(false);
}

//Driver Controll
////////////////////////////////////////////

void wall_expand_control(){
    if(master.get_digital(DIGITAL_B)){
        open_wall();
    }

    if(master.get_digital(DIGITAL_Y)){
        expand();
    }

}

////////////////////////////////////////////

