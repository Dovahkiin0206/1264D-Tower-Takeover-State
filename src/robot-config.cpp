#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor L1 = motor(PORT1, ratio18_1, false);
motor L2 = motor(PORT11, ratio18_1, false);
motor R1 = motor(PORT10, ratio18_1, true);
motor R2 = motor(PORT19, ratio18_1, true);
motor Lift1 = motor(PORT3, ratio18_1, true);
motor Lift2 = motor(PORT12, ratio18_1, false);
motor Intake1 = motor(PORT4, ratio18_1, true);
motor Intake2 = motor(PORT7, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
