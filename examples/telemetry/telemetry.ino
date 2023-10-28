/*
 Creative Robotix: telemetry

 This example demostrates the use of Codees Bluetooth module to tarnsmit sensor
 data back to the the connected host computer.  The data can be printed from
 the Arduino serial port terminal, graphed, dashbored, or used to inform Codee
 what to do by sending messages back to Codee via Bluetooth.  See bluetooth-server
 example.

 1. ensure the Bluetooth module has been configured, see the setup example
 2. ensure the Bluetooth Receive Enable jumper is removed
 3. upload this example via USB cable
 4. remove USB cable
 5. install batteries, connect to Codee via Bluetooth
 6. if needed, add new bluetooth device, looking for your robots name (if different from the default 'codee')
 7. open the arduino serial port at the correct serial port number 

 Note: this example only transmits data over serial, and so the Bluetooth Receive jumper 
 is not required.  If you wish to send data back to Codee from your computer, then the 
 Bluetooth Receive jumper needs to be set.  However, when the Bluetooth jumper is set, you 
 will not be able to upload new examples via the USB cable, and you will need to remove 
 the jumper again to do so.

 Created 23 October 2023
 by Simon Egerton

 Creative Robotix

 http://creativerobotix.com.au

 Creative Science Foundation

 http://creative-science.org/

 http://creative-science.org/partnerships/creative-robotix/

 */

#include "CreativeRobotix.h"

 // set up a new robot instance called codee
CreativeRobotix codee;

// the setup function runs once when you press reset or power the board
void setup() {
	// initilaise codee 
	codee.begin();

	// initialise serial 
	Serial.begin(57600);

}

// the loop function runs over and over again until power down or reset
void loop() {
	uint8_t ultrasound, battery;
	String data = "";

	// read ultrasound distance
	ultrasound = codee.readUltrasoundMedian(3);

	// readLine and updated class vairable linePosition
	codee.readLine();

	// read user auxillary inputs
	codee.readAuxInputs();

	// read battery voltage
	battery = codee.readBatteryVoltage();

	// construct data string to print
	data = data + "Battery = " + String(battery / 10) + "V "; // battery data
	data = data + "Ultrasound = " + String(ultrasound) + "CM ";  // ultrasound
	data = data + "AUX 1 = " + String(codee.auxInputs[0]) + " ";  // user inputs
	data = data + "AUX 2 = " + String(codee.auxInputs[1]) + " ";
	data = data + "Line position = " + String(codee.linePosition) + " "; // lineposition
	data = data + "Line state = " + String(codee.lineState) + " "; // linestate
	data = data + "Line sensors S1 - S5  = [ "; // line sensors 
	for (uint8_t sensor = 0; sensor < LINE_SENSORS; sensor++) { // line sensors
		if (codee.lineSensors[sensor] == 0) {
			data = data + "0, ";
		}
		else
		{
			data = data + "1, ";
		}
	}
	data = data + "]";

	// print data to serial
	Serial.println(data);

	// 0.5 second timming delay
	delay(500);
}
