/*
 * For Arduino UNO / other board may have different SPI pins
 * 
 * PIN CONNECTIONS : 
 * 
 * pin 09 > LDAC (User LDAC pin)
 * pin 10 > CS   (User SS pin)
 * pin 11 > SDI  (SPI MOSI pin)
 * pin 12 > NC   (SPI MISO pin) 
 * pin 13 > SCK  (SPI SCK pin)
 * 
 * SHDN, VCC, VREFA, VREFB > +5v
 * VSS > GND
 */

#include <MCP49x2.h>

int val = 1024;
MCP4922 myDAC(10,9);

void setup() {
  // Uncomment line above to run in openLatch mode
  Serial.begin(9600);
  //myDAC.openLatch();
  }

void loop() {
  myDAC.DACA(val);    // set DACA register

  // Comment the line above if you run in openLatch mode
  myDAC.trigger();    // trigger DAC Vout
  
  //val = val++ % 4096; // increment value
  delay(100);
  }
