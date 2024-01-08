#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontLeft = motor(PORT18, ratio18_1, true);
motor FrontRight = motor(PORT8, ratio18_1, false);
motor BackLeft = motor(PORT20, ratio18_1, true);
motor BackRight = motor(PORT10, ratio18_1, false);
controller Controller1 = controller(primary);
digital_out Flap1 = digital_out(Brain.ThreeWirePort.A);
motor Catapult = motor(PORT5, ratio36_1, false);
motor Intake = motor(PORT17, ratio6_1, true);
rotation Rotation = rotation(PORT4, false);
motor MiddleLeft = motor(PORT19, ratio18_1, true);
motor MiddleRight = motor(PORT9, ratio18_1, false);
inertial Inertial1 = inertial(PORT1);

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