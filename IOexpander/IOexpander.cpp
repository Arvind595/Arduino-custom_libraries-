/**
 * \file IOexpander.cpp
 * \brief Implementation of a class for dealing with the 74_165 chip.
 * \date 19 april 2020
 * \version 1.0
 * \author=Aravind Anirudh
 */

#include <IOexpander.h>

IOexpander::IOexpander(const uint8_t registers,const uint8_t serialDataPin,const uint8_t clockPin,const uint8_t latchPin)
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

}

void IOexpander::snapshot(){
   digitalWrite(_clockPin,LOW);
   digitalWrite(_latchPin,LOW);
   delay(1);
   digitalWrite(_latchPin,HIGH);
}

void IOexpander::pulseClock(){
	digitalWrite(_clockPin,LOW);
    delay(1);
    digitalWrite(_clockPin,HIGH);
    delay(1);
}

uint16_t IOexpander::readAll(){
	uint16_t binary=0;
	snapshot();
    
   for(uint8_t i =0; i<(_registers*8); i++){
	bool pinstate=digitalRead(_serialDataPin);
    pulseClock();
    binary=(binary<<1) | pinstate;
   }
	
	return binary;
}

bool IOexpander::readPin(const uint8_t pin){
	if(pin<=(_registers*8)){
	snapshot();
	uint8_t i;
	for(i=8;i!=pin;i--){
	pulseClock();
	}
	if(i==pin){
		return digitalRead(_serialDataPin);
	}
	}
	else return 0;
}	
	