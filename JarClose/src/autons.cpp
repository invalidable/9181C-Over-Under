#include "vex.h"

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void set_timeout(float t){
  chassis.set_drive_exit_conditions(1.5, 300, t);
  chassis.set_turn_exit_conditions(1, 300, t);
  chassis.set_swing_exit_conditions(1, 300, t);
}

void auton(){
  //chassis.drive_distance(40);
  //chassis.right_swing_to_angle(180);
  //chassis.left_swing_to_angle(180);
  //chassis.turn_to_angle(0);
  Wings.set(true);
  task::sleep(200);
  Wings.set(false);
  Intake.spin(fwd, 12, volt);
  set_timeout(1500);
  chassis.drive_distance(55);
  chassis.turn_to_angle(0);
  task::sleep(200);
  chassis.drive_distance(-5);
  set_timeout(700);
  chassis.turn_to_angle(75);
  Intake.stop(hold);
  Wings.set(true);
  set_timeout(1000);
  chassis.drive_distance(25);
  set_timeout(500);
  Wings.set(false);
  chassis.drive_distance(-5);
  set_timeout(1000);
  chassis.turn_to_angle(205);
  set_timeout(1500);
  chassis.drive_distance(48);

  //drifts into the bar
  set_timeout(1000);
  chassis.left_swing_to_angle(300);

  Balance.set(true);
  chassis.drive_distance(-22);
  set_timeout(600);
  Balance.set(false);
  chassis.turn_to_angle(160);
  chassis.turn_to_angle(90);
  set_timeout(3000);
  chassis.drive_distance(15);
  chassis.turn_to_angle(75);
  Intake.spin(reverse, 12, volt);
  chassis.drive_distance(18);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}