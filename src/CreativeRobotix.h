/*
 Name:		CreativeRobotix.h
 Created:	7/10/2023 4:25:23 PM
 Author:	Simon Egerton

 Creative Robotix Platform Arduino Library.

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

#ifndef _CreativeRobotix_h
#define _CreativeRobotix_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
	#include <LedControl.h>
	#include <NewPing.h>
	#include <Servo.h>
	#include <Wire.h>
	#include <SoftwareSerial.h>
#else
	#include "WProgram.h"
#endif

// Display properties 8x8

#define DISPLAY_HEIGHT			8
#define DISPLAY_WIDTH			8

// Predefined display images
#define DISPLAY_SMILE				0
#define DISPLAY_NEUTRAL				1
#define DISPLAY_FROWN				2	
#define DISPLAY_QUESTION			3
#define DISPLAY_OK					4
#define DISPLAY_TICK				5	
#define DISPLAY_CROSS				6	
#define DISPLAY_ROCK				7
#define DISPLAY_PAPER				8
#define DISPLAY_SCISSORS			9	
#define DISPLAY_QUAVER				10
#define DISPLAY_QUAVERx2			11
#define DISPLAY_HEART				12
#define DISPLAY_BLANK				13 

// Built in Melodies

#define MELODY_GREENSLEEVES		0
#define MELODY_LITTLELAMB		1
#define MELODY_HAPPYBIRTHDAY	2
#define MELODY_STARWARS			3
#define MELODY_CHARIOTS			4

// Notes

#define NOTE_RST 0
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define NOTE_P0	 0000


// Class defination

class CreativeRobotix
{
public:
	CreativeRobotix();
	void begin();
	void update();

	// Servos

	void headAngle(int8_t angle, boolean state);
	void armLeft(int8_t angle, boolean state);
	void armRight(int8_t angle, boolean state);
	void wheelLeft(int8_t velocity);
	void wheelRight(int8_t velocity);
	boolean hasStopped(void);
	
	// Behaviours
	void lookAround(uint8_t speed, boolean state);
	void swingArms(uint8_t speed, boolean state);

	// LED Display

	void displayScrollTextReset(void);
	boolean displayScrollText(String text);
	boolean displayScrollText(String text, boolean reset);
	boolean displayImage(uint8_t image);
	boolean displayDigits(uint8_t number);
	boolean displayASCII(uint8_t ascii);
	boolean displayCustom(uint64_t screen);
	boolean displayClear(void);
	boolean displayReset(void);
	boolean displayPixel(uint8_t row, uint8_t column, boolean state);
	boolean hasTextToScroll(void);

	// Audio 'speech'
	void sayDirect(String text);
	boolean say(String text);
	boolean hasTextToSay(void);

	// Audio melodies and tunes
	boolean playMelody(uint8_t melody);
	boolean playCustom(uint16_t notes[], uint8_t rduration[], uint8_t notesToPlay);
	boolean playTone(uint16_t frequency, uint16_t duration);
	boolean setMelodySpeed(uint8_t tempo);
	boolean hasMelodytoPlay(void);

	// Ultrasound

	uint8_t readUltrasound(void);
	uint8_t readUltrasoundMedian(uint8_t window);

	// Line sensors

	boolean lineSensors[5];
	float linePosition;
	uint8_t lineState;
	void readLineSensors(void);
	void readLine(void);

	// User Analoge Inputs
	uint16_t auxInputs[2];
	void readAuxInputs(void);

	// battery
	uint8_t readBatteryVoltage(void);

	// Bluetooth
	boolean btConfigure(String myRobotName, uint16_t myRobotPin);
	void btSetName(String myRobotName);
	void btSetPin(uint16_t myRobotPin);

	// Demo pin set
	boolean demo(void);

private:

	// Line Sensors

	#define LINE_SENSORS			5

	// Ultrasound Sensor

	#define PIN_HCSR04_TRIGGER		11
	#define PIN_HCSR04_ECHO			10
	#define HCSR04_MAX_DISTANCE		60 // Sensor returns a range between 1 to HCR04_MAX_DISTANCE, and 0 otherwise
	#define HCSR04_CLEAR			0

	// MAX72XX LED 8x8 display

	#define MAX72XX_HEIGHT			8
	#define MAX72XX_WIDTH			8
	#define MAX72XX_DIN				9
	#define MAX72XX_CS				8
	#define MAX72XX_CLK				7

	// Data buffer sizes for sound, text and bluetooth

	#define MELODY_TO_PLAY_BUFFER_LEN	30
	#define TEXT_TO_SAY_BUFFER_LEN		40
	#define TEXT_TO_SCROLL_BUFFER_LEN	40
	#define HC06_DATA_BUFFER_LEN		10

	LedControl _ledDisplay = LedControl(MAX72XX_DIN, MAX72XX_CLK, MAX72XX_CS, 0);
	NewPing _sonar = NewPing(PIN_HCSR04_TRIGGER, PIN_HCSR04_ECHO, HCSR04_MAX_DISTANCE); // NewPing setup of pins and maximum distance.;

	Servo _servos[MAX_SERVOS];

	// update booleans
	boolean _isArmsSwing = false;
	boolean _isHeadSwing = false;
	boolean _isTextToScroll = false;
	boolean _isTextToSay = false;
	boolean _isMelodyToPlay = false;

	// screen variables
	uint8_t _ledDisplayImage = 0, _ledDisplayDigits = 0, _ledDisplayASCII = 0;

	uint8_t _ledDisplayType = 0;

	uint8_t _armSwingSpeed = 0, _headSwingSpeed = 0;

	uint8_t _textToScrollLen = 0;
	byte _textToScrollBuffer[TEXT_TO_SCROLL_BUFFER_LEN];

	// audio 
	boolean _isUserMelody = false;

	float _melodyToPlaySpeed = 1.0;
	uint8_t	_melodyToPlayLen = 0, _melodyRecordStart = 0;
	uint16_t _melodyToPlayNoteBuffer[MELODY_TO_PLAY_BUFFER_LEN];
	uint8_t _melodyToPlayDurationBuffer[MELODY_TO_PLAY_BUFFER_LEN];

	// update timings 
	unsigned long _scrollInterval = 200;
	unsigned long _armSwingInterval = 25;
	unsigned long _headSwingInterval = 50;

	// text variables
	uint8_t _textToSayLen = 0;
	byte _textToSayBuffer[TEXT_TO_SAY_BUFFER_LEN];

	// bluetooth buffers
	uint8_t _hc06DataBuffer[HC06_DATA_BUFFER_LEN];

	// function prototypes
	void _restoreLEDDisplay();
	void _servoStop(uint8_t servo);
	void _setVelocityLeftWheel(uint8_t velocity);
	void _setVelocityRightWheel(uint8_t velocity);
	void _setHead(uint8_t velocity);
	void _setLeftArm(uint8_t angle);
	void _setRightArm(uint8_t angle);
	void _setLEDDisplayImage(uint8_t image);
	void _setLEDDisplayDigits(uint8_t number);
	void _setLEDDisplayASCII(uint8_t ascii);
	void _setLEDisplay(const uint64_t character);
	void _setMelodytoPlay(uint8_t melody);
	void _updateTextToSay(void);
	void _updateMelodyToPlay(boolean isUserMelody);
	void _updateTextToScroll(boolean reset);
	void _updateHeadSwing(void);
	void _updateArmsSwing(void);
	uint32_t _readVcc(void);
	uint64_t _shiftScreenLeft(uint64_t screen);
	int8_t _boundWheelVelocity(int8_t velocity);
};

#endif