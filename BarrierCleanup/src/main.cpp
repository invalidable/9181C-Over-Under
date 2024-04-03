#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         1               
// MiddleLeft           motor         2               
// BackLeft             motor         3               
// FrontRight           motor         8               
// MiddleRight          motor         9               
// BackRight            motor         10              
// Puncher              motor         20              
// Intake               motor         11              
// Inertial             inertial      16              
// Controller1          controller                    
// Wings                digital_out   G               
// Balance              digital_out   H               
// PuncherB             motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;
Drive chassis(
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
ZERO_TRACKER_NO_ODOM,
motor_group(FrontLeft, MiddleLeft, BackLeft),
motor_group(FrontRight, MiddleRight, BackRight),
//Inertial port number
PORT16,
//Wheel diameter
3.25,
//External gear ratio
0.6,
//Gyro
360,
//ignore these, they are for odom
PORT1, -PORT2, PORT3, PORT4, 3, 2.75, -2, 1, -2.75, 5.5);

bool auto_started = false;

void pre_auton(void) {
  vexcodeInit();
  default_constants();
}

void autonomous(void) {
  auto_started = true;
  auton();
}

void usercontrol(void) {
  while (1) {
    wait(2000, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
