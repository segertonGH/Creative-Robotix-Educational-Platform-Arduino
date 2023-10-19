/*
 Creative Robotix: randoms

 This example demostrates how to generate psuedo random numbers which vary each
 cycle.  Two random numbers are generates for the high & low protions of the
 display then displayed to screen.  Thi sexample is based on the idea from Michael
 James @ https://www.programmingelectronics.com/using-random-numbers-with-arduino/.
 This technique is useful for navigation and games, and is demostrated further by
 some of the other library examples.

 This example uses the A7 analoge pin reserved for Codees Bluetooth config.

 Created 14 October 2023
 by Simon Egerton

 Creative Science Foundation

 https://creative-science.org/

 https://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

#define INTERVAL	25

CreativeRobotix codee = CreativeRobotix();

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
		// random value, so let's multiply the value by another random number 
		randomDisplayHigh = random(0, RANDOM_MAX) * random(2, 10);
		randomDisplayLow = random(0, RANDOM_MAX) * random(2, 10);

		// display results on Codee
		screen = randomDisplayHigh;
		screen = (screen << 32) | randomDisplayLow;
		codee.displayCustom(screen);

		// play tone
		codee.playTone(random(NOTE_B0, NOTE_DS8), 50);

		// update current millis
		l_previousMillis = millis();
	}
}
