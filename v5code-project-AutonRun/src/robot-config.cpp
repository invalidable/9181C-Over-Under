#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontLeft = motor(PORT18, ratio18_1, true);
motor FrontRight = motor(PORT3, ratio18_1, false);
motor BackLeft = motor(PORT20, ratio18_1, true);
motor BackRight = motor(PORT1, ratio18_1, false);
controller Controller1 = controller(primary);
digital_out Flap1 = digital_out(Brain.ThreeWirePort.A);
digital_out Flap2 = digital_out(Brain.ThreeWirePort.B);
motor Catapult = motor(PORT17, ratio36_1, false);
motor Intake = motor(PORT7, ratio6_1, true);
rotation Rotation = rotation(PORT10, false);
motor MiddleLeft = motor(PORT19, ratio18_1, true);
motor MiddleRight = motor(PORT2, ratio18_1, false);
inertial Inertial1 = inertial(PORT16);

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