/*
 Name:		CRFirmata.ino
 Created:	29/18/2023 12:40:00 PM
 Author:	Simon Egerton
 Firmata is a generic protocol for communicating with microcontrollers
 from software on a host computer. It is intended to work with
 any host computer software package.
 
 To download a host software package, please click on the following link
 to open the list of Firmata client libraries in your default browser.
 
 https://github.com/firmata/arduino#firmata-client-libraries

 This is a Firmata Server for the Creative Robotix Platform

 Creative Robotix

 http://creativerobotix.com.au

 Creative Science Foundation

 http://creative-science.org/

 http://creative-science.org/partnerships/creative-robotix/

*/

#include "src\CRFirmata.h"
#include <Firmata.h>
#include <CreativeRobotix.h>

// ----------------------------------------------------------------------------
// NOTE: bluetooth is configured when both the bluetooth config pin and 
// the bluetooth receive pin are jumped on the Creative Robotix board

// edit this to rename your robots bluetooth connection, you may also rename 
// your robot via Snap4Arduino
#define MY_ROBOTS_NAME		"Codee"

// edit this to give your robot a new bluetooth pin number
#define MY_ROBOTS_PIN		1234
// ----------------------------------------------------------------------------

// external reference to codee declaration in CRFirmata.h
extern CreativeRobotix codee;

// forward declaration for compiler
void demo(void);

// the setup function runs once when you press reset or power the board
void setup() {
	// initilaise Creative Robotix firmata
	CRFirmataInit(MY_ROBOTS_NAME, MY_ROBOTS_PIN, demo);
}

// the loop function runs over and over again until power down or reset
void loop() {
	// run firmata updates
	CRFirmataUpdate();
}

// the demo fuction provides a built in demo when useing the firmata firmware
// this can be useful with groups using firmata to test most of the robots
// functions after a build.

void demo(void) {
	uint8_t counter = 0;
	uint8_t melody = MELODY_CHARIOTS;

	// swing arms and head
	codee.swingArms(2, true);
	codee.lookAround(2, true);

	// move forwards
	codee.wheelLeft(7);
	codee.wheelRight(7);

	delay(2000);

	// stop
	codee.wheelLeft(0);
	codee.wheelRight(0);

	delay(250);

	// move backwards
	codee.wheelLeft(-7);
	codee.wheelRight(-7);

	delay(2000);

	// stop
	codee.wheelLeft(0);
	codee.wheelRight(0);

	// play melody
	codee.playMelody(melody);

	// event loop 
	while (true) {
		codee.update();
		if (!codee.hasMelodytoPlay()) {
			// stop arms and head
			codee.swingArms(2, false);
			codee.lookAround(2, false);

			// lead ultrasound
			uint8_t range = codee.readUltrasound(); // Take reading in cm

			// say and display the range
			if (range) {
				codee.displayDigits(range);

				// easter egg if a range of 10 is held for a few itterations
				if (range == 10) {
					counter++;

					if (counter == 128) {
						counter = 0;

						// play next built in melody and swing arms and head
						codee.playMelody(++melody);
						codee.swingArms(2, true);
						codee.lookAround(2, true);
						codee.displayImage(DISPLAY_SMILE);
					}
				}
				else {
					// reset counter
					counter = 0;
					// convert range into character
					char say = (126 - HCSR04_MAX_DISTANCE) + range; 
					codee.sayDirect((String)say);
				}
			}
			else {
				// revert display back to smile if there's no untrasound input
				codee.displayImage(DISPLAY_SMILE);
			}
		}
	}
}

