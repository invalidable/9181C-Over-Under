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
// FrontLeft            motor         18              
// FrontRight           motor         3               
// BackLeft             motor         20              
// BackRight            motor         1               
// Controller1          controller                    
// Flap1                digital_out   A               
// Flap2                digital_out   B               
// Intake               motor         7               
// Catapult             motor         17              
// Rotation             rotation      10              
// MiddleLeft           motor         19              
// MiddleRight          motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"
#include <string.h>
#include <string>
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
string autonflap1 = "";
string autonflap2 = ""; 
static bool last1 = false;
static bool last2 = false;
int count;
//216100216100216100216100216100216100216100216100216100216100216200216100216100216100216100216100216100216100216100216100216600217600218000218000218000218000217700217200217200217200217100217300217300217300217300214900214900204900204900204900184900154900134900134900134900114900084900074900074900074900004900004900004900004900004900114900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900493700523700523700543700543700553500553600553600553600553500553500553500553500553500553400553200563100563100552800552600552700562700562700562700593700664900714900714900854900894900914900914900914900914900914900924900924900924900924900914900914900804900804900804900497900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499901499901499901499901499901499901499901499901499901499901499901499901499901499901499901499901499901499501494901494901494901494901494901494901494901494901494901494901494901494901494801494001493001492201492201491201490401490001490001490001490001490501490701490801490801490801490801490801490801490801490801490901492101493801493801493801494901494901494901494901494901494901494901494901494901494901494901494901494901494901514901524901534901534901534901534901534901535501535701535701535901536001545901555901555901555901645701645601645601645601645501645501645501645501645501645501645501645401645401645401645401645401635401645401645401645401645701646101646901646901646901648001648501648801648801648801649501639801649901649901649901639901649901649901649901649901649901649901619901619901579901529901499901499901499901499901499901499901499901499901499901499901499901499701499701494901494901494901494901494901494901494901494901494201494201491401490001490001490001490001490001490001490001490001490001490001490001490700493300493300493300494900494900494900494900494900494900494900494900494900494900494900495100495100495100495100495400496000496300496300496300496400496300496300496300496300496200496200496200496200496300496400496400496400496400496400496800497400497800497800498300498900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900499900498100497900497900497900497900498100498900498900499600499600499900499900499900499900494900494900494900494900494900494900504900504900504900504900504300504400514300514300514400524400534400534400534400524500534600534500534500534500554400554500554500554500554500554500554500554500554500554500554500574600574900574900574900574900574900594900614900614900624900624900624900624900624900624900624700624500644400644400644400654200644200644200644200644200653700653500643500643500643500653500643500653500653500653500643600643600643600643600643600643800644800644900644900644900644900644900644900644900644900644900644900654900654900644900644900644900655300655300655300645300655000644900644900644900654900644900654900654900654900644900654900654900654900644900654900654900644900644900644900654900644900644900644900654900644900654900644900644900644900644900644900644900644900644900644900644600644600644600644600644600644600644600644600644600644600644600644600644600644600604900594900594900594900594900594900594900594900594900594900594900594900594900594900594900574900564900564900564900564900564900564900564900564900564900564900564900554900554900544900514900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900494900
std::string saveRun = "994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900994900";
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
  while (1) {
    if(saveRun.length() != 0){
      // spin chassis
      go = (saveRun[0] - 48) * 10 + saveRun[1] - 48;
      rotate = (saveRun[2] - 48) * 10 + saveRun[3] - 48;
      autonflap1 = saveRun[4];
      autonflap2 = saveRun[5];
      if(go != 49 || rotate != 49){
        if(rotate == 49){
          FrontLeft.spin(vex::forward, go * 2 - 99, percent);
          FrontRight.spin(vex::forward, go * 2 - 99, percent);
          MiddleLeft.spin(vex::forward, go * 2 - 99, percent);
          MiddleRight.spin(vex::forward, go * 2 - 99, percent);
          BackLeft.spin(vex::forward, go * 2 - 99, percent);
          BackRight.spin(vex::forward, go * 2 - 99, percent);
        }
        else{
          FrontLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2.3), percent);
          FrontRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2.3), percent);
          MiddleLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2.3), percent);
          MiddleRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2.3), percent);
          BackLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2.3), percent);
          BackRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2.3), percent);
        }
      }
      else{
        FrontLeft.stop(brake);
        FrontRight.stop(brake);
        MiddleLeft.stop(brake);
        MiddleRight.stop(brake);
        BackLeft.stop(brake);
        BackRight.stop(brake);
      }
      if(autonflap1 == "1"){
        Flap1.set(true);
      }
      else{
        Flap1.set(false);
      }
      if(autonflap2 == "1"){
        Flap2.set(true);
      }
      else{
        Flap2.set(false);
      }
      //delete read parts of save file
      for (int i = 0; i < 6; i++) {
        saveRun.erase(saveRun.begin());
      }
    }
    else{
      FrontLeft.stop();
      FrontRight.stop();
      MiddleLeft.stop();
      MiddleRight.stop();
      BackLeft.stop();
      BackRight.stop();
    }
    wait(20, msec);
  }
}

int catafire(){
  Catapult.setVelocity(90, percent);
  while(true){
    if(Controller1.ButtonA.pressing())
    {
      Catapult.spin(vex::forward, 90, percent);
    }
    else if(Controller1.ButtonX.pressing()){    
      Catapult.spinFor(vex::forward, 1, turns);
    }
    else if(Controller1.ButtonB.pressing()){
      Catapult.spin(vex::reverse, 90, percent);
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
        FrontLeft.spin(vex::forward, go * 2 - 99, percent);
        FrontRight.spin(vex::forward, go * 2 - 99, percent);
        MiddleLeft.spin(vex::forward, go * 2 - 99, percent);
        MiddleRight.spin(vex::forward, go * 2 - 99, percent);
        BackLeft.spin(vex::forward, go * 2 - 99, percent);
        BackRight.spin(vex::forward, go * 2 - 99, percent);
      }
      else{
        FrontLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2.3), percent);
        FrontRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2.3), percent);
        MiddleLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2.3), percent);
        MiddleRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2.3), percent);
        BackLeft.spin(vex::forward, ((go * 2 - 99)) + ((rotate * 2 - 99) / 2.3), percent);
        BackRight.spin(vex::forward, ((go * 2 - 99)) - ((rotate * 2 - 99) / 2.3), percent);
      }
    }
    else{
      FrontLeft.stop(brake);
      FrontRight.stop(brake);
      MiddleLeft.stop(brake);
      MiddleRight.stop(brake);
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
    if(Controller1.ButtonR1.pressing())
    {
      Intake.spin(vex::forward, 100, percent);
    }
    else if(Controller1.ButtonL1.pressing())
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

