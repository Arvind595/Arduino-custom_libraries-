#SN74HC595 Library

## Arduino Code

There are a few simple rules for using that library. Please read the following summary and apply it to your project

### Basic Elements

Required header files (#include ...) and Setup side code.

```cpp
#include <SN74HC595.h>

void setup(){
 
}

void loop(){

}
```

### Object Declaration

The object declaration method. It is used outside the setup statement, and a name such as sr can be changed to any other name you want.

```cpp
#include <SN74HC595.h>

SN74HC595 sr(2, 5, 6, 3);
//for brightness control
//SN74HC595 sr(2, 5, 6, 3, 9);
```

### initialization

If you want more detailed settings, you can use it as follows.

```cpp
#include <SN74HC595.h>
SN74HC595 sr(2, 5, 6, 3, 9);
```

The values used for object deceleration can take the following values:

``` uint8_t registers;        //number of refisters
    uint8_t dataPin;   
    uint8_t latchPin;	        //combined latch pin
    uint8_t clockPin;	        //combined clock pin
    uint8_t outputEnablePin; // output enable must be PWM pin
```

### Set values

How to use the functions is as follows.

```cpp
void loop(){
  //enable output if brightness control is used.
  sr.enableOutput();
  //to set all the registers output low
  sr.setAllLow();
  delay(1000);
  //to set all the registers output high
  sr.setAllHigh();
  delay(1000);
}
```

and we can set individual pins too.

```cpp
void loop(){
sr.enableOutput();
  //to set individual pins of all registers
  //starting from pin 1
  for (int i = 1; i <= 16; i++) {
    sr.setPin(i, LOW);
    delay(100);
  }
  for (int i = 1; i <= 16; i++) {
    sr.setPin(i, HIGH);
    delay(100);
  }
  }
```

also adjust the brightness you want

```cpp
void loop(){  
//to set brightness of all registers outputs (8-bit)(0-255).
  for (int i = 255; i >= 0; i--) {
    delay(10);
    sr.setBrightness(i);
  }

  for (int i = 0; i < 255; i++) {
    delay(10);
    sr.setBrightness(i);
  }

  sr.setBrightness(255);
}
```

get the status of outputs as well

```cpp
void loop(){
  //to get status of outputs of registers.
  //sr.getAll(register number (starting from 0)); returns unsigned 8-bit value

  //reading status of register 0.
  Serial.print("status register 0 : ");
  Serial.println(sr.getAll(0), HEX);
  //reading status of register 1.
  Serial.print("status register 1 : ");
  Serial.println(sr.getAll(1), HEX);

  //reading individual status of pins.
  //sr.getPin(pin number(starting from 1).
  Serial.print("status of pin 8 : ");
  Serial.println(sr.getPin(8));
}
```

## Basic example

It can be seen as a collection of the contents mentioned above.

```cpp

#include "SN74HC595.h"
SN74HC595 sr(2, 5, 6, 3, 9);

void setup() {
Serial.begin(9600);
}

void loop() {
 //to set values register wise.
  //sr.set(register number(starting from 0), value(unsigned 8-bit));
  //to set 0xA5 at register 0 (Last most of the chain).
  sr.set(0, 0b10100101);
  delay(1000);

  //to set 0xB5 at register 1.
  sr.set(1, 0b10110101);
  
  Serial.print("status register 0 : ");
  Serial.println(sr.getAll(0), HEX);
  
  delay(1000);
}

```
