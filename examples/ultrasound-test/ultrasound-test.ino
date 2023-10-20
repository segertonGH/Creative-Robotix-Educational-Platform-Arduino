/*
 Creative Robotix: ultrasound 

 This example uses Codees display to reort the ultrasound sensor range reading and
 play a tone proportional to the range, higher tone = nearer, lower tone = further 

 Created 13 October 2023
 by Simon Egerton

 Creative Science Foundation

 https://creative-science.org/

 https://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

 // set up a new robot instance called codee
CreativeRobotix codee;

// the setup function runs once when you press reset or power the board
void setup() {
	// initilaise codee 
	codee.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	uint8_t range;

	// update codees behaviours, arms, head, sound, display
	codee.update();

	// read ultrasound sensor in cm
	range = codee.readUltrasound();

	// display range or smiley face
	if (!range) {
		codee.displayImage(DISPLAY_SMILE);
	}
	else {
		codee.displayDigits(range);

		// say the range 
		codee.playTone((HCSR04_MAX_DISTANCE * 35) - (range * 34), 50);
	}
}