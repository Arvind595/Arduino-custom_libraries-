/**
 * \file SN74HC165.cpp
 * \brief Implementation of a class for dealing with the 74_165 chip.
 * \date 19 april 2020
 * \version 1.0
 * \author=Aravind Anirudh
 */

#include <SN74HC165.h>

SN74HC165::SN74HC165(const uint8_t registers,const uint8_t serialDataPin,const uint8_t clockPin,const uint8_t latchPin)
{
    // set attributes
	_registers=registers;
    _clockPin = clockPin;
    _serialDataPin = serialDataPin;
    _latchPin = latchPin;

    // define pins
    pinMode(_clockPin, OUTPUT);
    pinMode(_serialDataPin, INPUT);
    pinMode(_latchPin, OUTPUT);

    // set pins
    digitalWrite(_clockPin, LOW);
    digitalWrite(_latchPin, HIGH);
	
	//initilise required locations to zero.
	for(uint8_t i=0; i<=_registers; i++){
		_binary[i]=0;
	}

}

void SN74HC165::snapshot(){
   digitalWrite(_clockPin,LOW);
   digitalWrite(_latchPin,LOW);
   delay(1);
   digitalWrite(_latchPin,HIGH);
}

void SN74HC165::pulseClock(){
	digitalWrite(_clockPin,LOW);
    delay(1);
    digitalWrite(_clockPin,HIGH);
    delay(1);
}

uint8_t SN74HC165::readAll(){
	uint8_t binary=0;
	snapshot();
    
   for(uint8_t i =0; i<(8); i++){
	bool pinstate=digitalRead(_serialDataPin);
    pulseClock();
    binary=(binary<<1) | pinstate;
   }
	
	return binary;
}
	
uint8_t SN74HC165::readAll(uint8_t chipNumber){
	//starts from 0th chip;
	for(uint8_t i=0; i<chipNumber;i++){
	_binary[i]=readAll();
	}
	
	return _binary[chipNumber];
}	
bool SN74HC165::readPin(const uint8_t pin){
	  uint8_t chipn = 0;
  for (unsigned int i = 8, j = 8; i <= 4080; i = i + 8, j = j + 7) {
    if (pin <= i) {
      chipn = i - j;
      break;
    }
  }
  return _binary[chipn]>>pin;
}
uint8_t SN74HC165::lastUpdateRead(uint8_t chipNumber){
	return _binary[chipNumber];
}
