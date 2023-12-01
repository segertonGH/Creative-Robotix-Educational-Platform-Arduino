/*
 Creative Robotix: bat and ball

 This example plays the game of bat and ball.  The player controls by variing the distance 
 of their hand in front of Codees ultrasound sensor.  The game ends when the player reaches 
 the winning score as defined by WINNING_SCORE (this is equal to the number of time the bat hits 
 the ball in a row), or until the player misses the ball.  Change GAME_DELAY to increase the 
 the difficult of the game play, the default value is 250.

 Created 15 October 2023
 by Simon Egerton

 Creative Robotix 

 http://creativerobotix.com.au

 Creative Science Foundation

 http://creative-science.org/

 http://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

 //---------------------------------------------------------------------
 // change the speed of the ball, smaller values are faster
#define GAME_DELAY 250

// Change to increase the total score to win
#define WINNING_SCORE 15
//---------------------------------------------------------------------

 // play positions in CM relative to the ultrasound sensor
static uint8_t bat_positions[] = { 8, 12, 16, 20, 24, 28 };

#define TRIGGER_WINDOW	2

// player variables
uint8_t playerBatNow = 1, playerBatPosition = 2, newPlayerBatPosition = 1;
uint8_t playerScore = 0, playerHighScore = 0;

// ball variables
int8_t balldx = 1, balldy = 1;
uint8_t ballx = 1, bally = 3;

// game over?
boolean gameOver = false;

static unsigned long l_currentMillis_b = 0;
static unsigned long l_previousMillis_b = 0;

// set up a new robot instance called codee
CreativeRobotix codee;

// the setup function runs once when you press reset or power the board
void setup() {
	// initilaise codee 
	codee.begin();

	// clear display
	codee.displayClear();

	// set codee pose
	codee.headAngle(0, true);
	codee.armLeft(0, true);
	codee.armRight(0, true);
}

// the loop function runs over and over again until power down or reset
void loop() {
	// update codees behaviours, arms, head, sound, display
	codee.update();

	// is the game to play ?
	if (!gameOver) {
		// update bat position for player
		updateBat();

		l_currentMillis_b = millis();

		// update ball position for Codee, score and check game over
		if ((l_currentMillis_b - l_previousMillis_b) > GAME_DELAY) {
			updateBall();

			// update current millis
			l_previousMillis_b = millis();

			// update score, check game logic
			updateScore();

			// is game over, then display result
			checkGameOver();
		}
	}
	else // trigger a new game after playing players victory tune (if max score of 99 achived)
	{
		// check no melody is playing first to avoid delaying codee. update with ultrasound reading
		if (!codee.hasMelodytoPlay()) {
			if (codee.readUltrasoundMedian(3) == bat_positions[0]) { // Hi five codee to play! 
				// reset codee
				codee.displayReset();
				codee.displayClear();

				// reset player and play
				playerBatNow = 1, playerBatPosition = 2, newPlayerBatPosition = 1;
				playerScore = 0;
				gameOver = false;
			}
		}
	}
}

void updateBall(void) {
	uint8_t ballxold = ballx, ballyold = bally;

	// update ball position
	ballx = ballx + (1 * balldx); // update x position
	if (ballx <= 0 || ballx >= (DISPLAY_WIDTH - 1)) { // check limits
		balldx = balldx * -1; // change direction if limits met
		codee.playTone(NOTE_C4, 10); // play ball ping
	}

	bally = bally + (1 * balldy); // update y position
	if (bally <= 1 || bally >= (DISPLAY_HEIGHT - 1)) { // check limits, y lower limits = 1, since bat occupies row 0
		balldy = balldy * -1; // change direction if limits met
		codee.playTone(NOTE_C4, 10); // play ball ping
	}

	if (ballxold != ballx || ballyold != bally) {  // update ball
		// x-axis maps to column, y-axis maps to row
		codee.displayPixel(ballyold, ballxold, false);
		codee.displayPixel(bally, ballx, true);
	}
}

void updateScore(void) {
	// is ball at row 1?
	if (bally == 1) {
		// if bat is not underneath the ball then loose
		if (ballx < (playerBatPosition - 1) || ballx >(playerBatPosition - 1) + 2)
		{
			codee.playTone(NOTE_C1, 500);  // play low sad note :-(
			gameOver = true;
		}
		else { // increase player score by 1
			playerScore++;

			if (playerScore >= WINNING_SCORE) gameOver = true; // max game score has been reached
		}
	}
}

void checkGameOver(void) {
	if (gameOver && playerScore < WINNING_SCORE) {
		if (playerScore > playerHighScore) playerHighScore = playerScore;
		codee.displayScrollText(" Game Over Score = " + String(playerScore) + " High Score = " + String(playerHighScore));
	}
	else {
		if (gameOver && playerScore >= WINNING_SCORE) {
			codee.displayScrollText("You Win With The Maximum Score Of " + String(WINNING_SCORE) + "!");
			codee.playMelody(MELODY_CHARIOTS);
		}
	}
}

void updateBat(void){
	playerBatNow = codee.readUltrasoundMedian(3); // get user input from ultrasound sensor
	if (playerBatNow) { // if there is a valid reading
		// check all bat positions
		for (uint8_t p = 0; p < sizeof(bat_positions) / sizeof(uint8_t); p++) {
			if (playerBatNow >= (bat_positions[p] - TRIGGER_WINDOW) && playerBatNow <= bat_positions[p]) {
				// found a match, exit the loop and return early
				newPlayerBatPosition = p + 1;
				break;
			}
		}
	}

	if (newPlayerBatPosition != playerBatPosition) {
		// remove the old bat
		codee.displayPixel(0, (playerBatPosition - 1) + 0, false);
		codee.displayPixel(0, (playerBatPosition - 1) + 1, false);
		codee.displayPixel(0, (playerBatPosition - 1) + 2, false);

		// diplay the new bat
		codee.displayPixel(0, (newPlayerBatPosition - 1) + 0, true);
		codee.displayPixel(0, (newPlayerBatPosition - 1) + 1, true);
		codee.displayPixel(0, (newPlayerBatPosition - 1) + 2, true);

		// update the bat position
		playerBatPosition = newPlayerBatPosition;
	}
}