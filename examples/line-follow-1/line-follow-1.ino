/*
 Creative Robotix: line following 

 This example demostrates a basic line following algrothim, based on a 
 Braitenberg statemachine.  This example assumes a black line on white background. 
 Ideally the line should be about 20mm wide, or roughly double the distance 
 between two sensors.  Codee uses the readline() function to update the lineState
 class variable.  lineState is an integer value between 0 and 10 with the following
 meaning when 5 line sensors are installed.

 0 Codee the the left, left, left, left of line
 1 Codee the the left, left, left of line
 2 Codee the the left, left of line
 3 Codee the the left of line
 4 Codee on line centre
 5 Codee the the right of line
 6 Codee the the right, right of line
 7 Codee the the right, right, right of line
 8 Codee the the right, right, right, right of line
 9 All sensors are not reflecting i.e. all sensors on the line
 10 All sensors are reflecting, i.e. all sensor off the line, on reflective area   
 
 lineSate can be used to index an array of wheel speeds, which allows
 the implementation of a range of line following behaviours and
 the posability of using machine learning / reinforcement learning to enable
 Codee to learn how to optimally follow a line.
 
 In this example the state array has been filled with a simple set of values.
 You may need to tweak them to suit your Codee.
 
 Created 18 October 2023
 by Simon Egerton

 Creative Science Foundation

 https://creative-science.org/

 https://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

// state array maps to -> [LLLL, LLL, LL, L, CENTRE, R, RR, RRR, RRRR, ALL ON, ALL OFF]
// line following states
int8_t lf_state_leftw[] = {	 9,	9,	9,	9,	9,	0,	0,	0,	0,	0,	0 };
int8_t lf_state_rightw[] = { 0,	0,	0,	0,	6,	6,	6,	6,	6,	0,	0 };

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
	line_follow_braitenberg();
}

void line_follow_braitenberg(void) {
	// read line and update line class variables 
	codee.readLine();
	// update Codees velocity state
	codee.wheelLeft(lf_state_leftw[codee.lineState]);
	codee.wheelRight(lf_state_rightw[codee.lineState]);
}