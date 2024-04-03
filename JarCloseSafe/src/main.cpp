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

static bool wingActivated = false; //Toggling the wings
static bool wingAlreadyPressed = false; //Only sense button press, not hold
static bool balanceActivated = false; //Toggling the balance
static bool balanceAlreadyPressed = false; //Only sense button press, not hold

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
    chassis.control_arcade();
    if(Controller1.ButtonL1.pressing()) //Spins the intake
    {
      Intake.spin(vex::forward, 12, volt);
    }
    else if(Controller1.ButtonR1.pressing())
    {
      Intake.spin(vex::reverse, 12, volt);
    }
    else
    {
      Intake.stop(hold);
    }
    if(Controller1.ButtonX.pressing() || Controller1.ButtonA.pressing()) //Two controlling buttons for redundancy
    {
      Puncher.spin(vex::forward, 130, rpm);
      PuncherB.spin(vex::forward, 130, rpm);
    }
    else if(Controller1.ButtonB.pressing()) //Reverse button to get it unjammed
    {
      Puncher.spin(vex::reverse, 50, percent);
      PuncherB.spin(vex::reverse, 50, percent);
    }
    else{
      Puncher.stop(hold);
      PuncherB.stop(hold);
    }
    if(Controller1.ButtonR2.pressing())
    {
      if(wingAlreadyPressed == false) //Check if the R2 Button is being held versus pressed for the first time. Avoids rapid re-toggling of the wings
      {
        wingAlreadyPressed = true;
        if(wingActivated == true){ //If the wings are on, turn them off. If they are off, turn them on
          wingActivated = false;
          Wings.set(false);
        }
        else{
          wingActivated = true;
          Wings.set(true);
        }
      }
    }
    else{
      wingAlreadyPressed = false;
    }
    if(Controller1.ButtonL2.pressing())
    {
      if(balanceAlreadyPressed == false) //Check if the R2 Button is being held versus pressed for the first time. Avoids rapid re-toggling of the wings
      {
        balanceAlreadyPressed = true;
        if(balanceActivated == true){ //If the wings are on, turn them off. If they are off, turn them on
          balanceActivated = false;
          Balance.set(false);
        }
        else{
          balanceActivated = true;
          Balance.set(true);
        }
      }
    }
    else{
      balanceAlreadyPressed = false;
    }
    vex::task::sleep(50);
    wait(20, msec);
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
