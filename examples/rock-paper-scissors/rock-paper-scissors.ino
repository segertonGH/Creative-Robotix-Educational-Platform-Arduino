/*
 Creative Robotix: rock paper scissor game 

 This example plays the game of rock, paper, scissors.  Codee will challenge you
 to play the best of three, playing a victory tune for a win, along with
 some scoll text.  The player chooses betwen, Rock, Paper, Sissors by holding a hand
 steady in front of Codee with a defined window.  This example contains a game may
 that can be printed on A3 paper to help enhance the expereince.
 
 Created 19 October 2023
 by Simon Egerton

 Creative Science Foundation

 https://creative-science.org/

 https://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

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
}
