using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FrontLeft;
extern motor FrontRight;
extern motor BackLeft;
extern motor BackRight;
extern controller Controller1;
extern digital_out Flap1;
extern digital_out Flap2;
extern motor Intake;
extern motor Catapult;
extern rotation Rotation;
extern motor MiddleLeft;
extern motor MiddleRight;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );