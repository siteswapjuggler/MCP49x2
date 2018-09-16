// MCP4902/4912/4922 library for Arduino
// initial release by Sylvain GARNAVAULT - 2016/06/30

#include "MCP49x2.h"

////////////////////////
//     INITIATION     //
////////////////////////

MCP49x2::MCP49x2() {
    MCP49x2(MCP_49x2_DFT_CS,MCP_49x2_DFT_LDAC,MCP_4922);
}

MCP49x2::MCP49x2(byte cs, byte ldac) {
    MCP49x2(cs,ldac,MCP_4922);
}

MCP49x2::MCP49x2(byte cs, byte ldac, byte chipset) {
    _cs = cs;                           // store the cs pin
    _ldac = ldac;                       // store the ldac pin
    _chipset = chipset;                 // store the chipset version
    pinMode(_cs,OUTPUT);                // set the cs pin as output
    pinMode(_ldac,OUTPUT);              // set the ldac pin as output
    digitalWrite(_cs,HIGH);             // set the cs pin to default HIGH state
    digitalWrite(_ldac,HIGH);           // set the ldac pin to default HIGH state
    SPI.begin();                        // init SPI communication
    }

/////////////////////////
//  PUBLIC  METHODS    //
/////////////////////////

void MCP49x2::trigger() {
    digitalWrite(_ldac,LOW);
    digitalWrite(_ldac,HIGH);
}

void MCP49x2::openLatch() {
    digitalWrite(_ldac,LOW);
}


void MCP49x2::DACA(int value) {
    analogWrite(0,value);               // set analog output
}

void MCP49x2::DACB(int value) {
    analogWrite(1,value);               // set analog output
}

void MCP49x2::analogWrite(byte dac, int value) {
    int config = SDN | GA;              // active output
    config |= ((dac != 0)*DAC);         // DAC selection
    writeCommandRegister(value,config); // write Command Register
}

void MCP49x2::writeCommandRegister(int value, int config) {
    value  = value << _chipset;         // offset for 4902 & 4912
    value  &= 0x0FFF;                   // value mask
    config &= 0xF000;                   // config mask
    _begin();                           // begin SPI transaction
	SPI.transfer((config|value) >> 8);  // send MSB byte
	SPI.transfer(value & 0xFF);         // send LSB byte
    _end();                             // end SPI transaction
	}

/////////////////////////
//  PRIVATE  METHODS   //
/////////////////////////

void MCP49x2::_begin() {
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));   // SPI configuration
    digitalWrite(_cs,LOW);                                              // select CHIP
}

void MCP49x2::_end() {
    digitalWrite(_cs,HIGH);                 // deselect CHIP
    SPI.endTransaction();                   // free SPI for other library
}
