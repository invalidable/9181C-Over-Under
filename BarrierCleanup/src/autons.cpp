#include "vex.h"

void default_constants(){
  chassis.set_drive_constants(12, 1.5, 0.005, 10, 0);
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
  set_timeout(600);
  chassis.right_curve_to_angle(45, 0.5);
  set_timeout(400);
  chassis.drive_distance(-900);
  set_timeout(600);
  chassis.turn_to_angle(35);
  chassis.drive_distance(15);
  chassis.turn_to_angle(300);
  chassis.drive_distance(-8);

  //matchloading
  Puncher.spinFor(fwd, 44, turns, 120, rpm, false);
  PuncherB.spinFor(fwd, 44, turns, 120, rpm, true);
  Puncher.spin(fwd, 5, volt);
  PuncherB.spin(fwd, 5, volt);

  //barrier cleanup
  set_timeout(600);
  chassis.turn_to_angle(305);
  set_timeout(1000);
  chassis.drive_distance(58);
  set_timeout(600);
  Puncher.stop();
  PuncherB.stop();
  chassis.turn_to_angle(230);
  Wings.set(true);
  set_timeout(1500);
  chassis.drive_distance(900);
  set_timeout(800);
  chassis.drive_distance(-15);
  Wings.set(false);
  chassis.turn_to_angle(170);
  chassis.drive_distance(32);
  set_timeout(800);
  chassis.left_curve_to_angle(310, 0.15);
  chassis.drive_distance(55);
  Wings.set(true);
  chassis.drive_distance(20);
  Wings.set(false);
  
  //left push
  chassis.left_slow_curve_to_angle(35, 0.7);
  chassis.drive_distance(900);
  set_timeout(600);
  chassis.drive_distance(-35);
  chassis.turn_to_angle(15);
  set_timeout(800);
  chassis.drive_distance(900);
  set_timeout(600);
  chassis.drive_distance(-20);
  //chassis.drive_distance(900);
  //chassis.drive_distance(-20);
  chassis.turn_to_angle(100);

  //front cleanup
  chassis.drive_distance(26);
  Wings.set(true);
  chassis.right_slow_curve_to_angle(315, 0);
  Wings.set(false);
  set_timeout(700);
  chassis.drive_distance(900);
  wait(200, msec);
  chassis.turn_to_angle(350);
  chassis.drive_distance(-40);
  chassis.turn_to_angle(50);
  chassis.drive_distance(30);
  chassis.turn_to_angle(315);
  Wings.set(true);
  set_timeout(1200);
  chassis.drive_distance(900);
  set_timeout(700);
  Wings.set(false);
  chassis.drive_distance(-40);
  chassis.turn_to_angle(225);
  chassis.drive_distance(-50);
  chassis.turn_to_angle(270);
  Wings.set(true);
  chassis.left_curve_to_angle(315, 0.6);
  set_timeout(1000);
  chassis.drive_distance(900);
  set_timeout(600);
  Wings.set(false);
  chassis.drive_distance(-12);

  //right push
  chassis.turn_to_angle(35);
  set_timeout(800);
  chassis.drive_distance(70);
  chassis.turn_to_angle(315);
  chassis.right_curve_to_angle(235, 0.5);
  chassis.drive_distance(900);
  chassis.drive_distance(-20);
  chassis.turn_to_angle(255);
  chassis.drive_distance(900);
  chassis.drive_distance(-20);
  chassis.drive_distance(900);
  chassis.drive_distance(-20);
  chassis.turn_to_angle(0);
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