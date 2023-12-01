/*
 Creative Robotix: bluetooth configure

 This example demonstrates how to set up Codees bluetooth. The configure function
 will set Codees bluetooth module name (myRobotname) and pin (myRobotPin) and configure 
 the baud rate to 57600.  The BT_Recive_Enable and BT_Configure jumpers need to be set and
 the USB cable disconnected.  Upload the firmware via USB, then set the BT jumpers, unplug 
 the USB cable, poweer Codee from batteries.  Codee will emit a series of chirps when 
 powered up.  If the bluetooth configuration update is successful, then Codee will display 
 a smile and say hello.  If the bluetooth configuration upadate hasn't been successful, then 
 a series of 'harsh' continous tones will sound, and Codee's display will remain blank. In 
 this case, check the USB cable has been removed and the BT_Receive_Enable jumper is set.

 Created 18 October 2023
 by Simon Egerton

 Creative Robotix

 http://creativerobotix.com.au

 Creative Science Foundation

 http://creative-science.org/

 http://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

#define MY_ROBOT_NAME "Codee"
#define MY_ROBOT_PIN 1234

 // set up a new robot instance called codee
CreativeRobotix codee;

// the setup function runs once when you press reset or power the board
void setup() {
	// configure bluetooth module
	codee.btConfigure(MY_ROBOT_NAME, MY_ROBOT_PIN);

	// initilaise codee
	codee.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
