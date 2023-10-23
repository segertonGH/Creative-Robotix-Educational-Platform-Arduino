/*
 Creative Robotix: bluetooth configure

 This example demonstrates how to set up Codees bluetooth. The configure function
 will set Codees bluetooth module name (myRobotname) and pin (myRobotPin) and set 
 the baud rate to 57600.   given the name myRobotname and a pin myRobotPin, the baud 
 rate is set to 57600.  The BT_Enable and BT_Configure jumpers need to be set and
 the USB cable disconnected.  Codee should be powered from batteries.

 Created 18 October 2023
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

	// configure bluetooth module
	codee.btConfigure(MY_ROBOT_NAME, MY_ROBOT_PIN);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
