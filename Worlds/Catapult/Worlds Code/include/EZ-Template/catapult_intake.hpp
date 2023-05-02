#pragma once

int get_cat_vel1();
int get_cat_vel2();
double get_cat_pos1();
double get_cat_pos2();
int get_cat_lim();
void set_cat_vel(double speed);
void stop_cats();
void set_cat_pos1(double pos, int speed);
void set_cat_pos2(double pos, int speed);
void zero_cat();
void zero_cat2();
void reset_cat();
void reset_cat_auton();
void close_launch();
void shoot_launch();
void shoot_launch2();
bool cat_reset();
void reset_c();
void intake_check();
void reset_da_reset();
void cat_pid();
void pid_part2();
void hold_cats();
void reset_reach();


int get_intake_vel();
int get_intake_pos();
void set_intake_pos();
void zero_intake();
void start_intake();
void end_intake();

void catapult_control();
void intake_control();