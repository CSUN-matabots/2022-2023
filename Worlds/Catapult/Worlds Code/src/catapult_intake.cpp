#include "EZ-Template/catapult_intake.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

pros::Motor catapult1(14, false);
pros::Motor catapult2(15, true);

pros::Motor intake(2, false);

pros::ADIDigitalOut launch1 = pros::ADIDigitalOut('A');
pros::ADIDigitalOut launch2 = pros::ADIDigitalOut('F');

pros::ADIDigitalIn catLimit = pros::ADIDigitalIn('H');

int counting = 0;
bool cat_set = false;


//Catapult Controls
////////////////////////////////////////////////////////////
int get_cat_vel1()   {return catapult1.get_actual_velocity();}

int get_cat_vel2()   {return catapult2.get_actual_velocity();}

double get_cat_pos1()   {return catapult1.get_position();}

double get_cat_pos2()   {return catapult2.get_position();}

int get_cat_lim()    {return catLimit.get_value();}

void stop_cats(){
    catapult1 = 0;
    catapult2 = 0;
    catapult1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    catapult2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void set_cat_vel(double speed){
    catapult1 = speed;
    catapult2 = speed;
}

void set_cat_pos1(double pos, int speed){
    catapult1.move_absolute(pos, speed);
}

void set_cat_pos2(double pos, int speed){
    catapult2.move_absolute(pos, speed);
}

void zero_cat(){
    catapult1.tare_position();
}

void zero_cat2(){
    catapult2.tare_position();
}

void reset_cat(){
    if(catLimit.get_value() == 0){
        catapult1 = 120;
        catapult2 = 120;
    }
    else if (catLimit.get_value() == 1){
        catapult1 = 10;
        catapult2 = 10;
        catapult1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        catapult2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }
}



void reset_cat_auton(){
    while(!cat_reset()){
        reset_c();
        pros::delay(100);
    }
}
void reset_c(){
    if(!catLimit.get_value()){
        catapult1 = 115;
        catapult2 = 115;
        cat_set = false;
        pros::delay(69);
    }
    else{
        catapult1=10;
        catapult2=10;
        cat_set =true;
        //start_intake();
    }   
}    
bool cat_reset(){
    if(cat_set){
        return true;
    }else {
        return false;
    }
}
void close_launch(){
    launch1.set_value(false);
    launch2.set_value(false);
}
void shoot_launch(){
    launch1.set_value(true);
    launch2.set_value(true);
    pros::delay(200);
    launch1.set_value(false);
    launch2.set_value(false);
}
void shoot_launch2(){
    launch1.set_value(true);
    launch2.set_value(true);
    catapult1 = 127;
    catapult2 = 127;
    pros::delay(200);
    launch1.set_value(false);
    launch2.set_value(false);
    reset_da_reset();
    reset_cat();
}
void reset_da_reset(){
    cat_set = false;
}
void hold_cats(){
    catapult1 = 10;
    catapult2 = 10;
    catapult1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    catapult2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
////////////////////////////////////////////////////////////

//Intake Controls
////////////////////////////////////////////////////////////
int get_intake_vel()   {return intake.get_actual_velocity();}

int get_intake_pos()   {return intake.get_position();}

void set_intake_pos(double pos, int speed){
    intake.move_absolute(pos, speed);
}

void zero_intake(){
    intake.tare_position();
}

void start_intake(){
    intake = 127;
}

void end_intake(){
    intake = 0;
}

void intake_check(){
    if (get_intake_vel() > 0){
        if(!catLimit.get_value()){
        intake = 0;
        }
    }
}
////////////////////////////////////////////////////////////



//Driver Control
///////////////////////////////////////////
void catapult_control(){
    /*
    if(master.get_digital(DIGITAL_R1)){
        catapult1 = 127;
        catapult2 = 127;
    }
    else{
        reset_cat();
    }
    */

    if(master.get_digital(DIGITAL_R2)){
        catapult1 = 127;
        catapult2 = 127;
    }
    else{
        reset_cat();
        //cat_pid();
    }
    
    
/*
if (master.get_digital(DIGITAL_X) && master.get_digital(DIGITAL_R1)){
        catapult1 = 127;
        catapult2 = 127;
        shoot_launch();
        reset_cat();
    }
*/
    

    if (master.get_digital(DIGITAL_X) && master.get_digital(DIGITAL_R2)){
        shoot_launch2();
    }
    
}

void intake_control(){
    /*
    if(master.get_digital(DIGITAL_R2)){
        intake = 127;
    }
    else if(master.get_digital(DIGITAL_DOWN)){
        intake = -127;
    }
    else {
        intake = 0;
    }
    */

    if(master.get_digital(DIGITAL_R1)){
        intake = 127;
    }
    else if(master.get_digital(DIGITAL_DOWN)){
        intake = -127;
    }
    else {
        intake = 0;
    }
    
    
}
///////////////////////////////////////////



//Catapult PID
//////////////////////////////////////////////////////////

double error = 0;
double derivative = 0;
double prevError = 0;
double kP = 0.3;
double kD = 0.7;
double average = 0;
bool reach_bot = false;
double target = 150;

void pid_part2() {
    average = (get_cat_pos1() + get_cat_pos2()) / 2;
    error = target - average;
    derivative = error - prevError;
    prevError = error;
    pros::delay(20);
    catapult1 = -(kP * error) + (kD * derivative);
    reach_bot = false;
}

void cat_pid(){
    if(!reach_bot){
        pid_part2();
    }
    else if (reach_bot || get_cat_lim()){
        hold_cats();
    }
}
void reset_reach(){
    reach_bot = false;
}
//////////////////////////////////////////////////////////