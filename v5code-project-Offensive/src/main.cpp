/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\alex_    W Alex                                  */
/*    Created:      Mon Aug 14 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         18              
// FrontRight           motor         8               
// BackLeft             motor         20              
// BackRight            motor         10              
// Controller1          controller                    
// Intake               motor         17              
// Catapult             motor         5               
// Rotation             rotation      11              
// MiddleLeft           motor         19              
// MiddleRight          motor         9               
// Inertial1            inertial      1               
// Flap1                digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

//Just some general stuff, nothing to worry about
#include "vex.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace vex;

////////////////////////////////////////////// GENERAL VARIABLES ///////////////////////////////////////////////////

int count; //Basic utility variables for iteration
int num;

int go; //Forward Power
int rotate; //Rotation Power

static bool wingActivated = false; //Toggling the wings
static bool alreadyPressed = false; //Only sense button press, not hold

///////////////////////////////////////// RECORDING SYSTEM VARIABLES ///////////////////////////////////////////////

std::string newSave = ""; //The save to write the new recording to during recording
std::string save = "4949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000494901100004949011000049490110000484901100004549011000045490110000404901100003749011000033490110000294901100002549011000025490110000224901100002149011000021490110000224901100002249011000022490110000224901100002149011000021490110000214901100002249011000022490110000214901100002149011000021490110001224601100012244011000122450110001224501100012145011000121450110001214501100011848011000112480110000124801100000348010000100480100002004801000030048010000400460100005004601000060045010000700440100008004401000090044010000900460100010004901000100049010001100490100011004901000110049010001100490100012004901000120049010001200490100012001401000120014010001200000100012000001000130000010001505090100017163601000191636010002220490100025234901000292549010003325490100037234901000422049010004620490100050004901000540049010005800490100061004901000620049010006300490100064004901000640049010006300490100063004901000620049010006200490100062004901000610049010006100490100061004901000610043010006100090100061000901000620000010006500000100067000001000680000010006900220100069004901000700049010007100490100073004901000750049010007600490100077004901000781749010007849490100078494901000788049010007890490100079994901000799949010008099490100080994901000809949010008099490100080995001000809953010008099530100080996901000809978010008099780100080999000000809990000008049990000080499900000804999000008049990000080499900000794999000007749990000075499900000734999000006949990000065499900000614999000005749990000052499900000474999000004149990000035499900000294999000002249990000016499900000084999000000249990010004499900100104999001001749990010023499900100304984001003749490010044494900100514949001005949490010066494900100714949001007649530010080495300100834961001008549620010087496200100874962001008749610010087496200100864963001008649650010086496500100864966001008749680010088496800100894969001009049690010092496900100944967001009749660010100496600101044967001010749670010111495700101154950001011849490010122494900101254949001012952490010131534900101325449001013354490010134544900101345449001013460480010133664300101337144001013371440010132794300101328942001013296380010131993500101309934001012999380010129994900101289949001012799490010126994900101269949001012699490010125994900101259949001012599490010125994900101249949001012299490010120994900101189949001011799490010118994900101209949001012199490010122994900101239949001012399490010123994900101229949001012299490010121994900101219949001012199490010122924900101229249001012203490010122004900101220049001012200490010122004900101220049001012200490010122004900101220049001012200490010122494900101226549001012299490010121994900101219949001012299490010122994900101229949001012299490010122994900101229949001012299490010123994900101239949001012499490010124994900101239949001012399490010122994900101219949001012199490010121994900101229949001012299490010122994900101229949001012299490010122494600101224946001012239460010122004900101220049001012200490010122004900101220049001012200490010122004900101220049001012200490010122254900101224949001012249490010122493800101225812001012258120010122990000101229900001012299000010122991200101219949001012099490010119994900101179949001011699490010114994900101129949001011099490010109994900101099949001011199490010114994900101189949001012099490010120994900101209949001011999490010118624900101174349001011600490010115004900101150049001011600490010116004900101160049001011600490010116004900101160049001011500060010115000600101140006001011449000010114490000101144900001011449000010114490000101144900001011349000010112490000101094900001010649000010103490000100994905001009449430010089494300100844949001007849490010072534900100665649001006158490010057584900100545839001005258320010051583200100515811001005158110010052582100100535848001005358490010053584900100525849001005058490010048604900100446249001004062490010035634900100316241001002762290010024622700100226227001002162290010021623200100216249001002164490010021644900100216749001001969490010017704900100147349011001173490110007754901100047549011000275490100001754901000027549010000375490100003754901000037549010000375580100002757301000017573010000175800110000758001100017580011000275800110003758001100047575011000675750110009756801100127552011001675490110020754901100257549011002975490110034754901100397549011004375490110048754901100517549011005575490110058754201100607531011006175230110062752301100617523011006175230110059752801100577538011005575490110052754901100487549011004475490110040754901100357549011003075490110025754901100217549011001775490110014755601100127568011001175680110010757501100107575011001175720110012757201100147572011001775490110020754901100247549011002875490110033754901100387549011004375490110047754901100527549011005575490110059754901100617549011006375490110064754901100657549011006775490110070754901100717549011007275490110073754901100737549011007370490110072704901100716749011007167490110071534901100714949011007149490110072494901100724949011007249490110072494901100714949011007149490110071494901100714949011007149490110071494901100714949011007149490110071495601100714959011007149640110071496401100714972011007149750110071497701100714978011007149780110071497901100724979011007449790110076497901100794979011008249790110086497901100914979011009649780110101497601101074976011011249760110117496201101204958011012349490010126494900101294949001013349490010136494900101394949001014149490010142495800101434958001014449640010145496800101454968001014549660010145496300101454963001014549610010145495700101464954001014749510010148495100101504950001015349490210155494902101584950021016049500210162495002101634950021016449500210165494902101654949021016549490210165494902101654949021016549490210165494902101654949021016549490010165494400101654937001016549310010165493100101654925001016549000010165490000101644900001016449000010163490000101614900001015949000010156490000101514900001014749000010141490100101354915001012849490010121494900101134949001010549490010098494900100924949001008749490010084494900100814942001007949420010077494000100774940001007649400010076514000100765340001007753400010077543900100775439001007755320110077553101100765536011007555360110074553601100725549011006955490110067554901100635549011005955490110055554901100515549011004755490110043554901100405549011003854550110037555801100365461011003755650110038546801100395468011004054660110041546201100435462011004554590110047535201100505449011005354490110057544901100615449011006554490110069544901100735449011007654490110079544901100815449011008254490110082544901100815448011008054480110079544401100785444011007754440110076544501100755446011007554490110074544901100745449011007354490110073544901100725749011007258490110071584901100715849011007058490110070584901100705849011006958490110069584901100695849011006958490110070584901100705849011007058490110070584901100705849011007058490110071584901100715849011007158490110071584901100715849011007158490110071584901100715849011007158490110071564901100714949011007249490110072494801100724935011007249320110072493001100724927011007249270110072492701100714921011007149210110071492001100704920011006849250110067492901100664931011006449320110062493201100594934011005649340110053493401100484934011004449340110040493401100354934011003149340110027493401100244934011002149340110018493401100154934011001349340110011493501100104937011000849390110007493901100054940011000449420110003494201100014946010000149490000002494900000044949000000649490000008494900000094949000001049490000010494910000104944100001049431000010494310000104943100001049431000010414910000101849100001000491000010004910000100049100001000491000010004910000100049100001100491000011004910000110061100001200601000012005610000120056100001200531000012005310000120054100001200541000012005510000130056100001300581000013006410000130080100001300801000013009710000130096100001300891000013007710000130077100001200621000011004910000090049100000700491000004004910100000049101000400491010008004910100100049101001300491010015004910100179949101001899491010018994910100189949101001799491010016994910100159949101001399491010011994910100109949101000999491010008994910100078649101000686491010005494910100044949101000349490010002494900100014949001000149490010000494900100004960000000149700000002498000000024992000000249990000001499900000014999000000149990000001499900100014999001000349990010005499900100084999001001249990010017499900100224999001002749990010033499900100394999001004649990010054499900100624999001007049990010078499900100874999001009649990010105499900101144999001012249490010131494900101404949001014855490010156634900101626349001016779490010171944900101749949001017699510010177995100101789951001017799500010177994900101779949001017799490010177994900101769949001017699490010176994900101769949001017699490010176994900101759949001017599490010175994900101759949001017687490010177494900101791849001018000490010180004900101800049001018000490010180004900101800049001018100490010181034900101814949001018149490010181494900101814949001018149490010182";
//The save to read back during the Autonomous Period

string saveWingActivated = ""; //Variables for reading the save
string intakeActivated = "";
string combinedString;

//////////////////////////////////////// CORRECTION SYSTEM VARIABLES //////////////////////////////////////////////

int face; //Which way the robot is facing

double r; //Power for the right side of the chassis
double l; //Power for the left side of the chassis

template <typename T>

//A convenient function for converting numbers into strings(text)
std::string ToString(T val)
{
  std::stringstream stream;
  stream << val;
  return stream.str();
}

competition Competition;

//Calibrate the inertial, and make the program wait so it can finish
void CalibrateInertial()
{
  Inertial1.calibrate();
  while (Inertial1.isCalibrating()) {
      wait(800, msec);
  }
  wait(800, msec);
  Controller1.rumble("."); //Vibrate the controller once it's done
}

//Function for showing motor temperatures on the brain for ensuring motors don't die
void MotorTemp(vex::motor m, string name){
  if(m.temperature(percent) == 100){
    combinedString = name + " DEAD: " + ToString(m.temperature(celsius));
  }  
  if(m.temperature(percent) >= 90){
    combinedString = name + " OVERHEATED: 12.5% Power: " + ToString(m.temperature(celsius));
  }
  else if(m.temperature(percent) >= 80){
    combinedString = name + " Overheated: 25% Power: " + ToString(m.temperature(celsius));
  }
  else if(m.temperature(percent) >= 70){
    combinedString = name + "Hot: 50% Power: " + ToString(m.temperature(celsius));
  }
  else{
    combinedString = name + " OK: " + ToString(m.temperature(celsius));
  }
  Brain.Screen.print(combinedString.c_str());
  Brain.Screen.newLine();
}

//Call MotorTemp for all relavent motors
void MonitorTemp(){
  while(1){
    Brain.Screen.setCursor(1, 1);
    MotorTemp(FrontLeft, "Chassis"); //The 6 motors on the chassis have the same temp anyways, so just check one
    MotorTemp(Catapult, "Catapult");
    MotorTemp(BackRight, "Intake");
    Brain.Screen.print(num);
    num++;
    wait(1000, msec);
  }
}

//Function to control the chassis as one, instead of having to spin all the motors manually all the time
void chassis(int left, int right){
  FrontLeft.spin(vex::forward, left, percent);
  FrontRight.spin(vex::forward, right, percent);
  MiddleLeft.spin(vex::forward, left, percent);
  MiddleRight.spin(vex::forward, right, percent);
  BackLeft.spin(vex::forward, left, percent);
  BackRight.spin(vex::forward, right, percent);
}

//Have all the chassis motors brake
void halt(){
  FrontLeft.stop(brake);
  FrontRight.stop(brake);
  MiddleLeft.stop(brake);
  MiddleRight.stop(brake);
  BackLeft.stop(brake);
  BackRight.stop(brake);
}

//Controls the catapult seperately from the rest of the chassis so it has more freedom
int catafire(){
  while(true){
    if(Controller1.ButtonX.pressing() || Controller1.ButtonA.pressing()) //Two controlling buttons for redundancy
    {
      Catapult.spin(vex::forward, 12, volt);
    }
    else if(Controller1.ButtonB.pressing()) //Reverse button to get it unjammed
    {
      Catapult.spin(vex::reverse, 50, percent);
    }
    else{
      Catapult.stop(hold);
    }
    vex::task::sleep(50);
  }
  return 0;
}

//Corrects the orientation of the robot when off course
void correct_orientation(int sign, string correction, double rr, double ll){
  cout << "actual: " << Inertial1.rotation(degrees) << endl; //Print the rotation the robot thinks it is (for debugging)
  int c = atoi(correction.c_str());
  if(sign == 0){
    c = c * -1;
  }
  cout << c << endl; //Prints the rotation the robot wants to go to (for debugging)

  //If the robot is off by a certain amount, add speed to the side that's lagging behind and reduce speed of the other side until it catches up
  if(Inertial1.rotation(degrees) < c - 5){ //The -5 avoids triggering the correction system if the error is too minor or is just an inaccuracy
    while(Inertial1.rotation(degrees) < c - 1){ //The -1 avoids overshooting by cutting it off when it gets "close enough"
      cout << "correcting1" << endl;
      cout << "actual: " << Inertial1.rotation(degrees) << endl;
      cout << c << endl;
      chassis(rr + 15, ll - 15);
      wait(20, msec);
    }
  }
  //same thing but for the other side
  else if(Inertial1.rotation(degrees) > c + 5){
    while(Inertial1.rotation(degrees) > c + 1){
      cout << "correcting2" << endl;
      cout << "actual: " << Inertial1.rotation(degrees) << endl;
      cout << c << endl;
      chassis(rr + 15, ll - 15);
      wait(20, msec);
    }
  }
}

//Runs as soon as possible
void pre_auton(void) {
  vexcodeInit();
  CalibrateInertial(); //Calibrate the Inertial Sensor
  MonitorTemp(); //Keep checking the motor temps
}


void autonomous(void) {
  while (1) {
    //Read the save, section by section
    if(save.length() != 0){
      //Spin chassis
      go = (save[0] - 48) * 10 + save[1] - 48;
      rotate = (save[2] - 48) * 10 + save[3] - 48;
      saveWingActivated = save[4];
      intakeActivated = save[5];
      if(go != 49 || rotate != 49){
        //If the robot is not rotating, do not rotate (49 is the "middle" value, but it's still off by 0.5 so the robot will slowly turn otherwise)
        if(rotate == 49){
          chassis(go * 2 - 99, go * 2 - 99);
          r = go * 2 - 99; //storing these speed values for later
          l = go * 2 - 99;
        }
        //If the robot is not going forward, spin slower so it's easier to control
        else if(go == 49){
          chassis((rotate * 2 - 99) / 1.5, -(rotate * 2 - 99) / 1.5);
          r = (rotate * 2 - 99) / 1.5;
          l = -(rotate * 2 - 99) / 1.5;
        }
        //Otherwise, just drive normally
        else{
          chassis((go * 2 - 99) + (rotate * 2 - 99), ((go * 2 - 99)) - (rotate * 2 - 99));
          r = (go * 2 - 99) + (rotate * 2 - 99);
          l = (go * 2 - 99) - (rotate * 2 - 99);
        }
      }
      else{
        halt();
      }
      if(saveWingActivated == "1"){ //Open or close the wings
        Flap1.set(true);
      }
      else{
        Flap1.set(false);
      }
      if(intakeActivated == "2"){ //Turn on or turn off the intake
        Intake.spin(vex::forward, 100, percent);
      }
      else if(intakeActivated == "1"){
        Intake.spin(vex::forward, -100, percent);
      }
      else{
        Intake.stop(hold);
      }
      if(save[6] == '0'){ //Run the heading correction check, which will spin the chassis to get back on course if necessary
        correct_orientation(0, save.substr(7, 4), r, l);
      }
      else if(save[6] == '1'){
        correct_orientation(1, save.substr(7, 4), r, l);
      }
      //Delete already read parts of save file
      for (int i = 0; i < 11; i++) {
        save.erase(save.begin());
      }
    }
    else{
      halt();
      break;
    }
    wait(20, msec);
  }

}

void usercontrol(void) {
  std::cout << "START" << "\n";
  vex::task catapult = task(catafire); //Run the catapult control script
  while (1) {  
    //Get inputs from the controller
    go = Controller1.Axis3.position(percent);
    rotate = Controller1.Axis1.position(percent);
    //Modify inputs for easier recording (get rid of negative signs and triple digits so that -100 to 100 is now 0 to 99)
    go = (int)(go + 99) / 2;
    rotate = (int)(rotate + 99) / 2;
    if(go < 10){ //Add a leading zero if the value is single-digit
      newSave = newSave + "0";
      newSave = newSave + ToString(go);
    }
    else{
      newSave = newSave + ToString(go);
    }
    if(rotate < 10){
      newSave = newSave + "0";
      newSave = newSave + ToString(rotate);
    }
    else{
      newSave = newSave + ToString(rotate);
    } 
    if(Controller1.ButtonUp.pressing()){ //For slower, more precise control
      chassis(20, 20);
    }
    else{
      //Spin the chassis
      if(go != 49 || rotate != 49){
        //If the robot is not rotating, do not drift rotation
        if(rotate == 49){
          chassis(go * 2 - 99, go * 2 - 99);
        }
        //If the robot is not going forward, spin slower
        else if(go == 49){
          chassis((rotate * 2 - 99) / 1.5, -(rotate * 2 - 99) / 1.5);
        }
        //Otherwise, just drive
        else{
          chassis(((go * 2 - 99)) + (rotate * 2 - 99), ((go * 2 - 99)) - (rotate * 2 - 99));
        }
      }
      else{
        halt();
      }
    }
    if(Controller1.ButtonR2.pressing())
    {
      if(alreadyPressed == false) //Check if the R2 Button is being held versus pressed for the first time. Avoids rapid re-toggling of the wings
      {
        alreadyPressed = true;
        if(wingActivated == true){ //If the wings are on, turn them off. If they are off, turn them on
          wingActivated = false;
          newSave = newSave + "0";
          Flap1.set(false);
        }
        else{
          wingActivated = true;
          newSave = newSave + "1";
          Flap1.set(true);
        }
      }
      else{
        if(wingActivated == true){
          newSave = newSave + "1";
        }
        else{
          newSave = newSave + "0";
        }
      }
    }
    else{
      alreadyPressed = false;
      if(wingActivated == true){
        newSave = newSave + "1";
      }
      else{
        newSave = newSave + "0";
      }
    }
    if(Controller1.ButtonR1.pressing()) //Spins the intake
    {
      Intake.spin(vex::forward, 100, percent);
      newSave = newSave + "2";
    }
    else if(Controller1.ButtonL1.pressing())
    {
      Intake.spin(vex::reverse, 100, percent);
      newSave = newSave + "1";
    }
    else
    {
      Intake.stop(hold);
      newSave = newSave + "0";
    }

    face = round(Inertial1.rotation(degrees)); //Get the rotation of the robot
    if(face >= 0){ //Stores if the rotation is negative or positive
      newSave = newSave + "1";
    }
    else{
      newSave = newSave + "0";
    }
    if(face < 10 && face > -10){ //Add leading zeros for consistent save sizes
      newSave = newSave + "000" + ToString(abs(face));
    }
    else if(face < 100 && face > -100){
      newSave = newSave + "00" + ToString(abs(face));
    }
    else if(face < 1000 && face > -1000){
      newSave = newSave + "0" + ToString(abs(face));
    }
    else{
      newSave = newSave + ToString(abs(face));
    }
    if(newSave.length() >= 660){ //Print out the save file once it reaches a certain size
      std::cout << newSave << "\n";
      newSave = "";
    }
    wait(20, msec);
  }
}

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

























































































































































































// this comment is on line 420 :)