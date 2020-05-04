#SN74HC165  Library

## Arduino Code

There are a few simple rules for using that library. Please read the following summary and apply it to your project

### Basic Elements

Required header files (#include ...) and Setup side code.

```cpp
#include <SN74HC165.h>
void setup(){

}
```

### Object Declaration

The object declaration method. It is used outside the setup statement, and a name such as io can be changed to any other name you want.

```cpp
#include <SN74HC165.h>

SN74HC165 io(1,4,3,2);
```

### initialization
No initilization required, by default as soon as an object is declared with valid Pins you are ready to go.

```cpp
#include <SN74HC165.h>

SN74HC165 io(1,4,3,2);
void setup(){
}
```

 detailed settings, you can use it as follows.

```cpp
#include <SN74HC165.h>

SN74HC165 io(1,4,3,2);
//SN74HC165 io(number of Registers, dataPin, clock, latch); 
void setup(){
}
```

The values used for, can take the following values:

```
On any DIgitalPins,
number of Regiaters : max uint8_t , number of chips in chain.
dataPin : (uint8_t) must be non inverted version of last bit (Qn) in the chain.
clock :(uint8_t) combined clock of all registers in chain.
latch pin :(uint8_t) combined load pin of registers in chain.

```

### Read values

How to read the Register value is as follows.

```cpp
void loop(){
Serial.println(io.readAll(),BIN);
// by default it returns uint8_t , i.e, last  register value in chain.
//its purpouse was when used for single register, it ment read all pins :P
}
```

and we can get individual pins too.

```cpp
void loop(){
//pin number should not exceed (8 * number of registers);
//MSB- H=D8 G=D7 F=D6 E=D5 D=D4 C=D3 B=D2 A=D1 -LSB
Serial.println(io.readPin(4));
}
```

also can get register wise values if you want

```cpp
void loop(){
//readAll(uint8_t chipNumber); to read one register at a time.starting from 0.it latches for every call
//Serial.println(io.readAll(0),BIN);
}
```
to read previously latched values

```cpp
void loop(){
//to read registers without latching (previously latched values).
//calling this function for the frist time returns all zeros.
Serial.println(io.lastUpdateRead(0),BIN);
}
```

## Basic example

It can be seen as a collection of the contents mentioned above.

```cpp
#include<SN74HC165.h>

//create an class object io.
SN74HC165 io(1,4,3,2); // SN74HC165 io(number of registers ,data_in,clock,latch);
//data_in is non-inverted version of Qn

void setup() {
Serial.begin(115200);
}

void loop() {
	
// reading all the input pins : readAll() --> returns 8-bit of last register in chain
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
```
