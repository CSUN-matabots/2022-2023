#include "main.h"
#include "pros/misc.h"

pros::Motor roller(1, true);

int get_roller_vel(){
    return roller.get_actual_velocity();
}

int get_roller_pos(){
    return roller.get_position();
}

void set_roller_pos(double pos, int speed){
    roller.move_absolute(pos, speed);
}

void zero_roller(){
    roller.tare_position();
}

void change_roller(){
    roller = -127;
    pros::delay(200);
    roller = 0;
}


//Driver Control babey
///////////////////////////////////////////////////////////

void roller_control(){
    if(master.get_digital(DIGITAL_L2)){
        roller = -127;
    }
    else if (master.get_digital(DIGITAL_UP)){
        roller = 127;
    }
    else {
        roller = 0;
    }
}
    
///////////////////////////////////////////////////////////