//example for 74_165 (PISO) using IO_EXPANDER.

#include<IOexpander.h>

//create an class object io.
IOexpander io(1,4,3,2); // IOexpander io(number of registers ,data_in,clock,latch);
void setup() {
Serial.begin(115200);
}

void loop() {
	
// reading all the input pins : readAll();
Serial.println(io.readAll(),BIN);

// reading status of single pin : readPin(pin number);
//the function returns zero if pin number exceeds 8 * number of registers
Serial.println(io.readPin(4));

delay(1000);

}