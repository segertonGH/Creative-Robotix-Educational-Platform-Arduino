/*
 Creative Robotix: rock paper scissors game 

 This example plays the game of rock, paper, scissors.  Codee will challenge you to play the 
 best of three games, playing a victory tune for a win, along with scoll text.  The player 
 chooses betwen, Rock, Paper, Sissors by holding a hand steady in front of Codee within a 
 defined window.  This example contains a game matt in the examples folder to enhance the 
 playability.  The matt is best printed on A3 paper.
 
 Created 24 October 2023
 by Simon Egerton

 Creative Robotix

 http://creativerobotix.com.au

 Creative Science Foundation

 http://creative-science.org/

 http://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

// game constants
#define GAME_TRIES		3		// best out of 3
#define GAME_TIME		5000	// time in ms for each game 
#define GAME_COUNTDOWN	1000	// should value should divide GAME_TIME exactly 
#define GAME_DELAY		1000	// value of game pauses in ms

#define	START_US		5		// minimum distance to hi-five code to start game 			

#define ROCK_US			8		// distance thresholds in cm for rock, paper, scissors
#define PAPER_US		16
#define SCISSORS_US		25

#define DISPLAY_PLAYER	0x0005f507f5050000 // H = 
#define DISPLAY_CODEE	0x0007f101f1070000 // C =  
#define DISPLAY_SCORE	0x000007f407f10700 // S = 

// game choice array
uint8_t gameChoice[] = {DISPLAY_ROCK, DISPLAY_PAPER, DISPLAY_SCISSORS};

// game variables
uint8_t playerScore = 0, codeeScore = 0;
uint8_t playerChoice, codeeChoice;

// timmers
static unsigned long l_currentMillis = 0;
static unsigned long l_previousMillis = 0;

// set up a new robot instance called codee
CreativeRobotix codee;

// the setup function runs once when you press reset or power the board
void setup() {
	// initilaise codee 
	codee.begin();

	// seed random generator with analog reading from A7
	randomSeed(analogRead(A7));

	// reset positure
	resetPosture();
}

// the loop function runs over and over again until power down or reset
void loop() {
	// update codees behaviours, arms, head, sound, display
	codee.update();

	// display opening text message
	codee.displayScrollText("LETS PLAY A NICE GAME");

	// wait for user to start the game;
	if (startGame()) playGame();
}

boolean startGame(void) {
	uint8_t	 ultrasound = codee.readUltrasoundMedian(3);

	if (ultrasound > 0 && ultrasound <= START_US) {
		return(true);
	}
	return (false);
}

void playGame(void) {
	uint8_t gamesPlayed = 0;

	// reset scores
	playerScore = 0, codeeScore = 0;

	// play
	while (gamesPlayed < GAME_TRIES) {
		playGo();
		gamesPlayed = gamesPlayed + 1;
	}

	// who wins?
	gameOver();
}

void gameOver() {
	if (playerScore > codeeScore) {
		codee.displayScrollText("YOU WIN! ", true);
		codee.swingArms(2, true);
		codee.playMelody(MELODY_STARWARS);
	}
	else if (playerScore < codeeScore) {
		codee.displayScrollText("I WIN! ", true);
		codee.swingArms(2, true);
		codee.playMelody(MELODY_CHARIOTS);
	}
	else {
		codee.displayScrollText("DRAW ", true);
	}

	codee.lookAround(2, true);

	// set the times
	l_currentMillis = millis();
	l_previousMillis = l_currentMillis;

	// while game time hasn't expired, update codees behaviours
	while ((l_currentMillis - l_previousMillis) < GAME_TIME * 3) {
		// update Codee
		codee.update();

		// update time
		l_currentMillis = millis();
	}

	// reset positure
	resetPosture();
}

void resetPosture(void){
	// Reset
	codee.lookAround(2, false);
	codee.swingArms(2, false);
	codee.headAngle(0, true);
	codee.armLeft(-20, true);
	codee.armRight(-20, true);

	// Revert Display
	codee.displayReset();
}

void playGo(void) {
	// display question mark
	codee.displayImage(DISPLAY_QUESTION);

	// delay
	delay(GAME_DELAY);

	// get player input
	playerChoice = getPlayerInput();

	// codee guess
	codeeChoice = random(0, 2);

	// display choices made
	displayChoices();

	// update score
	updateScore();

	// diplay score
	displayScore();
}

uint8_t getPlayerInput(void) {
	uint8_t ultrasound, playerInput;
	
	// set the times
	l_currentMillis = millis();
	l_previousMillis = l_currentMillis;

	// while game time hasn't expired
	while ((l_currentMillis - l_previousMillis) < GAME_TIME){

		// update codee
		codee.update();

		// update countdown tone
		countDownTone();

		// get player inpuet and process
		ultrasound = codee.readUltrasound();

		if (ultrasound < ROCK_US) {
			codee.displayImage(DISPLAY_ROCK);
			playerInput = 0;
		} else if (ultrasound < PAPER_US) {
			codee.displayImage(DISPLAY_PAPER);
			playerInput = 1;
		} else if (ultrasound < SCISSORS_US) {
			codee.displayImage(DISPLAY_SCISSORS);
			playerInput = 2;
		}

		// update current time
		l_currentMillis = millis();
	}

	return(playerInput);
}

void countDownTone(void) {
	// create local timmer variables
	static unsigned long l_currentMillis;
	static unsigned long l_previousMillis = 0;

	// use counts to increase tone each itteration
	static uint8_t count = 0;

	// set the times
	l_currentMillis = millis();

	if ((l_currentMillis - l_previousMillis) > GAME_COUNTDOWN) {

		// save the last time we played a tone
		l_previousMillis = l_currentMillis;
		
		// play a tone 
		codee.playTone(NOTE_C6 + (count * 300), 100);

		// update count, rolls over to 0 on last tone
		count = (count + 1) % (GAME_TIME / GAME_COUNTDOWN);
	}
}

void displayChoices() {
	// announce result
	codee.sayDirect("The result is...");

	// display player choice 
	codee.displayCustom(DISPLAY_PLAYER);
	delay(GAME_DELAY);
	codee.displayImage(gameChoice[playerChoice]);
	delay(GAME_DELAY);

	// display codee choice 
	codee.displayCustom(DISPLAY_CODEE);
	delay(GAME_DELAY);
	codee.displayImage(gameChoice[codeeChoice]);
	delay(GAME_DELAY);
}

void updateScore() {
	if ((playerChoice - codeeChoice) == -2 || (playerChoice - codeeChoice) == 1) { // player wins
		playerScore++;
	}
	else {
		if (!((playerChoice - codeeChoice) == 0)) { // codee wins
			codeeScore++;
		}
	}

	// draw
}

void displayScore(void) {
	codee.displayCustom(DISPLAY_SCORE);
	delay(GAME_DELAY / 2);
	codee.displayDigits((playerScore * 10) + codeeScore);
	delay(GAME_DELAY / 2);
}