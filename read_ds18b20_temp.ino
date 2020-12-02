//////////////////////////////////////////////////////////////////////////////////////////
//
// Author: Aaron Pritchard
// Filename: read_ds18b20_temp.ino
// Class: CSC354-030
// Prof: Dr. Hussain
// Date: 30 November 2020
// Major: CS 
// Desc: DS18B20 temperature sensor implementation to connect to SEEEDUINO XIAO on pin 6.
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <OneWire.h>
int inPin=6; // define D10 as input pin connecting to DS18S20 S pin
OneWire ds(inPin); 
 
void setup(void) {
  Serial.begin(9600);
}
 
void loop(void) {
  int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
 
  if ( !ds.search(addr)) {
      ds.reset_search();
      return;
  }
 
 
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); 
 
  delay(1000);  
 
 
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);  
 
 
 
  for ( i = 0; i < 9; i++) { 
    data[i] = ds.read();
  }
  Serial.print("Temperature: ");
  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  
  if (SignBit)
  {
    TReading = (TReading ^ 0xffff) + 1;
  }
  Tc_100 = (6 * TReading) + TReading / 4; 
  Whole = Tc_100 / 100; 
  Fract = Tc_100 % 100;
  if (SignBit)
  {
     Serial.print("-");
  }
  Serial.print((Whole *9/5) + 32);
  Serial.print(".");
  if (Fract < 10)
  {
     Serial.print("0");
  }

  Serial.print((Fract *9/5) + 32);
  Serial.print(" F\n");
}
