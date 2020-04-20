//example for 74_165 (PISO) using IO_EXPANDER.

#include<IOexpander.h>

//create an class object io.
IOexpander io(1,4,3,2); // IOexpander io(number of registers ,data_in,clock,latch);
//data_in is non-inverted version of Qn

void setup() {
Serial.begin(115200);
}

void loop() {
	
// reading all the input pins : readAll();
Serial.println(io.readAll(),BIN);

// reading status of single pin : readPin(pin number);
//pin number should not exceed (8 * number of registers);
//MSB- H=D8 G=D7 F=D6 E=D5 D=D4 C=D3 B=D2 A=D1 -LSB
Serial.println(io.readPin(4));

delay(1000);

}