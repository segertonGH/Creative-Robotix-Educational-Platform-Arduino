/*
 Creative Robotix: line detection 

 This example uses Codees 5 line sensors to detect the presence of a
 none reflective line drawn against a reflective background (e.g. a black line on a 
 white sheet of paper).  Ideally the line should be about 15mm wide, or roughly the half 
 the distance between two sensors.  Codee uses the sensors binary readings, on-line, off-line, 
 to calculate a weighted sum average biased by the weight of the middle sensor (see calculation 
 below).  This returns a single value, where a value of 0 means Codee is centred over the line, 
 a negative none zero value means Codee is to the left of the line (and should steer right) and 
 a positive none zero value means Codee is to the right of the line (and should steer left). A
 return of 5 indicates that that all sensors are on the line, while a return value of 6 indicates 
 that all sensor are off the line.

 linePosition = (SUM(all sensors positions on line) / number of sensors on line) - middle sensor position

 The line position is also used to calculate a state value which can be used to index an array of
 wheel velocities, which can be used to implement a Braitenburge style line follower.  Line states
 are held in the calss variable linestate and takes on the following values, 

 0 Codee the the very, very, very, left of line
 1 Codee the the very, very, left of line
 2 Codee the the very, left of line
 3 Codee the the left of line
 4 Codee on line centre
 5 Codee the the right of line
 6 Codee the the very, right of line
 7 Codee the the very, very, right of line
 8 Codee the the very, very, very, right of line
 9 All sensors are not reflecting i.e. all sensors on the line
 10 All sensors are reflecting, i.e. all sensor off the line, on reflective area

 With the example below set LINEREPORT to LINEPOSITION to report the lineposition and LINEREPORT 
 to LINESTATE to report linestate.

 Created 13 October 2023
 by Simon Egerton

 Creative Robotix

 http://creativerobotix.com.au

 Creative Science Foundation

 http://creative-science.org/

 http://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

#define LINEPOSITION	0
#define LINESTATE		1

//  set LINEREPORT to either LINEPOSITION or LINESTATE 
#define LINEREPORT LINEPOSITION

 // set up a new robot instance called codee
CreativeRobotix codee;

void setup() {
	// initilaise codee 
	codee.begin();

	// initialise serial 
	Serial.begin(57600);
}

void loop() {
	// update codees behaviours, arms, head, sound, display
	codee.update();

	// readLine and updated class vairable linePosition and lineState
	codee.readLine();

	if (LINEREPORT == LINEPOSITION) {
		reportLinePosition();
	}
	else
	{
		reportLineState();
	}

	// add a 0.5s delay to the loop
	delay(500);
}

void reportLinePosition(void){
	uint8_t linePosition;

	// print line position to serial
	Serial.println("Line Position = " + (String)codee.linePosition);

	// claculate the decimal value for display
	linePosition = abs(codee.linePosition) * 10;

	// diplay line position 
	codee.displayDigits(linePosition);

	// add decimal point
	codee.displayPixel(1, 3, true);

	// display the negative sign
	if (codee.linePosition < 0) {
		codee.displayPixel(0, 7, true);
		codee.displayPixel(0, 6, true);
	}
}

void reportLineState(void) {
	// print line state to serial
	Serial.println("Line State = " + (String)codee.lineState);

	// diplay line state 
	codee.displayDigits(codee.lineState);
}
