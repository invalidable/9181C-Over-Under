#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontLeft = motor(PORT11, ratio18_1, true);
motor FrontRight = motor(PORT20, ratio18_1, false);
motor BackLeft = motor(PORT19, ratio18_1, true);
motor BackRight = motor(PORT12, ratio18_1, false);
controller Controller1 = controller(primary);
digital_out Flap1 = digital_out(Brain.ThreeWirePort.A);
digital_out Flap2 = digital_out(Brain.ThreeWirePort.B);
motor Catapult = motor(PORT2, ratio36_1, true);
motor Intake = motor(PORT18, ratio6_1, false);
rotation Rotation = rotation(PORT1, false);

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