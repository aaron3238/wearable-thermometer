//////////////////////////////////////////////////////////////////////////////////////////
//
// Author: Aaron Pritchard
// Filename: MAX30205.ino
// Class: CSC354-030
// Prof: Dr. Hussain
// Date: 2 December 2020 
// Major: CS 
// Description: Makes use of the MAX30205 temperature sensor to display temps in f to serial.
//
/////////////////////////////////////////////////////////////////////////////////////////

/*

This program Print temperature on terminal

Hardware Connections (Breakoutboard to Arduino):
Vin  - 5V (3.3V is allowed)
GND - GND
SDA - A4 (or SDA)
SCL - A5 (or SCL)

*/

#include <Wire.h>
#include "Protocentral_MAX30205.h"
MAX30205 tempSensor;


const bool fahrenheittemp = true; // I'm showing the temperature in Fahrenheit, If you want to show the temperature in Celsius the make this variable false.

void setup() {

  Serial.begin(9600);
  Wire.begin();

  //scan for temperature in every 30 sec untill a sensor is found. Scan for both addresses 0x48 and 0x49
  while(!tempSensor.scanAvailableSensors()){
    Serial.println("Couldn't find the temperature sensor, please connect the sensor." );
    delay(30000);
  }

  tempSensor.begin();   // set continuos mode, active mode
}

void loop() {

	float temp = tempSensor.getTemperature(); // read temperature for every 100ms

  if(fahrenheittemp){
    temp = (temp * 1.8) + 37;
    Serial.print(temp,2);
    Serial.println("'F");
  }else{
    Serial.print(temp ,2);
    Serial.println("'c" );
  }
	delay(100); // slow it down a bit
}
