/*
 Name:		CRFirmata.h
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

#pragma once

// definitions for creative robotix educational platform

// creaive robotix SYSEX commands
#define CRE_ULTRASOUND		0x08
#define CRE_AUDIO			0x09
#define CRE_LED_DISPLAY		0x0A
#define CRE_SWING_ARMS		0x0B
#define CRE_LOOK_AROUND		0x0C
#define CRE_HCO6_CMD		0x0D
#define CRE_SERVO			0x0E

// Creative robotix SYSEX sub commands
#define AUDIO_SAY			0
#define AUDIO_MELODY_BLTIN	1
#define AUDIO_MELODY_USR	2
#define AUDIO_TONE			3
#define AUDIO_MELODY_SPEED	4

#define LED_SET_IMAGE		1
#define LED_SET_SCROLL_TEXT	2
#define LED_SET_NUMBER		3
#define LED_SET_ROW_DATA	4
#define LED_SET_SET_PIXEL	5
#define LED_SET_CLEAR		6
#define LED_SET_ASCII		7
#define LED_RST_SCROLL_TEXT	8

#define HC06_CMD_SETNAME	1
#define HC06_CMD_SETPIN		2

#define SERVO_WHEEL_LEFT	0
#define SERVO_WHEEL_RIGHT	1
#define SERVO_WHEEL_STOP	2
#define SERVO_ARM_LEFT		3
#define SERVO_ARM_RIGHT		4
#define SERVO_HEAD			5


// creative robotix configuration
#define CRE_DEFAULT_CONFIGURATION_INPUTS 0x000C00 // each bit: 1 = pin in INPUT, 0 = anything else, configures pins 10 and 12 as digital inputs.

#define IS_PIN_DIGITAL_INPUT(p)        ((CRE_DEFAULT_CONFIGURATION_INPUTS >> p) & 0x01 )

// forward declarations for compiler
void CRFirmataInit(String myRobotsName, uint16_t myRobotsPin, void (*demo)());
void CRFirmataUpdate(void);