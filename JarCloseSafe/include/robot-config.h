using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FrontLeft;
extern motor MiddleLeft;
extern motor BackLeft;
extern motor FrontRight;
extern motor MiddleRight;
extern motor BackRight;
extern motor Puncher;
extern motor Intake;
extern inertial Inertial;
extern controller Controller1;
extern digital_out Wings;
extern digital_out Balance;
extern motor PuncherB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );