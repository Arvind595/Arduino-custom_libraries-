/**
   \SN74HC595.h\ example-as a ton of outputs
   \date 25 april 2020
   \version 1.1
   \author=Aravind Anirudh
   \url=https://github.com/Arvind595/Arduino-custom_libraries-
*/
#include "SN74HC595.h"

// define an object of SN74HC595
SN74HC595 sr(2, 5, 6, 3, 9);
//for brightness control use outputenable pin (must be an PWM pin of microcontroller) in object.
//(const uint8_t registers, const uint8_t dataPin, const uint8_t latchPin, const uint8_t clockPin, const uint8_t outputEnablePin);
//or use this,
//(const uint8_t registers, const uint8_t dataPin, const uint8_t latchPin, const uint8_t clockPin,);

void setup() {
  Serial.begin(9600);
}
void loop() {
  //enable output if brightness control is used.
  sr.enableOutput();
  //to set all the registers output low
  sr.setAllLow();
  delay(1000);
  //to set all the registers output high
  sr.setAllHigh();
  delay(1000);

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
  //to disable output.
  sr.disableOutput();
  delay(1000);
  sr.enableOutput();
  delay(1000);

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
  sr.setAllLow();

  //to set values register wise.
  //sr.set(register number(starting from 0), value(unsigned 8-bit));
  //to set 0xA5 at register 0 (Last most of the chain).
  sr.set(0, 0b10100101);
  delay(1000);

  //to set 0xB5 at register 1.
  sr.set(1, 0b10110101);
  delay(1000);

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
  sr.setAllLow();
  
  //some animation.
  for(int i=0;i<10;i++){
    sr.set(0,0x55);
    sr.set(1,0x55);
    delay(200);
    sr.set(0,0xAA);
    sr.set(1,0xAA);
    delay(200);
  }
  delay(5000);
}
