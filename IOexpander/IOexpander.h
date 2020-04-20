/**
 * \IOexpander.h
 * \date 19 april 2020
 * \version 1.0
 * \author=Aravind Anirudh
 */

#ifndef IO_H
#define IO_H

#include <Arduino.h>

class IOexpander{
	public:
	
	IOexpander(const uint8_t registers,const uint8_t serialDataPin, const uint8_t clockPin,const uint8_t latchPin);
	
	uint16_t readAll();
	bool readPin(const uint8_t pin);
	
	private:
	
	void snapshot(); 	// latch into register
	void pulseClock();	// pulse the clock pin
	
	uint8_t _registers;
	uint8_t _serialDataPin;
	uint8_t _clockPin;
	uint8_t _latchPin;


};
#endif