/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\alex_                                            */
/*    Created:      Mon Aug 14 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         11              
// FrontRight           motor         20              
// BackLeft             motor         19              
// BackRight            motor         12              
// Controller1          controller                    
// Flap1                digital_out   A               
// Flap2                digital_out   B               
// Catapult             motor         2               
// Intake               motor         18              
// Rotation             rotation      1               
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace vex;
int go;
int rotate;
int count = 0;
string wing1 = "";
string wing2 = "";

std::string save = "494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494901494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494911494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900";
// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  while (1) {
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  while(count > 0){
    count = count - 1;
    Catapult.spinFor(vex::forward, 0.5, seconds);
    while(Rotation.angle() > 305 || Rotation.angle() < 10)
    {
      Catapult.spin(vex::forward, 100, percent);
      vex::task::sleep(50);
    }
    Catapult.stop(hold);
    vex::task::sleep(500);
  }
  while (1) {
    if(save.length() != 0){
      // spin chassis
      go = (save[0] - 48) * 10 + save[1] - 48;
      rotate = (save[2] - 48) * 10 + save[3] - 48;
      wing1 = save[4];
      wing2 = save[5];
      cout << go << endl;
      cout << rotate << endl;
      if(go != 49 || rotate != 49){
        if(rotate == 49){
          cout << "1" << endl;
          FrontLeft.spin(vex::forward, go * 2 - 99, percent);
          FrontRight.spin(vex::forward, go * 2 - 99, percent);
          BackLeft.spin(vex::forward, go * 2 - 99, percent);
          BackRight.spin(vex::forward, go * 2 - 99, percent);
        }
        else{
          cout << "2" << endl;
          FrontLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2), percent);
          FrontRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2), percent);
          BackLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2), percent);
          BackRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2), percent);
        }
      }
      else{
        cout << "3" << endl;
        FrontLeft.stop(brake);
        FrontRight.stop(brake);
        BackLeft.stop(brake);
        BackRight.stop(brake);
      }
      if(wing1 == "1"){
        Flap1.set(true);
      }
      else{
        Flap1.set(false);
      }
      if(wing2 == "1"){
        Flap2.set(true);
      }
      else{
        Flap2.set(false);
      }
      //delete read parts of save file
      for (int i = 0; i < 6; i++) {
        save.erase(save.begin());
      }
    }
    else{
      FrontLeft.stop();
      FrontRight.stop();
      BackLeft.stop();
      BackRight.stop();
    }
    wait(20, msec); // Sleep the task for a short amount of time to
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {

    wait(100, msec);
  }
}

