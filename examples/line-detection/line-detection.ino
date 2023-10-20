/*
 Creative Robotix: line detection 

 This example uses Codees 5 line sensors to detect the presence of a
 black line drawn against a while background.  Ideally the black line should be
 about 15mm wide, or roughly the half the distance between two sesnors.  Codee
 uses the sensors calculate a weighted sum average biased by the weight of the 
 middle sensor (see calculation below).  This returns a single value, where 
 a value of 0 means Codee is centred over the line, a negative none zero value
 means Codee is to the left of the line (and should steer right) and a positive
 none zero value means Codee is to the right of the line (and should steer left). A
 return of 5 indicates that that all sensors of on the (black) line, while a return 
 value of of 6 indicate that all sensor are off the line.

 linePosition = (SUM(all sensors positions on line) / number of sensors on line) - middle sensor position

 Created 13 October 2023
 by Simon Egerton

 Creative Science Foundation

 https://creative-science.org/

 https://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

 // set up a new robot instance called codee
CreativeRobotix codee;

void setup() {
	// initilaise codee 
	codee.begin();

	// initialise serial 
	Serial.begin(57600);
}

void loop() {
	uint8_t linePosition;

	// update codees behaviours, arms, head, sound, display
	codee.update();

	// readLine and updated class vairable linePosition
	codee.readLine();

	// print line position to serial
	Serial.println("Line Position = " + (String)codee.linePosition);

	// claculate the decimal value for display
	linePosition = abs(codee.linePosition) * 10;

	// diplay line position 
	codee.displayDigits(linePosition);

	// add decimal point
	codee.displayPixel(3, 1, true);

	// display the negative sign
	if (codee.linePosition < 0) {
		codee.displayPixel(7, 0, true);
		codee.displayPixel(6, 0, true);
	}
	
	delay(500);
}
