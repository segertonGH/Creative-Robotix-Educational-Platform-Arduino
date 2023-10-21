# Creative Robotix Educational Platform Arduino Library
An Arduino library for use with the Creative Robotix Educational Platform

Creative Robotix is a project by the Creative Science Foundation.  It is a fully customizable
robotics platform, with body parts that can be 3D printed and contstructed with low cost open hardware.

Creative-Robotix can be used by teachers, parents, children, adults, in groups or as individuals to address core STEAM (Science, Technology, Engineering, Arts & Maths) learning and making activities in a fun, hands-on, social and interactive way.  Our open-source platform can be used by anyone from 7 years up who are interested in learning more about technology. The tasks are carefully designed to fit the abilities of all ages, ranging from simple to more complex assembly, depending on your age, knowledge and guidance available.

[Our website](https://creative-science.org/partnerships/creative-robotix/) has more information about the project. 

## Download

## Install 
The library can be installed using the [standard Arduino library install procedure](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library)

This library has two library dependencies [LEDControl](https://www.arduino.cc/reference/en/libraries/ledcontrol/) and [NewPing](https://www.arduino.cc/reference/en/libraries/newping/).  Accept their installation when asked by the Arduino IDE.  The Creative Robotix library makes use the arduino tone function which creates a timmer conflict with the NewPing library.  To resolve this conflict, open NewPing.h and change all instances of " TIMER_ENABLED true" to " TIMER_ENABLED false" before saving.  The NewPing.h file can be found in the [arduino library folder](https://docs.arduino.cc/hacking/software/Libraries).

## Documentation


### Working with the examples

Libary examples can be found from the Arduino IDE File -> Examples -> CreativeRobotix.  To compile the library examples for the Arduino Creative Robotix platform select Tools -> Board -> Arduino AVR Boards -> Arduino Nano.  The Arduino Nano has two bootloder varients these can be found from Tools -> Processor.  Select the "ATmega 328P(old Booloader).  If the upload is not successful, then try the "ATmega 328P" processor.  If neither processors are successful then check the Bluetooth Enable jummper and ensure that it it removed.  If the jumper is removed, then check that the NewPing.h file has been successfully updated.

### Constructor

**CreativeRobotix codee**

Initilises the Creative Robotix platform and configures the boards pins.

### Methods

* **begin()** - Initilises display and says "Hello World!"

* **update()** - This method is called to update the robots built in behaviours, swing arms, looks around, scroll text and audio.

#### <ins>Servos</ins>
* **headAngle(int8_t angle, boolean state)** - Set head angle, 0 centre, positive values right, negative values left.  State **true** to action the request and keep servo active.  State **false** to deactivate servo, angle has no effect. 

* **armLeft(int8_t angle, boolean state)** - Set arm angle, 0 centre, positive values up above centre, negative value down below centre.  State **true** to action the request and keep servo active.  State **false** to deactivate servo, angle has no effect. 

* **armRight(int8_t angle, boolean state)** - Same as **armLeft**

* **wheelLeft(int8_t velocity)** - Positive values turn the wheel forward, negative values turn the wheen backward.  0 stops the wheel.

* **wheelRight(int8_t velocity)** - Same as **wheelLeft**.

* **hasStopped()** - Returns **true** if both wheels have stopped, **false** otherwise.
	
#### <ins>Behaviours</ins>
* **lookAround(uint8_t speed, boolean state)** - this is a placeholder.

* **swingArms(uint8_t speed, boolean state)** - this is a placeholder.

#### <ins>Display</ins>
* **displayScrollText(String text)** - this is a placeholder.

* **displayImage(uint8_t image)** - this is a placeholder.

* **displayDigits(uint8_t number)** - this is a placeholder.

* **displayASCII(uint8_t ascii)** - this is a placeholder.

* **displayCustom(uint64_t screen)** - this is a placeholder.

* **displayClear()** - this is a placeholder.

* **displayReset()** - this is a placeholder.

* **displayPixel(uint8_t row, uint8_t column, boolean state)** - this is a placeholder.

* **hasTextToScroll()** - this is a placeholder.

#### <ins>Audio 'speech'</ins>
* **sayDirect(String text)** - this is a placeholder.

* **say(String text)** - this is a placeholder.

* **hasTextToSay()** - this is a placeholder.

#### <ins>Audio melodies and tunes</ins>
* **playMelody(uint8_t melody)** - this is a placeholder.

* **playCustom(uint16_t notes[], uint8_t rduration[], uint8_t notesToPlay)** - this is a placeholder.

* **playTone(uint16_t frequency, uint16_t duration)** - this is a placeholder.

* **setMelodySpeed(uint8_t tempo)** - this is a placeholder.

* **hasMelodytoPlay()** - this is a placeholder.

#### <ins>Ultrasound</ins>
* **readUltrasound(void)** - this is a placeholder.

* **readUltrasoundMedian(uint8_t window)** - this is a placeholder.

#### <ins>Line sensors</ins>
* **readLineSensors()** - this is a placeholder.

* **readLine()** - this is a placeholder.

#### <ins>User Analoge Inputs</ins>
* **readAuxInputs()** - this is a placeholder.

#### <ins>Battery</ins>
* **readBatteryVoltage()** - this is a placeholder.

#### <ins>Bluetooth</ins>
* **btConfigure(String myRobotName, uint16_t myRobotPin)** - this is a placeholder.

* **btSetName(String myRobotName)** - this is a placeholder.

* **btSetPin(uint16_t myRobotPin)** - this is a placeholder.

### <ins>Variables</ins>
* **linePosition** - this is a placeholder.

* **lineState** - this is a placeholder.

* **auxInputs[]** - this is a placeholder.

### <ins>Constants</ins>

Dipslay constants refernces the number of LED in the display height and width

* **DISPLAY_HEIGHT**, **DISPLAY_WIDTH**

Built in images for use with the **diaplayImage** method

* **DISPLAY_SMILE**, **DISPLAY_NEUTRAL**, **DISPLAY_FROWN**, **DISPLAY_QUESTION**, **DISPLAY_OK**, **DISPLAY_TICK**, **DISPLAY_CROSS**, **DISPLAY_ROCK**, **DISPLAY_PAPER**, **DISPLAY_SISSORS**, **DISPLAY_QUAVER**, **DISPLAY_QUAVERx2**, **DISPLAY_HEART**, **DISPLAY_BLANK**

Built in Melodies for use with the **playMelody** method 

* **MELODY_GREENSLEEVES**, **MELODY_LITTLELAMB**, **MELODY_HAPPYBIRTHDAY**, **MELODY_STARWARS**, **MELODY_CHARIOTS**

Note definitions for use with **playTone** and **playMelody** methods.  Eight octaves.

**NOTE_RST**

**NOTE_B0**

**NOTE_C1**, **NOTE_CS1**, **NOTE_D1**, **NOTE_DS1**, **NOTE_E1**. **NOTE_F1**, **NOTE_FS1**, **NOTE_G1**, **NOTE_GS1**, **NOTE_A1**, **NOTE_AS1**, **NOTE_B1**

**NOTE_C2**, **NOTE_CS2**, **NOTE_D2**, **NOTE_DS2**, **NOTE_E2**, **NOTE_F2**, **NOTE_FS2**, **NOTE_G2**, **NOTE_GS2**, **NOTE_A2**, **NOTE_AS2**, **NOTE_B2**

**NOTE_C3**, **NOTE_CS3**, **NOTE_D3**, **NOTE_DS3**, **NOTE_E3**, **NOTE_F3**, **NOTE_FS3**, **NOTE_G3**, **NOTE_GS3**, **NOTE_A3**, **NOTE_AS3**, **NOTE_B3**

**NOTE_C4**, **NOTE_CS4**, **NOTE_D4**, **NOTE_DS4**, **NOTE_E4**, **NOTE_F4**, **NOTE_FS4**, **NOTE_G4**, **NOTE_GS4**, **NOTE_A4**, **NOTE_AS4**, **NOTE_B4**

**NOTE_C5**, **NOTE_CS5**, **NOTE_D5**, **NOTE_DS5**, **NOTE_E5**, **NOTE_F5**, **NOTE_FS5**, **NOTE_G5**, **NOTE_GS5**, **NOTE_A5**, **NOTE_AS5**, **NOTE_B5**

**NOTE_C6**, **NOTE_CS6**, **NOTE_D6**, **NOTE_DS6**, **NOTE_E6**, **NOTE_F6**, **NOTE_FS6**, **NOTE_G6**, **NOTE_GS6**, **NOTE_A6**, **NOTE_AS6**, **NOTE_B6**

**NOTE_C7**, **NOTE_CS7**, **NOTE_D7**, **NOTE_DS7**, **NOTE_E7**, **NOTE_F7**, **NOTE_FS7**, **NOTE_G7**, **NOTE_GS7**, **NOTE_A7**, **NOTE_AS7**, **NOTE_B7**

**NOTE_C8**, **NOTE_CS8**, **NOTE_D8**, **NOTE_DS8**, **NOTE_E8**, **NOTE_F8**, **NOTE_FS8**, **NOTE_G8**, **NOTE_GS8**, **NOTE_A8**, **NOTE_AS8**, **NOTE_B8**
