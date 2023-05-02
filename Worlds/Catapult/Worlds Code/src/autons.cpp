#include "EZ-Template/catapult_intake.hpp"
#include "EZ-Template/roller.hpp"
#include "EZ-Template/util.hpp"
#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;


///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!

void roller_shot_no_tape(){

  reset_cat_auton();
  

  //pros::delay(1000);

  //shoot_launch2();
  /*
  set_cat_vel(100);
  if(get_cat_lim() > 5){
    stop_cats();
  }
  */
  /*
  zero_cat();
  zero_cat2();
  set_cat_pos1(1000, 100);
  set_cat_pos2(1000, 100);
  */
  
  ///*
  pros::delay(200);


  chassis.set_drive_pid(2.5, DRIVE_SPEED);
  chassis.wait_drive();

  change_roller();

  chassis.set_drive_pid(-2.5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(230,  DRIVE_SPEED);
  chassis.wait_drive();

  start_intake();
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_until(10);
  chassis.set_max_speed(20);
  chassis.wait_drive();
  end_intake();

  chassis.set_turn_pid(135, DRIVE_SPEED);
  chassis.wait_drive();

  shoot_launch2();
  pros::delay(100);

  chassis.set_turn_pid(45, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, 100);
  chassis.wait_drive();


  chassis.set_drive_pid(-7, 50);
  chassis.wait_drive();
  chassis.set_turn_pid(-105, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, 70);
  chassis.wait_drive();
  

  change_roller();
  //*/

}

void roller_shot_tape(){
  
  //Brings catapult down and gets it ready to launch. Has 2 preloads in already
  reset_cat_auton();

  //waits for 200msec before moving to next line (cat may still be lowering)
  pros::delay(200);

  //Moves forward for 2 inches at 110 voltage. Does not continue until function finishes
  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();

  //Swings the robot to have roller wheel touch roller. Does not move to next line until it has reached this distance
  chassis.set_swing_pid(ez::LEFT_SWING, 115, SWING_SPEED);
  chassis.wait_drive();

  pros::delay(300);

  //changes roller
  change_roller();

  //start intake at full voltage
  //start_intake();

  //checks to see if catapult is down
  intake_check();

  //moves the robot back 2 inches
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();

  //turns the robot to face 225 degrees (supposed to be parallel to auton line)
  chassis.set_turn_pid(225, DRIVE_SPEED);
  chassis.wait_drive();

  //moves forward 15 inches at 110 voltage, at 10 inches, change voltage to 50 for remainder
  chassis.set_drive_pid(15, 110);
  //chassis.wait_until(10);
  //chassis.set_max_speed(50);
  chassis.wait_drive();

  //turn to 135 degrees
  chassis.set_turn_pid(135, DRIVE_SPEED);
  chassis.wait_drive();

  //stop intake
  end_intake();

  //shoot using pneumatic and cat. Wait 500 msec to let it launch
  shoot_launch2();
  pros::delay(500);

  chassis.set_turn_pid(145, TURN_SPEED);
  chassis.wait_drive();

  
  //moves back 20 inches to hypothetically hit wall in the back and line up with disks on low goal to pick up
  chassis.set_drive_pid(20, DRIVE_SPEED);
  stop_cats();
  chassis.wait_drive();

  

  reset_da_reset();

  /*
  //drives forward for 50 inches at 110 volts to pick up disks
  chassis.set_drive_pid(50, DRIVE_SPEED);
  chassis.wait_drive();

  //turns to 135 degrees yet again (facing high goal)
  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  //drives for 15 inches at 110 volts to get as close as can be to auton line 
  chassis.set_drive_pid(-15, DRIVE_SPEED);
  chassis.wait_drive();

  //shoots cat and pneumatics to score disks 
  shoot_launch2();
  pros::delay(500);
  */
  //start intake again at 127 volts
  //start_intake();

  


}

void roller_shot_taped(){
   //Brings catapult down and gets it ready to launch. Has 2 preloads in already
  reset_cat_auton();

  //waits for 200msec before moving to next line (cat may still be lowering)
  pros::delay(200);

  //Moves forward for 2 inches at 110 voltage. Does not continue until function finishes
  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();

  //Swings the robot to have roller wheel touch roller. Does not move to next line until it has reached this distance
  chassis.set_swing_pid(ez::LEFT_SWING, 115, SWING_SPEED);
  chassis.wait_drive();

  pros::delay(300);

  //changes roller
  change_roller();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();



  chassis.set_drive_pid(-120, DRIVE_SPEED);
  chassis.wait_drive();


}


// . . .