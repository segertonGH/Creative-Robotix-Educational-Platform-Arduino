/*
 Creative Robotix: line following

 This example demostrates a basic line following method.  This example assumes a 
 black line on white background. Ideally the line should be about 20mm wide, or 
 roughly double the distance between two sensors.  Codee uses the readline() 
 function to update the class variable linePostion.  This variable decribes the 
 relative position of code on the line.  See the line detection example for an 
 explantion.

 linePosition = 6 when all line sensors are reflecting i.e. off the line, on white reflective area
 linePosition = 5 when all line sensors are not reflecting i.e. on the line, on dark area
 linePosition = 0 whenb Codee is on the line centre (go straight)
 linePosition < 0 when Codee is to the left of the line (turn right)
 linePosition > 0 when Codee is to the right of the line (turn left)

 Created 18 October 2023
 by Simon Egerton

 Creative Science Foundation

 https://creative-science.org/

 https://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

// simple line follower, adjust speeds to suit your Codee
#define lf_left_speed	9
#define lf_right_speed	6

CreativeRobotix codee = CreativeRobotix();

// the setup function runs once when you press reset or power the board
void setup() {
	// initilaise codee
	codee.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	// update codees behaviours, arms, head, sound, display
	codee.update();

	// line follow
	line_follow_simple();
}

void line_follow_simple(void) {
	// read line and update line class variables 
	codee.readLine();

	// stop
	if (codee.linePosition > 2) {
		codee.wheelLeft(0);
		codee.wheelRight(0);
	}

	// straight
	if (codee.linePosition == 0) {
		codee.wheelLeft(lf_left_speed);
		codee.wheelRight(lf_right_speed);
	}

	// turn left
	if (codee.linePosition > 0) {
		codee.wheelLeft(0);
		codee.wheelRight(lf_right_speed);
	}

	// turn right
	if (codee.linePosition < 0) {
		codee.wheelLeft(lf_left_speed);
		codee.wheelRight(0);
	}
}
