/*
 Creative Robotix: Codee the robot melody demo

 This example uses Codees ultrasound sensor to select from the list of 
 built in melodies.  Melodies are selected by holding an object in front
 of codee at the trigger distance for a period of at least 5 seconds.  Codee
 will then play the melody.  Wait for codee to stop playing before selecting
 the next melody.  Codees display a message for user input and is used to 
 indicate the melody being slected.

Distance bands for tune selection:

GREENSLEEVES		5cm - 10cm
LITTLELAMB			15cm - 20cm
HAPPYBIRTHDAY		25cm - 30cm
STARWARS			35cm - 40cm
MELODY_CHARIOTS		45cm - 50cm
 
 Created 12 October 2023
 by Simon Egerton
 
 Creative Science Foundation

 https://creative-science.org/

 https://creative-science.org/partnerships/creative-robotix/
 
 */

#include "CreativeRobotix.h"

#define GREENSLEEVES	10
#define LITTLELAMB		20
#define HAPPYBIRTHDAY	30
#define STARWARS		40
#define CHARIOTS		50

#define TRIGGER_WINDOW	5

uint16_t interval = 0;
uint8_t userInput = 0, userSelection = 0;

// set up a new robot instance called codee
CreativeRobotix codee;

void setup() {
	// initilaise codee 
	codee.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	// update codees behaviours, arms, head, sound, display
	codee.update();

	// if codeee is currently not playing a melody, check which melody to play next
	if (!codee.hasMelodytoPlay()) {
		userInput = codee.readUltrasound(); // get user input from ultrasound sensor
		if (userInput == 0) { // If no reading, then display help
			codee.displayScrollText("CHOOSE A SONG TO PLAY");
		}
		else { // check user selection, function makes use of globals 
			checkUserSelection(GREENSLEEVES, 'G');
			checkUserSelection(LITTLELAMB, 'L');
			checkUserSelection(HAPPYBIRTHDAY, 'H');
			checkUserSelection(STARWARS, 'S');
			checkUserSelection(CHARIOTS, 'C');
		}

		// if a selection has a continious count of > 500 play that tune
		if (interval > 500) {
			switch (userSelection) {
			case GREENSLEEVES:
				codee.playMelody(MELODY_GREENSLEEVES);
				break;
			case LITTLELAMB:
				codee.playMelody(MELODY_LITTLELAMB);
				break;
			case HAPPYBIRTHDAY:
				codee.playMelody(MELODY_HAPPYBIRTHDAY);
				break;
			case STARWARS:
				codee.playMelody(MELODY_STARWARS);
				break;
			case CHARIOTS:
				codee.playMelody(MELODY_CHARIOTS);
				break;
			}

			interval = 0;
		}
	}  
}

void checkUserSelection(uint8_t melody, uint8_t songID) {
	// check userInput (ultrasound range) within tune window
	if (userInput >= (melody - TRIGGER_WINDOW) && userInput <= melody) {
		// display songID
		codee.displayASCII(songID);
		// is the user selection the same as the previous time? Yes, then increment the interval
		if (userSelection == melody) {
			interval++;
		}
		else
		{
			// no, selection has changed, reset interval
			userSelection = melody;
			interval = 0;
		}
	}
}
