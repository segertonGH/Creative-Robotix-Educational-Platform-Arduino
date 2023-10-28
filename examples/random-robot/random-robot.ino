/*
 Creative Robotix: random robot

 This example demostrates how to generate psuedo random numbers which vary each
 cycle.  The random numbers are used to set Codees screen display.  Codees screen is 64 bits 
 wide (i.e. 8 pixels by 8 pixels).  Two random numbers are generated for the high (top 32 bits) & 
 low (bottom 32 bits) of the screen then sent to display.  This example genertes random numbers 
 based on the idea from Michael James @ https://www.programmingelectronics.com/using-random-numbers-with-arduino/.
 This technique uses a floating analoge pin to seed the random number generator.  Generating random 
 number is useful to navigation, games, and is demostrated further by some of the other library 
 examples.

 This example uses the A7 analoge pin reserved for Codees Bluetooth config to seed the random 
 number generator.

 Created 14 October 2023
 by Simon Egerton

 Creative Robotix

 http://creativerobotix.com.au

 Creative Science Foundation

 http://creative-science.org/

 http://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

#define INTERVAL	25

 // set up a new robot instance called codee
CreativeRobotix codee;

uint32_t randomDisplayHigh, randomDisplayLow;

static unsigned long l_currentMillis = 0;
static unsigned long l_previousMillis = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	// initilaise codee
	codee.begin();

	// seed random generator with analog reading from A7
	randomSeed(analogRead(A7));

	// animate codee
	codee.swingArms(3, true);
	codee.lookAround(1, true);
}

// the loop function runs over and over again until power down or reset
void loop() {
	uint64_t screen;

	// update codees behaviours, arms, head, sound, display
	codee.update();

	l_currentMillis = millis();

	if ((l_currentMillis - l_previousMillis) > INTERVAL) {
		// generate random display data.  RANDOM_MAX is half the required 
		// random value i.e. 31 bits, so let's multiply the value by another 
		// random number to ensure at least 32 bits are generated 
		randomDisplayHigh = random(0, RANDOM_MAX) * random(2, 10);
		randomDisplayLow = random(0, RANDOM_MAX) * random(2, 10);

		// assembly the screen data, starting with loading the top half of the data to display
		screen = randomDisplayHigh; 
		// shift the screen data right 32 bits, and load in the bottom half of the data to display
		screen = (screen << 32) | randomDisplayLow;
		
		// display results on Codee
		codee.displayCustom(screen);

		// play tone
		codee.playTone(random(NOTE_B0, NOTE_DS8), 50);

		// update current millis
		l_previousMillis = millis();
	}
}
