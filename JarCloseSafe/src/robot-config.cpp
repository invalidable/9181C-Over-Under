#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontLeft = motor(PORT1, ratio18_1, true);
motor MiddleLeft = motor(PORT2, ratio18_1, true);
motor BackLeft = motor(PORT3, ratio18_1, true);
motor FrontRight = motor(PORT8, ratio18_1, false);
motor MiddleRight = motor(PORT9, ratio18_1, false);
motor BackRight = motor(PORT10, ratio18_1, false);
motor Puncher = motor(PORT20, ratio18_1, false);
motor Intake = motor(PORT11, ratio18_1, false);
inertial Inertial = inertial(PORT16);
controller Controller1 = controller(primary);
digital_out Wings = digital_out(Brain.ThreeWirePort.G);
digital_out Balance = digital_out(Brain.ThreeWirePort.H);
motor PuncherB = motor(PORT13, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}