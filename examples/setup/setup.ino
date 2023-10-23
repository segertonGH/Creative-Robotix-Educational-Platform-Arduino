/*
 Creative Robotix: setup

 This example centres Codees head, arms, and programes Codees bluetooth module.
 The bluetooth module is given the name myRobotname and a pin myRobotPin, the baud 
 rate is set to 57600.  The BT_Enable and BT_Configure jumpers need to be set and
 the USB cable disconnected.  Codee should be powered from batteries.

 If Codees head and arms are not centred, then remove the servo screw holding 
 them in place and reposition while the servos are activted to their center spots.

 NOTE: Codees forearm should be horizontal, parallel to the desktop, in the centre
 position.

 Created 23 October 2023
 by Simon Egerton

 Creative Science Foundation

 https://creative-science.org/

 https://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

#define MY_ROBOT_NAME "Codee"
#define MY_ROBOT_PIN 1234

 // set up a new robot instance called codee
CreativeRobotix codee;

// the setup function runs once when you press reset or power the board
void setup() {

	// initilaise codee
	codee.begin();

	// move head to centre
	codee.headAngle(0, true);

	// move arms to centre
	codee.armLeft(0, true);
	codee.armRight(0, true);

	// configure bluetooth module
	codee.btConfigure(MY_ROBOT_NAME, MY_ROBOT_PIN);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
