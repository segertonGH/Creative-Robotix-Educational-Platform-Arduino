/*
 Name:		CreativeRobotix.cpp
 Created:	7/10/2023 4:25:23 PM
 Author:	Simon Egerton

 Creative Robotix platform Arduino library. 

 Last updated October 18th, 2023

 Compile Notes:

 Additional libraies required for compile

 http://playground.arduino.cc/Code/NewPing

 New Ping conflicts with the Tone functions, edit the NewPing.h file
 and set the TIMMER_ENABLED setting to 'false'.  The header file can
 be found under the 'Arduino/libraries/NewPing' folder.

 https://github.com/wayoda/LedControl

 Creative Robotix

 http://creativerobotix.com.au

 Creative Science Foundation

 http://creative-science.org/

 http://creative-science.org/partnerships/creative-robotix/

*/

#include "CreativeRobotix.h"
#include <Arduino.h>

// Demo
#define PIN_DEMO				12

// Auxilary analoge inputs

#define PIN_AUX_0				A0
#define PIN_AUX_1				A1

// Line sensors

#define PIN_LINE1				A2
#define PIN_LINE2				A3
#define PIN_LINE3				A4
#define PIN_LINE4				A5
#define PIN_LINE5				A6

// Wheels 

#define PIN_LEFT_WHEEL_SERVO	2
#define PIN_RIGHT_WHEEL_SERVO	3
#define WHEEL_SPEED_MAX			30

#define VELOCITY_LEFT			0
#define VELOCITY_RIGHT			1

// Arms, head

#define PIN_LEFT_ARM_SERVO		4
#define PIN_RIGHT_ARM_SERVO		5
#define PIN_HEAD_SERVO			6

// Behaviour limits for arms and head

#define ARM_MAX_DEGREES			40
#define ARM_SWING_MAX_DEGREES	40
#define HEAD_SWING_MAX_DEGREES	40
#define HEAD_SWING_MAX_SPEED	5
#define ARMS_SWING_MAX_SPEED	5

// Speaker

#define PIN_SPEAKER					13

#define AUDIO_SAY			0
#define AUDIO_MELODY_BLTIN	1
#define AUDIO_MELODY_USR	2
#define AUDIO_TONE			3
#define AUDIO_MELODY_SPEED	4

// Bluetooth

#define PIN_SETUP_HC06			21
#define HC06_CMD_SETNAME		1
#define HC06_CMD_SETPIN			2

// Melody data 

#define AUDIO_MELODIES_BLTIN	5

const static uint16_t AUDIO_MELODIES_NOTES[] PROGMEM = {
	// Green Sleeves 
	19,
	NOTE_FS3,
	NOTE_A3, NOTE_B3,
	NOTE_CS4, NOTE_D4, NOTE_CS4,
	NOTE_B3, NOTE_GS3,
	NOTE_E3, NOTE_FS3, NOTE_GS3,
	NOTE_A3, NOTE_FS3,
	NOTE_FS3, NOTE_F3, NOTE_FS3,
	NOTE_GS3, NOTE_F3,
	NOTE_CS3,
	// Marry Had a Little Lamb
	26,
	NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3,
	NOTE_E3, NOTE_E3, NOTE_E3,
	NOTE_D3, NOTE_D3, NOTE_D3,
	NOTE_E3, NOTE_G3, NOTE_G3,
	NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3,
	NOTE_E3, NOTE_E3, NOTE_E3, NOTE_E3,
	NOTE_D3, NOTE_D3, NOTE_E3, NOTE_D3,
	NOTE_C3,
	// Happy Birthday
	25,
	NOTE_G3, NOTE_G3,
	NOTE_A3, NOTE_G3, NOTE_C4,
	NOTE_B3, NOTE_G3, NOTE_G3,
	NOTE_A3, NOTE_G3, NOTE_D4,
	NOTE_C4, NOTE_G3, NOTE_G3,
	NOTE_G4, NOTE_E4, NOTE_C4,
	NOTE_B3, NOTE_A3, NOTE_G4, NOTE_G4,
	NOTE_E4, NOTE_C4, NOTE_D4,
	NOTE_C4,
	// Star Wars
	40,
	NOTE_A3, NOTE_A3, NOTE_A3,
	NOTE_D4, NOTE_A4, NOTE_RST,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_E4, NOTE_RST, NOTE_A3, NOTE_A3, NOTE_A3,
	NOTE_D4, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_D5, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_E4,
	// Chariots of Fire
	81,
	NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_E4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_E4, NOTE_RST, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
	NOTE_C4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_E4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_RST, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
	NOTE_G4, NOTE_E4, NOTE_RST, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
	NOTE_C4, NOTE_RST, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
	NOTE_B4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
	NOTE_B4, NOTE_RST, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
	NOTE_B4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
	NOTE_C4
};

const uint8_t AUDIO_MELODIES_NOTES_LEN = sizeof(AUDIO_MELODIES_NOTES) / sizeof(uint16_t);

const static uint8_t AUDIO_MELODIES_DURATIONS[] PROGMEM = {
	// Green Sleevs
	19,
	4,
	2, 4,
	3, 8, 4,
	2, 4,
	3, 8, 4,
	2, 4,
	3, 8, 4,
	2, 4,
	1,
	// Mary Had a Little Lamb
	26,
	4, 4, 4, 4,
	4, 4, 2,
	4, 4, 2,
	4, 4, 2,
	4, 4, 4, 4,
	4, 4, 4, 4,
	4, 4, 4, 4,
	1,
	// Happy Birthday
	25,
	8, 8,
	4, 4, 4,
	2, 8, 8,
	4, 4, 4,
	2, 8, 8,
	4, 4, 4,
	4, 4, 8, 8,
	4, 4, 4,
	2,
	// Star Wars
	40,
	12, 12, 12,
	2, 2, 8,
	12, 12, 12, 2, 4,
	12, 12, 12, 2, 4,
	12, 12, 12, 2, 8, 12, 12, 12,
	2, 2,
	12, 12, 12, 2, 4,
	12, 12, 12, 2, 4,
	12, 12, 12, 2,
	// Chariots of fire
	81,
	8, 12, 12, 12,
	4, 4, 8, 8, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 4, 8, 8, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 4, 8, 8, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 4, 8, 8, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 16, 4, 16, 4, 16, 12, 12, 12,
	2, 8, 8, 12, 12, 12,
	4, 16, 4, 16, 4, 16, 12, 12, 12,
	2
};

const uint8_t AUDIO_MELODIES_DURATIONS_LEN = sizeof(AUDIO_MELODIES_DURATIONS) / sizeof(uint8_t);

const static uint16_t NOTES[] PROGMEM = { // NOTE_P0 included to force a nice hash function 
	NOTE_A1, NOTE_AS1, NOTE_B1, NOTE_P0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_P0, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1,	// Scale C1
	NOTE_A2, NOTE_AS1, NOTE_B2, NOTE_P0, NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_P0, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2,	// Scale C2 
	NOTE_A3, NOTE_AS1, NOTE_B3, NOTE_P0, NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_P0, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3,	// Scale C3 
	NOTE_A4, NOTE_AS1, NOTE_B4, NOTE_P0, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_P0, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4,	// Scale C4 
	NOTE_A5, NOTE_AS1, NOTE_B5, NOTE_P0, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_P0, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5,	// Scale C5 
	NOTE_A6, NOTE_AS1, NOTE_B6, NOTE_P0, NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_P0, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6,	// Scale C6 
	NOTE_A7, NOTE_AS1, NOTE_B7, NOTE_P0, NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_P0, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7,	// Scale C7 
	NOTE_P0, NOTE_P0, NOTE_P0, NOTE_P0, NOTE_C8, NOTE_CS8, NOTE_D1, NOTE_DS8															// Scale C8 
};

const uint8_t NOTES_LEN = sizeof(NOTES) / sizeof(uint16_t);


// Local 8x8 display data

const static uint32_t LED_DISPLAY_IMAGES[][2] PROGMEM = {
	0x3c420018, 0xe7a5a5e7,			// smile
	0x007e0018, 0xe7a5a5e7,			// neutral
	0x423c0018, 0xe7a5a5e7,			// frown
	0x0c0c000c, 0x1830331e,			// question mark
	0x00005735, 0x35570000,			// OK
	0x00040a11, 0x20408000,			// tick
	0x00422418, 0x18244200,			// cross
	0x7e3c1805, 0x03070507,			// rock
	0x1f3e7cf9, 0xf1070507,			// paper
	0xd8f82027, 0x54570107,			// sissors
	0x10387cfe, 0xfeee4400,			// Heart
	0x060e0c08, 0x08281800,			// Quaver
	0x066eecc8, 0x8898f000,			// Quaver x 2
	0x00000000, 0x00000000			// blank
};

const uint8_t LED_DISPLAY_IMAGES_LEN = sizeof(LED_DISPLAY_IMAGES) / sizeof(uint32_t) / 2;

const static uint32_t LED_DISPLAY_DIGITS[][2] PROGMEM = {
	0x0000e0a0, 0xa0a0e000,			// 0
	0x00008080, 0x80808000,			// 1
	0x0000e020, 0xe080e000,			// 2	
	0x0000e080, 0xe080e000,			// 3
	0x00008080, 0xe0a0a000,			// 4
	0x0000e080, 0xe020e000,			// 5
	0x0000e0a0, 0xe020e000,			// 6
	0x00008080, 0x8080e000,			// 7
	0x0000e0a0, 0xe0a0e000,			// 8
	0x00008080, 0xe0a0e000			// 9
};

const int LED_DIGITS_LEN = sizeof(LED_DISPLAY_DIGITS) / sizeof(uint32_t) / 2;

const static uint32_t LED_DISPLAY_CHARACTERS[][2] PROGMEM = {
	0x00000000, 0x00000000,
	0x18001818, 0x3c3c1800,
	0x00000000, 0x286c6c00,
	0x6c6cfe6c, 0xfe6c6c00,
	0x103c4038, 0x04781000,
	0x60660c18, 0x30660600,
	0xfc66a614, 0x3c663c00,
	0x00000000, 0x00040400,
	0x60301818, 0x18306000,
	0x060c1818, 0x180c0600,
	0x006c38fe, 0x386c0000,
	0x0010107c, 0x10100000,
	0x00000000, 0x60303000,
	0x0000003c, 0x00000000,
	0x06060000, 0x00000000,
	0x00060c18, 0x30600000,
	0x3c66666e, 0x76663c00,
	0x7e181818, 0x1c181800,
	0x7e060c30, 0x60663c00,
	0x3c666038, 0x60663c00,
	0x30307e32, 0x34383000,
	0x3c666060, 0x3e067e00,
	0x3c66663e, 0x06663c00,
	0x18181830, 0x30667e00,
	0x3c66663c, 0x66663c00,
	0x3c66607c, 0x66663c00,
	0x00181800, 0x18180000,
	0x0c181800, 0x18180000,
	0x6030180c, 0x18306000,
	0x00003c00, 0x3c000000,
	0x060c1830, 0x180c0600,
	0x18001838, 0x60663c00,
	0x003c421a, 0x3a221c00,
	0x6666667e, 0x66663c00,			// A
	0x3e66663e, 0x66663e00,			// B
	0x3c660606, 0x06663c00,			// C
	0x3e666666, 0x66663e00,			// D
	0x7e06063e, 0x06067e00,			// E
	0x0606063e, 0x06067e00,			// F
	0x3c667606, 0x06663c00,			// G
	0x6666667e, 0x66666600,			// H
	0x3c181818, 0x18183c00,			// ...
	0x1c363630, 0x30307800,
	0x66361e0e, 0x1e366600,
	0x7e060606, 0x06060600,
	0xc6c6c6d6, 0xfeeec600,
	0xc6c6e6f6, 0xdecec600,
	0x3c666666, 0x66663c00,
	0x06063e66, 0x66663e00,
	0x603c7666, 0x66663c00,
	0x66361e3e, 0x66663e00,
	0x3c66603c, 0x06663c00,
	0x18181818, 0x185a7e00,
	0x7c666666, 0x66666600,			// ...
	0x183c6666, 0x66666600,			// V
	0xc6eefed6, 0xc6c6c600,			// W
	0xc6c66c38, 0x6cc6c600,			// X
	0x1818183c, 0x66666600,			// Y
	0x7e060c18, 0x30607e00,			// Z
	0x78181818, 0x18187800,			// [
	0x00603018, 0x0c060000,			// '\'
	0x1e181818, 0x18181e00,			// ]
	0x00000082, 0x44281000,			// ^
	0x7e000000, 0x00000000,			// _
	0x0000000c, 0x18181800,			// `
	0x7c667c60, 0x3c000000,			// a
	0x3e66663e, 0x06060600,			// b
	0x3c660666, 0x3c000000,			// c
	0x7c66667c, 0x60606000,			// ...
	0x3c067e66, 0x3c000000,
	0x0c0c3e0c, 0x0c6c3800,
	0x3c607c66, 0x667c0000,
	0x6666663e, 0x06060600,
	0x3c181818, 0x00180000,
	0x1c363630, 0x30003000,
	0x66361e36, 0x66060600,
	0x18181818, 0x18181800,
	0xd6d6feee, 0xc6000000,
	0x6666667e, 0x3e000000,
	0x3c666666, 0x3c000000,
	0x06063e66, 0x663e0000,
	0xf0b03c36, 0x363c0000,
	0x06066666, 0x3e000000,
	0x3e403c02, 0x7c000000,
	0x1818187e, 0x18180000,
	0x7c666666, 0x66000000,			// ...
	0x183c6666, 0x00000000,			// v
	0x7cd6d6d6, 0xc6000000,			// w
	0x663c183c, 0x66000000,			// x
	0x3c607c66, 0x66000000,			// y
	0x3c0c1830, 0x3c000000,			// z
	0x7018180c, 0x18187000,
	0x0e181830, 0x18180e00,
	0x00080808, 0x08080000,
	0x00000036, 0x5c000000,
	0x00000000, 0x00000000			// del
};

const int LED_DISPLAY_CHARACTERS_LEN = sizeof(LED_DISPLAY_CHARACTERS) / sizeof(uint32_t) / 2;

#define GETSCROLLROW(c, b)				((byte)((c >> (8*b)) & 0xFF))
#define GETDISPLAYROW(c, b)				((byte)((c >> (8*(7-b)) & 0xFF)))

#define LED_SET_IMAGE					1
#define LED_SET_SCROLL_TEXT				2
#define LED_SET_NUMBER					3
#define LED_SET_ROW_DATA				4
#define LED_SET_SET_PIXEL				5
#define LED_SET_CLEAR					6

#define LED_DISPLAY_TYPE_IMAGES			0
#define LED_DISPLAY_TYPE_DIGITS			1
#define LED_DISPLAY_TYPE_ASCII			2

//==============================================================================
// FUNCTIONS (CREATIVE ROBOTIX PLATFORM)
//==============================================================================

// constructor 
CreativeRobotix::CreativeRobotix() {

	// set up DEMO pin

	pinMode(PIN_DEMO, INPUT_PULLUP);

	// set up AUX and LINE inputs

	pinMode(PIN_AUX_0, INPUT_PULLUP);
	pinMode(PIN_AUX_1, INPUT_PULLUP);

	pinMode(PIN_LINE1, INPUT);
	pinMode(PIN_LINE2, INPUT);
	pinMode(PIN_LINE3, INPUT);
	pinMode(PIN_LINE4, INPUT);
	pinMode(PIN_LINE5, INPUT);

	// audio
	pinMode(PIN_SPEAKER, OUTPUT);
	
	// servos attach()

	_servos[PIN_LEFT_WHEEL_SERVO].attach(PIN_LEFT_WHEEL_SERVO);
	_servos[PIN_RIGHT_WHEEL_SERVO].attach(PIN_RIGHT_WHEEL_SERVO);
	_servos[PIN_LEFT_ARM_SERVO].attach(PIN_LEFT_ARM_SERVO);
	_servos[PIN_RIGHT_ARM_SERVO].attach(PIN_RIGHT_ARM_SERVO);
	_servos[PIN_HEAD_SERVO].attach(PIN_HEAD_SERVO);

	// servos detach()

	_servos[PIN_LEFT_WHEEL_SERVO].detach();
	_servos[PIN_RIGHT_WHEEL_SERVO].detach();
	_servos[PIN_LEFT_ARM_SERVO].detach();
	_servos[PIN_RIGHT_ARM_SERVO].detach();
	_servos[PIN_HEAD_SERVO].detach();

	// Initialise the MAX72XX display 

	_ledDisplay.shutdown(0, false);		// The MAX72XX is in power-saving mode on startup
	_ledDisplay.setIntensity(0, 7);		// Set the brightness to (7), maximum value (15)
	_ledDisplay.clearDisplay(0);		// and clear the display

	// Initialise wheel servos and servo arrays to zero 

	_setVelocityLeftWheel(90);
	_setVelocityRightWheel(90);
}

// initialise robot
void CreativeRobotix::begin(void) {
	// LED Display to neutral

	_setLEDDisplayImage(DISPLAY_NEUTRAL);

	// Say hello, I'm active
	sayDirect("Hello World!");

	_setLEDDisplayImage(DISPLAY_SMILE);
}

// LED Matrix display functions
void CreativeRobotix::_restoreLEDDisplay(void){
	switch (_ledDisplayType) {
	case LED_DISPLAY_TYPE_IMAGES:
		_setLEDDisplayImage(_ledDisplayImage);
		break;
	case LED_DISPLAY_TYPE_DIGITS:
		_setLEDDisplayDigits(_ledDisplayDigits);
		break;
	case LED_DISPLAY_TYPE_ASCII:
		_setLEDDisplayASCII(_ledDisplayASCII);
		break;
	default:
		break;
	}
}

void CreativeRobotix::_setLEDDisplayImage(uint8_t image) {
	uint64_t character;
	character = pgm_read_dword(&(LED_DISPLAY_IMAGES[image][0])); // High
	character = (character << 32) | pgm_read_dword(&(LED_DISPLAY_IMAGES[image][1])); // Low
	_setLEDisplay(character);
	_ledDisplayImage = image;
	_ledDisplayType = LED_DISPLAY_TYPE_IMAGES;
}

void CreativeRobotix::_setLEDDisplayDigits(uint8_t number) {
	uint64_t digit_tens, digit_units;
	digit_tens = pgm_read_dword(&(LED_DISPLAY_DIGITS[int(number / 10)][0])); // High
	digit_tens = (digit_tens << 32) | pgm_read_dword(&(LED_DISPLAY_DIGITS[int(number / 10)][1])); // Low
	digit_units = pgm_read_dword(&(LED_DISPLAY_DIGITS[number - (int(number / 10) * 10)][0])); // High
	digit_units = (digit_units << 32) | pgm_read_dword(&(LED_DISPLAY_DIGITS[number - (int(number / 10) * 10)][1])); // Low
	_setLEDisplay((digit_tens >> 4) | digit_units);
	_ledDisplayDigits = number;
	_ledDisplayType = LED_DISPLAY_TYPE_DIGITS;
}

void CreativeRobotix::_setLEDDisplayASCII(uint8_t ascii) {
	uint64_t character;
	character = pgm_read_dword(&(LED_DISPLAY_CHARACTERS[ascii - ' '][0])); // High
	character = (character << 32) | pgm_read_dword(&(LED_DISPLAY_CHARACTERS[ascii - ' '][1])); // Low
	_setLEDisplay(character);
	_ledDisplayASCII = ascii;
	_ledDisplayType = LED_DISPLAY_TYPE_ASCII;
}

void CreativeRobotix::_setLEDisplay(const uint64_t character)
{
	for (uint8_t row = 0; row < 8; row++)
	{
		_ledDisplay.setRow(0, row, GETDISPLAYROW(character, row));
	}
}

void CreativeRobotix::_updateTextToSay(void) {
	/* timer variables */
	static uint8_t character = 0;
	static boolean toneActive = false;
	static unsigned long l_currentMillis;	// store the current value from millis()
	static unsigned long l_previousMillis;	// for comparison with currentMillis
	static unsigned long toneDuration;		// store current tone duration

	l_currentMillis = millis();

	if (character >= _textToSayLen) { // All done, reset
		_isTextToSay = false;
		character = 0;
		_textToSayLen = 0;
	}
	else { // Still have a character to say, have we finished the tone?
		if (!toneActive) { // If no active tone, play the next one
			toneDuration = _textToSayBuffer[character] / 2;
			tone(PIN_SPEAKER, (128 - _textToSayBuffer[character]) * 100, toneDuration); // convert character to suitable frequency, currently arbitary, update?
			toneActive = true;
			l_previousMillis = l_currentMillis;
		}
		else { // update timmer and tone
			if ((l_currentMillis - l_previousMillis) > toneDuration) { // tone duration reached
				noTone(PIN_SPEAKER);
				toneActive = false;
				character++; // next character
			}
		}
	}
}

void CreativeRobotix::_setMelodytoPlay(uint8_t melody) {
	_melodyRecordStart = 0; // Reset the record start

	for (uint8_t i = 0; i < melody; i++) {  // Work out melodies location
		_melodyRecordStart += pgm_read_word(&(AUDIO_MELODIES_NOTES[_melodyRecordStart])) + 1; // melody record number_of_notes (+1);
	}

	_melodyToPlayLen = pgm_read_word(&(AUDIO_MELODIES_NOTES[_melodyRecordStart]));

	_melodyRecordStart = _melodyRecordStart + 1; // offset the melody record start for first note in record
}

void CreativeRobotix::_updateMelodyToPlay(boolean isUserMelody) {
	/* timer variables */
	static uint8_t note = 0;
	static uint16_t noteFrequency;
	static boolean noteActive = false, notePause = false;
	static unsigned long l_currentMillis;	// store the current value from millis()
	static unsigned long l_previousMillis;	// for comparison with currentMillis
	static unsigned long noteDuration;		// store current note duration
	static unsigned long notePauseDuration;	// store current note duration

	l_currentMillis = millis();

	if (note >= _melodyToPlayLen) { // All done, reset
		_isMelodyToPlay = false;
		note = 0;
		_melodyToPlayLen = 0;
	}
	else { // Still have a note to play, have we finished the note?
		if (!noteActive) { // If no active note, play the next one
			if (isUserMelody) {
				noteDuration = ((1000.0 / _melodyToPlaySpeed) / (float)_melodyToPlayDurationBuffer[note]);
				noteFrequency = _melodyToPlayNoteBuffer[note];
			}
			else {
				noteDuration = ((1000.0 / _melodyToPlaySpeed) / (float)pgm_read_byte(&(AUDIO_MELODIES_DURATIONS[_melodyRecordStart + note])));
				noteFrequency = pgm_read_word(&(AUDIO_MELODIES_NOTES[_melodyRecordStart + note]));
			}
			tone(PIN_SPEAKER, noteFrequency, noteDuration);
			noteActive = true;
			l_previousMillis = l_currentMillis;
		}
		else { // update timmer and tone
			if (!notePause) {
				if ((l_currentMillis - l_previousMillis) > noteDuration) { // tone duration reached
					notePauseDuration = noteDuration * 0.30; // 30% seems to work well
					notePause = true;
					l_previousMillis = l_currentMillis;
				}
			}
			else {
				if ((l_currentMillis - l_previousMillis) > notePauseDuration) {
					noTone(PIN_SPEAKER);
					notePause = false;
					noteActive = false;
					note++; // next note
				}
			}
		}
	}
}

void CreativeRobotix::_updateTextToScroll(boolean reset) {
	static uint8_t character = 0, character_previous = 1, character_scroll = 0, cindex;
	static unsigned long l_currentMillis;	// store the current value from millis()
	static unsigned long l_previousMillis;	// for comparison with currentMillis
	static uint64_t current_character = 0, screen = 0, column_update;

	l_currentMillis = millis();

	if (reset) {  // reset the state
		character = 0;
		character_previous = 1, character_scroll = 0;
		current_character = 0, screen = 0, column_update = 0;
	}

	// take care of special condition when there is only one character to scroll (were current_character acts as a buffer)
	if (_textToScrollLen == 1) {

		cindex = _textToScrollBuffer[0] - ' ';
		uint64_t test_character = pgm_read_dword(&(LED_DISPLAY_CHARACTERS[cindex][0])); // High
		test_character = (test_character << 32) | pgm_read_dword(&(LED_DISPLAY_CHARACTERS[cindex][1])); // Low

		if (test_character != current_character) current_character = test_character;
	}

	if ((l_currentMillis - l_previousMillis) > _scrollInterval) {
		// update screen buffer 

		if (character_scroll >= MAX72XX_WIDTH) {  // time to shift in next character? 
			character = (character + 1) % _textToScrollLen;
			character_scroll = 0;
		}

		if (character != character_previous) {  // shift in next character on character change
			character_previous = character;
			cindex = _textToScrollBuffer[character] - ' ';  // characters start from 0x20 or ASCII ' ' 
			current_character = pgm_read_dword(&(LED_DISPLAY_CHARACTERS[cindex][0])); // High
			current_character = (current_character << 32) | pgm_read_dword(&(LED_DISPLAY_CHARACTERS[cindex][1])); // Low
		}

		screen = _shiftScreenLeft(screen);  // shift screen left one column, update to selected column shifts and or direction 
		column_update = (current_character & (0x0101010101010101 << character_scroll)) << ((MAX72XX_WIDTH - 1) - character_scroll); // character_scroll selects next column to shift in on the right
		screen = screen | column_update; // update the screen with the column 

		// update screen

		_setLEDisplay(screen);

		// update variables
		character_scroll++;
		l_previousMillis = l_currentMillis;

		// TODO: Multi screen scroll 
	}
}

uint64_t CreativeRobotix::_shiftScreenLeft(uint64_t screen) {
	uint64_t new_screen = 0;

	for (int8_t row = MAX72XX_WIDTH - 1; row >= 0; row--) {
		new_screen = (new_screen << 8) | ((GETSCROLLROW(screen, row) >> 1) & 0xFF);  // columns are labeled left to right from 1 to 7, hence sifts are opposit in sense, may physically invert the screen to fix?
	}

	return (new_screen);
}

int8_t CreativeRobotix::_boundWheelVelocity(int8_t velocity) {
	if (velocity < -WHEEL_SPEED_MAX) {
		velocity = -WHEEL_SPEED_MAX;
	}
	else if (velocity > WHEEL_SPEED_MAX) {
		velocity = WHEEL_SPEED_MAX;
	}

	return(velocity);
}

void CreativeRobotix::_setVelocityLeftWheel(uint8_t velocity) {
	if (!_servos[PIN_LEFT_WHEEL_SERVO].attached()) _servos[PIN_LEFT_WHEEL_SERVO].attach(PIN_LEFT_WHEEL_SERVO);

	_servos[PIN_LEFT_WHEEL_SERVO].write(velocity);

	if (velocity == 90) _servos[PIN_LEFT_WHEEL_SERVO].detach();
}

void CreativeRobotix::_setVelocityRightWheel(uint8_t velocity) {
	if (!_servos[PIN_RIGHT_WHEEL_SERVO].attached()) _servos[PIN_RIGHT_WHEEL_SERVO].attach(PIN_RIGHT_WHEEL_SERVO);

	_servos[PIN_RIGHT_WHEEL_SERVO].write(velocity);

	if (velocity == 90) _servos[PIN_RIGHT_WHEEL_SERVO].detach();
}

void CreativeRobotix::_setHead(uint8_t angle) {

	if (!_servos[PIN_HEAD_SERVO].attached()) _servos[PIN_HEAD_SERVO].attach(PIN_HEAD_SERVO);

	if (angle < (90 - HEAD_SWING_MAX_DEGREES)) angle = 90 - HEAD_SWING_MAX_DEGREES;
	if (angle > (90 + HEAD_SWING_MAX_DEGREES)) angle = 90 + HEAD_SWING_MAX_DEGREES;

	_servos[PIN_HEAD_SERVO].write(angle);
}

void CreativeRobotix::_updateHeadSwing(void) {
	static uint8_t angle = 90;
	static int8_t direction = 1;
	static unsigned long l_currentMillis;	// store the current value from millis()
	static unsigned long l_previousMillis;	// for comparison with currentMilli()

	l_currentMillis = millis();

	if ((l_currentMillis - l_previousMillis) > _headSwingInterval) {

		angle = angle + (_headSwingSpeed * direction);

		if (angle < (90 - HEAD_SWING_MAX_DEGREES) || angle >(90 + HEAD_SWING_MAX_DEGREES)) direction = direction * -1; // change direction

		_setHead(angle);

		// update variables
		l_previousMillis = l_currentMillis;
	}
}

void CreativeRobotix::_updateArmsSwing(void) {
	static uint8_t angle = 90;
	static int8_t direction = 1;
	static unsigned long l_currentMillis;	// store the current value from millis()
	static unsigned long l_previousMillis;	// for comparison with currentMilli()

	l_currentMillis = millis();

	if ((l_currentMillis - l_previousMillis) > _armSwingInterval) {

		if (angle < (90 - ARM_SWING_MAX_DEGREES) || angle >(90 + ARM_SWING_MAX_DEGREES)) direction = direction * -1; // change direction

		angle = angle + (_armSwingSpeed * direction);

		_setLeftArm(angle);
		_setRightArm(angle);

		// update variables
		l_previousMillis = l_currentMillis;
	}
}

void CreativeRobotix::_setLeftArm(uint8_t angle) {
	// Enable servos?
	if (!_servos[PIN_LEFT_ARM_SERVO].attached()) _servos[PIN_LEFT_ARM_SERVO].attach(PIN_LEFT_ARM_SERVO);

	if (angle < (90 - ARM_MAX_DEGREES)) angle = 90 - ARM_MAX_DEGREES;
	if (angle > (90 + ARM_MAX_DEGREES)) angle = 90 + ARM_MAX_DEGREES;

	_servos[PIN_LEFT_ARM_SERVO].write(angle);
}

void CreativeRobotix::_setRightArm(uint8_t angle) {
	// Enable servos?
	if (!_servos[PIN_RIGHT_ARM_SERVO].attached()) _servos[PIN_RIGHT_ARM_SERVO].attach(PIN_RIGHT_ARM_SERVO);

	if (angle < (90 - ARM_SWING_MAX_DEGREES)) angle = 90 - ARM_SWING_MAX_DEGREES;
	if (angle > (90 + ARM_SWING_MAX_DEGREES)) angle = 90 + ARM_SWING_MAX_DEGREES;

	_servos[PIN_RIGHT_ARM_SERVO].write(angle);
}

void CreativeRobotix::_servoStop(uint8_t servo) {
	_servos[servo].detach();
}

uint32_t CreativeRobotix::_readVcc(void)
{
	// Decide if we have battery power i.e. a value > 4700 (or 4.7 volts)
	int32_t result;
	// Read 1.1V reference against AVcc
	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	delay(2); // Wait for Vref to settle
	ADCSRA |= _BV(ADSC); // Convert
	while (bit_is_set(ADCSRA, ADSC));
	result = ADCL;
	result |= ADCH << 8;
	result = 1126400L / result; // Back-calculate AVcc in mV
	return result;
}

void CreativeRobotix::sayDirect(String text) {
	// Say text string, uses delay, private use only
	for (uint8_t i = 0; i < text.length(); i++) {
		if (text[i] < 128) {
			tone(PIN_SPEAKER, (128 - text[i]) * 100, text[i] / 2); // Arbitary frequency mapping, for printable characters only.
			delay(text[i] / 2);
			noTone(PIN_SPEAKER);
		}
	}
}

void CreativeRobotix::update(void) {
	if (_isTextToSay) _updateTextToSay();
	if (_isTextToScroll) _updateTextToScroll(false);
	if (_isArmsSwing) _updateArmsSwing();
	if (_isHeadSwing) _updateHeadSwing();
	if (_isMelodyToPlay) _updateMelodyToPlay(_isUserMelody);
}

boolean CreativeRobotix::say(String text) {
	if (text.length() < TEXT_TO_SAY_BUFFER_LEN) {
		strcpy((char*)_textToSayBuffer, text.c_str());
		_textToSayLen = text.length();
		_isTextToSay = true;
		return(true);
	}
	return(false);
}

boolean CreativeRobotix::hasTextToSay(void) {
	return(_isTextToSay);
}

boolean CreativeRobotix::displayScrollText(String text) {
	if (text.length() < TEXT_TO_SCROLL_BUFFER_LEN) {
		strcpy((char*)_textToScrollBuffer, text.c_str());
		_textToScrollLen = text.length();
		_isTextToScroll = true;
		return(true);
	}
	return(false);
}

boolean CreativeRobotix::displayScrollText(String text, boolean reset) {
	if (text.length() < TEXT_TO_SCROLL_BUFFER_LEN) {
		strcpy((char*)_textToScrollBuffer, text.c_str());
		_textToScrollLen = text.length();
		_isTextToScroll = true;
		_updateTextToScroll(reset);
		return(true);
	}
	return(false);
}

void CreativeRobotix::displayScrollTextReset(void) {
		_updateTextToScroll(true);
}

boolean CreativeRobotix::hasTextToScroll(void) {
	return(_isTextToScroll);
}

boolean CreativeRobotix::displayImage(uint8_t image) {
	if (image < LED_DISPLAY_IMAGES_LEN) {
		_isTextToScroll = false;
		_setLEDDisplayImage(image);
		return(true);
	}
	return (false);
}

boolean CreativeRobotix::displayDigits(uint8_t number) {
	if (number >=0 && number < LED_DIGITS_LEN * 10) {
		_isTextToScroll = false;
		_setLEDDisplayDigits(number);
		return(true);
	}
	return (false);
}

boolean CreativeRobotix::displayASCII(uint8_t ascii) {
	if ((ascii - ' ') >= 0 && (ascii - ' ') < LED_DISPLAY_CHARACTERS_LEN) {
		_isTextToScroll = false;
		_setLEDDisplayASCII(ascii);
		return(true);
	}
	return (false);
}

boolean CreativeRobotix::displayPixel(uint8_t row, uint8_t column, boolean state) {
	if ((row >= 0 && row < MAX72XX_WIDTH) && (column >= 0 && column < MAX72XX_HEIGHT)) {
		_ledDisplay.setLed(0, row, column, state);
		return(true);
	}
	return(false);
}

boolean CreativeRobotix::displayClear(void) {
	_isTextToScroll = false;
	_setLEDDisplayImage(DISPLAY_BLANK);
}

boolean CreativeRobotix::displayReset(void) {
	_isTextToScroll = false;
	_restoreLEDDisplay();
}

boolean CreativeRobotix::displayCustom(uint64_t screen) {
	_setLEDisplay(screen);
}

boolean CreativeRobotix::playMelody(uint8_t melody) {
	_setMelodytoPlay(melody % AUDIO_MELODIES_BLTIN);
	_isUserMelody = false;
	_isMelodyToPlay = true;
	return(true);
}

boolean CreativeRobotix::playCustom(uint16_t notes[], uint8_t duration[], uint8_t notesToPlay) {
	_melodyToPlayLen = 0;

	for (uint8_t note = 0; note < notesToPlay && (_melodyToPlayLen < MELODY_TO_PLAY_BUFFER_LEN); note++) { // Silently drop notes > MAX_BUFFER

		_melodyToPlayNoteBuffer[_melodyToPlayLen] = notes[note];
		_melodyToPlayDurationBuffer[_melodyToPlayLen] = duration[note];
		_melodyToPlayLen++;
	}

	_isUserMelody = true;
	_isMelodyToPlay = true;
	return(true);
}

boolean CreativeRobotix::playTone(uint16_t frequency, uint16_t duration) {
	_melodyToPlayNoteBuffer[0] = frequency;
	_melodyToPlayDurationBuffer[0] = (1000.0 / (float)(duration)) / _melodyToPlaySpeed; // Rescale with melodyToPlaySpeed
	_melodyToPlayLen = 1;
	_isUserMelody = true;
	_isMelodyToPlay = true;
	return (true);
}

boolean CreativeRobotix::setMelodySpeed(uint8_t tempo) {
	if (tempo > 0 && tempo <= 10) {
		_melodyToPlaySpeed = (float)(tempo * 100) / 100.0; // why do this?
		return (true);
	}
	return(false);
}

boolean CreativeRobotix::hasMelodytoPlay(void) {
	return(_isMelodyToPlay);
}

uint8_t CreativeRobotix::readUltrasound(void) {
	return(_sonar.ping_cm()); // Take reading in cm
}

uint8_t CreativeRobotix::readUltrasoundMedian(uint8_t window) {
	return(_sonar.convert_cm(_sonar.ping_median(window))); // Take reading in cm
}

void CreativeRobotix::readLineSensors(void) {
	lineSensors[0] = digitalRead(PIN_LINE1);
	lineSensors[1] = digitalRead(PIN_LINE2);
	lineSensors[2] = digitalRead(PIN_LINE3);
	lineSensors[3] = digitalRead(PIN_LINE4);
	if (analogRead(PIN_LINE5) > 750) {
		lineSensors[4] = true;
	}
	else {
		lineSensors[4] = false;
	}
}

void CreativeRobotix::readAuxInputs(void) {
	auxInputs[0] = analogRead(PIN_AUX_0);
	auxInputs[1] = analogRead(PIN_AUX_1);
}

void CreativeRobotix::readLine(void) {
	uint8_t online = 0, position = 0;
	
	// read line position
	readLineSensors();

	// count weighted sum of sensors online
	for (uint8_t i = 0; i < LINE_SENSORS; i++) {
		if (lineSensors[i] == false) {
			online = online + 1;
			position = position + (i + 1);
		}
	}

	// position on line 0 center; >0 right of line; <0 left of line 
	if (!online) {
		linePosition = LINE_SENSORS + 1;
		lineState = (2 * LINE_SENSORS);
	}
	else if (online == LINE_SENSORS) {
		linePosition = LINE_SENSORS;
		lineState = (2 * LINE_SENSORS) - 1;
	}
	else {
		linePosition = ((float)position / (float)online) - 3.0; // 3.0 represents the centre linesensor
		lineState = 2 * (linePosition + 2);
	}
}

void CreativeRobotix::wheelLeft(int8_t velocity) {
	velocity = 90 + _boundWheelVelocity(velocity);

	_setVelocityLeftWheel(velocity);
}

void CreativeRobotix::wheelRight(int8_t velocity) {
	velocity = 90 - _boundWheelVelocity(velocity);

	_setVelocityRightWheel(velocity);
}

boolean CreativeRobotix::hasStopped(void) {
	if (_servos[PIN_RIGHT_WHEEL_SERVO].read() == 90) {
		return(true);
	}

	return(false);
}

void CreativeRobotix::headAngle(int8_t angle, boolean state) {
	if (state) {
		angle = 90 + angle;

		_setHead(angle); // detach servo after setting angle
	}
	else
	{
		_servoStop(PIN_HEAD_SERVO);
	}
}

void CreativeRobotix::lookAround(uint8_t speed, boolean state) {
	if (state) {
		if (speed > HEAD_SWING_MAX_SPEED) speed = HEAD_SWING_MAX_SPEED;
		_headSwingSpeed = speed;
		_isHeadSwing = true;
	}
	else {
		_isHeadSwing = false;
		_servoStop(PIN_HEAD_SERVO);
	}
}

void CreativeRobotix::swingArms(uint8_t speed, boolean state) {
	if (state) {
		if (speed > ARMS_SWING_MAX_SPEED) speed = ARMS_SWING_MAX_SPEED;
		_armSwingSpeed = speed;
		_isArmsSwing = true;
	}
	else {
		_isArmsSwing = false;
		_servoStop(PIN_LEFT_ARM_SERVO);
		_servoStop(PIN_RIGHT_ARM_SERVO);
	}
}

void CreativeRobotix::armLeft(int8_t angle, boolean state) {
	if (state) {
		if (angle < -ARM_MAX_DEGREES) angle = -ARM_MAX_DEGREES;
		if (angle > ARM_MAX_DEGREES) angle = ARM_MAX_DEGREES;

		angle = 90 - angle;

		_setLeftArm(angle);
	}
	else {
		_servoStop(PIN_LEFT_ARM_SERVO);
	}
}

void CreativeRobotix::armRight(int8_t angle, boolean state) {
	if (state) {
		if (angle < -ARM_MAX_DEGREES) angle = -ARM_MAX_DEGREES;
		if (angle > ARM_MAX_DEGREES) angle = ARM_MAX_DEGREES;

		angle = 90 + angle;

		_setRightArm(angle);
	}
	else {
		_servoStop(PIN_RIGHT_ARM_SERVO);
	}
}

uint8_t CreativeRobotix::readBatteryVoltage(void) {
	return(_readVcc()/100);
}
boolean CreativeRobotix::btConfigure(String myRobotsName, uint16_t myRobotsPin) {
	uint8_t i;
	boolean btatcrlf = true;
	String response, command;
	unsigned long baudrate[] = { 57600, 9600, 1200, 2400, 4800, 19200, 38400, 115200 };

	if (analogRead(PIN_SETUP_HC06) > 50) { // Nothing to do 
		return (false);
	}

	// Discover HC-06 current baudrate

	uint8_t baudrates = sizeof(baudrate) / sizeof(baudrate[0]);

	for (i = 0; i < baudrates; i++) {

		// Try to connect
		sayDirect("ATAT");
		Serial.begin(baudrate[i]);

		// Two types of firmwaire to deal with, types which require <CR><LF>, and types that do not

		// Are we dealing with HC-05 type firmaware requiring <CR><LF>?

		Serial.print("AT\r\n");
		Serial.setTimeout(1000);
		response = Serial.readString();

		Serial.print("AT\r\n");			// TODO: Find out why this only works the second time, timming? Delays?
		Serial.setTimeout(1000);
		response = Serial.readString();

		// Were we successful? 

		if (response.startsWith("OK")) {
			break; // Yes, got it.
		}

		// Are we deadling with HC-06 firware with NO <CR><LF> needed?

		Serial.print("AT");
		Serial.setTimeout(1000);
		response = Serial.readString();

		Serial.print("AT");			// TODO: Find out why this only works the second time, timming? Delays?
		Serial.setTimeout(1000);
		response = Serial.readString();

		// Were we successful? 

		if (response.startsWith("OK")) {
			btatcrlf = false;
			break; // Yes, got it.
		}

		Serial.end();
	}

	if (i == baudrates) { // Couldn't connect to the HC-06
		while (1) { sayDirect("{}"); delay(100); }; // Sound the alarm... 
	}

	// All good, let's congigure... 

	// Set Name
	// TODO restrict name to 20 characters 
	(btatcrlf) ? command = (String)"AT+NAME" + (String)myRobotsName + (String)"\r\n" : command = (String)"AT+NAME" + (String)myRobotsName;
	Serial.print(command);
	Serial.setTimeout(3000);
	delay(500);
	sayDirect("OK");
	// Set Pin

	(btatcrlf) ? command = (String)"AT+PIN" + myRobotsPin + (String)"\r\n" : command = (String)"AT+PIN" + myRobotsPin;
	Serial.print(command);
	Serial.setTimeout(3000);
	delay(500);
	sayDirect("OK");

	// Disable indications

	(btatcrlf) ? command = (String)"AT+ENABLEIND0" + (String)"\r\n" : command = (String)"AT+ENABLEIND0";
	Serial.print(command);
	Serial.setTimeout(3000);
	delay(500);
	sayDirect("OK");

	// Set S4A Baud rate

	(btatcrlf) ? command = (String)"AT+BAUD7" + (String)"\r\n" : command = (String)"AT+BAUD7";

	Serial.print(command);
	Serial.setTimeout(3000);
	delay(500);
	sayDirect("OK");

	Serial.end();

	// setup complete
	return(true);
}

void CreativeRobotix::btSetName(String myRobotName) {
	// Type HC05 firmware
	Serial.print("AT\r\n");
	Serial.setTimeout(1000);
	String responsecrlf = Serial.readString();

	// Type HC06 firmware
	Serial.print("AT");
	Serial.setTimeout(1000);
	String response = Serial.readString();

	// Were we successful?

	if (responsecrlf.startsWith("OK") || response.startsWith("OK")) {

		String hc06Command = "AT+NAME";  // Build command string

		hc06Command += myRobotName;

		// type HC05 firmware
		if (responsecrlf.startsWith("OK")) {
			hc06Command += (String)"\r\n";
			Serial.print(hc06Command);
			Serial.setTimeout(3000);
			delay(500);
			Serial.print(hc06Command);
			Serial.setTimeout(3000);
			delay(500);
		}

		//type HC06 firmware
		if (response.startsWith("OK")) {
			Serial.print(hc06Command);
			Serial.setTimeout(3000);
			delay(500);
		}

		sayDirect("ok ok ok");
	}
	else
	{
		sayDirect("{}{}{}{}{}{}{}{}{}"); // Signal Error
	}
}

void CreativeRobotix::btSetPin(uint16_t myRobotPin) {
	// Type HC05 firmware
	Serial.print("AT\r\n");
	Serial.setTimeout(1000);
	String responsecrlf = Serial.readString();

	// Type HC06 firmware
	Serial.print("AT");
	Serial.setTimeout(1000);
	String response = Serial.readString();

	// Were we successful?

	if (responsecrlf.startsWith("OK") || response.startsWith("OK")) {

		String hc06Command = "AT+PIN";  // Build command string

		hc06Command += String(myRobotPin);

		// type HC05 firmware
		if (responsecrlf.startsWith("OK")) {
			hc06Command += (String)"\r\n";
			Serial.print(hc06Command);
			Serial.setTimeout(3000);
			delay(500);
			Serial.print(hc06Command);
			Serial.setTimeout(3000);
			delay(500);
		}

		//type HC06 firmware
		if (response.startsWith("OK")) {
			Serial.print(hc06Command);
			Serial.setTimeout(3000);
			delay(500);
		}

		sayDirect("ok ok ok");
	}
	else
	{
		sayDirect("{}{}{}{}{}{}{}{}{}"); // Signal Error
	}
}

boolean CreativeRobotix::demo(void) {
	// demo pin is enabled with pull_up 
	if (digitalRead(PIN_DEMO) == HIGH) {
		return (false);
	}
	return(true);
}