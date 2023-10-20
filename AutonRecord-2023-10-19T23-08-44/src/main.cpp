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
// LimitSwitchC         limit         C               
// Intake               motor         18              
// Catapult             motor         2               
// Rotation             rotation      1               
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace vex;
int go;
int rotate;
bool intaking;
static bool wing1 = false;
static bool wing2 = false;
static bool last1 = false;
static bool last2 = false;
int count;
std::string save = "";
template <typename T>

std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

competition Competition;


void pre_auton(void) {
  vexcodeInit();
  Rotation.resetPosition();
}

void autonomous(void) {

}

int catafire(){
  while(true){
    if(Controller1.ButtonA.pressing())
    {
      Catapult.spinFor(vex::forward, 0.5, seconds);
      while(Rotation.angle() > 305 || Rotation.angle() < 10)
      {
        Catapult.spin(vex::forward, 100, percent);
        vex::task::sleep(50);
      }
    }
    else if(Controller1.ButtonB.pressing())
    {
      Catapult.spinFor(vex::reverse, 0.5, seconds);
    }
    else
    {
      Catapult.stop(hold);
    }
    vex::task::sleep(50);
  }
  return 0;
}

void usercontrol(void) {
  std::cout << "START" << "\n";
  vex::task catapult = task(catafire);
  while (1) {  
    //get inputs
    go = Controller1.Axis3.position(percent);
    rotate = Controller1.Axis1.position(percent);
    //modify and record inputs
    go = (int)(go + 99) / 2;
    rotate = (int)(rotate + 99) / 2;
    if(go < 10){
      save = save + "0";
      save = save + ToString(go);
    }
    else{
      save = save + ToString(go);
    }
    if(rotate < 10){
      save = save + "0";
      save = save + ToString(rotate);
    }
    else{
      save = save + ToString(rotate);
    }
    //spin the chassis
    if(go != 49 || rotate != 49){
      if(rotate == 49){
        if(Controller1.ButtonY.pressing())
        {
          FrontLeft.spin(vex::forward, go * 2 - 99, percent);
          FrontRight.spin(vex::forward, go * 2 - 99, percent);
          BackLeft.spin(vex::forward, go * 2 - 99, percent);
          BackRight.spin(vex::forward, go * 2 - 99, percent);
        }
        else{
          FrontLeft.spin(vex::forward, ((go * 2 - 99) / 1), percent);
          FrontRight.spin(vex::forward, ((go * 2 - 99) / 1), percent);
          BackLeft.spin(vex::forward, ((go * 2 - 99) / 1), percent);
          BackRight.spin(vex::forward, ((go * 2 - 99) / 1), percent);
        }
      }
      else{
        if(Controller1.ButtonY.pressing())
        {
          FrontLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2), percent);
          FrontRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2), percent);
          BackLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2), percent);
          BackRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2), percent);
        }
        else{
          FrontLeft.spin(vex::forward, ((go * 2 - 99) / 1) + ((rotate * 2 - 99) / 2), percent);
          FrontRight.spin(vex::forward, ((go * 2 - 99) / 1) - ((rotate * 2 - 99) / 2), percent);
          BackLeft.spin(vex::forward, ((go * 2 - 99) / 1) + ((rotate * 2 - 99) / 2), percent);
          BackRight.spin(vex::forward, ((go * 2 - 99) / 1) - ((rotate * 2 - 99) / 2), percent);
        }
      }
    }
    else{
      FrontLeft.stop(brake);
      FrontRight.stop(brake);
      BackLeft.stop(brake);
      BackRight.stop(brake);
    }
    if(Controller1.ButtonL2.pressing())
    {
      if(last1 == false)
      {
        last1 = true;
        if(wing1 == true){
          wing1 = false;
          save = save + "0";
          Flap1.set(false);
        }
        else{
          wing1 = true;
          save = save + "1";
          Flap1.set(true);
        }
      }
      else{
        if(wing1 == true){
          save = save + "1";
        }
        else{
          save = save + "0";
        }
      }
    }
    else{
      last1 = false;
      if(wing1 == true){
        save = save + "1";
      }
      else{
        save = save + "0";
      }
    }
    if(Controller1.ButtonR2.pressing())
    {
      if(last2 == false){
        last2 = true;
        if(wing2 == true){
          wing2 = false;
          save = save + "0";
          Flap2.set(false);
        }
        else{
          wing2 = true;
          save = save + "1";
          Flap2.set(true);
        }
      }
      else{
        if(wing2 == true){
          save = save + "1";
        }
        else{
          save = save + "0";
        }
      }
    }
    else{
      last2 = false;
      if(wing2 == true){
        save = save + "1";
      }
      else{
        save = save + "0";
      }
    }
    if(Controller1.ButtonL1.pressing())
    {
      Intake.spin(vex::forward, 100, percent);
    }
    else if(Controller1.ButtonR1.pressing())
    {
      Intake.spin(vex::reverse, 100, percent);
    }
    else
    {
      Intake.stop(hold);
    }
    if(save.length() > 400){
      std::cout << save << "\n";
      save = "";
    }
    wait(20, msec);
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

