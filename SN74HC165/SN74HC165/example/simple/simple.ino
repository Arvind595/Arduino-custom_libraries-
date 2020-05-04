//example for 74_165 (PISO) using IO_EXPANDER.

#include<SN74HC165.h>

//create an class object io.
SN74HC165 io(1,4,3,2); // SN74HC165 io(number of registers ,data_in,clock,latch);
//data_in is non-inverted version of Qn

void setup() {
Serial.begin(115200);
}

void loop() {
	
// reading all the input pins : readAll() --> returns 16-bit of last two registers in chain
//readAll(uint8_t chipNumber); to read one register at a time.starting from 0.it latches for every call
//Serial.println(io.readAll(0),BIN);
Serial.println(io.readAll(),BIN);

//to read registers without latching (previously latched values).
//calling this function for the frist time returns all zeros.
Serial.println(io.lastUpdateRead(0),BIN);

// reading status of single pin : readPin(pin number);
//pin number should not exceed (8 * number of registers);
//MSB- H=D8 G=D7 F=D6 E=D5 D=D4 C=D3 B=D2 A=D1 -LSB
Serial.println(io.readPin(4));

delay(1000);

}