/**
 * \SN74HC595.cpp
 * \date 25 april 2020
 * \version 1.1
 * \author=Aravind Anirudh
 * \url=https://github.com/Arvind595/Arduino-custom_libraries-
 */
 
#include "SN74HC595.h"

SN74HC595::SN74HC595(const uint8_t registers, const uint8_t dataPin, const uint8_t latchPin, const uint8_t clockPin) {
  _registers = registers;
  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;

  pinMode(_dataPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);

  digitalWrite(_latchPin, LOW);
  digitalWrite(_clockPin, LOW);

  for (uint8_t i = 0; i <= _registers; i++) {
    _binary[i] = 0;
  }

}
SN74HC595::SN74HC595(const uint8_t registers, const uint8_t dataPin, const uint8_t latchPin, const uint8_t clockPin, const uint8_t outputEnablePin) {
  _registers = registers;
  _dataPin = dataPin;
  _latchPin = latchPin;
  _clockPin = clockPin;
  _outputEnablePin = outputEnablePin;

  pinMode(_dataPin, OUTPUT);
  pinMode(_latchPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_outputEnablePin, OUTPUT);

  digitalWrite(_latchPin, LOW);
  digitalWrite(_clockPin, LOW);
  digitalWrite(_outputEnablePin, LOW);
}
void SN74HC595::disableOutput() {
  digitalWrite( _outputEnablePin, HIGH);
}

void SN74HC595::enableOutput() {
  digitalWrite( _outputEnablePin, LOW);
}

void SN74HC595::setBrightness(uint8_t value) {
  analogWrite( _outputEnablePin, 255 - value);
}
uint8_t SN74HC595::getChipNumber(uint8_t pin) {
  uint8_t chipn = 0;
  for (unsigned int i = 8, j = 8; i <= 4080; i = i + 8, j = j + 7) {
    if (pin <= i) {
      chipn = i - j;
      break;
    }
  }
  return chipn;
}
uint8_t SN74HC595::modifyBit(uint8_t number, uint8_t position, bool value) {
  // whole numbers 0 is position of lsb
  position = position - 1;
  uint8_t mask = 1 << position;
  return (number & ~mask) | ((value << position) & mask);
}
void SN74HC595::updateRegister() {
  for (int i = 0 ; i < _registers; i++) {
    shiftOut(_dataPin, _clockPin, LSBFIRST, _binary[i]);
  }
  digitalWrite(_latchPin, HIGH);
  digitalWrite(_latchPin, LOW);
}
void SN74HC595::setPin(uint8_t pin, bool voltage) {
  uint8_t chipn = getChipNumber(pin);
  _binary[chipn] = modifyBit(_binary[chipn], (pin - (8 * chipn )), voltage);
  updateRegister();
}
void SN74HC595::setAllLow() {
  for (uint8_t i = 0; i <= _registers; i++) {
    _binary[i] = 0;
  }
  updateRegister();
}
void SN74HC595::setAllHigh() {
  for (uint8_t i = 0; i <= _registers; i++) {
    _binary[i] = 255;
  }
  updateRegister();
}
void SN74HC595::set(uint8_t chipNumber,uint8_t value) {
_binary[chipNumber]=value;
updateRegister();
}
uint8_t SN74HC595::getAll(uint8_t chip) {
  return _binary[chip];
}
bool SN74HC595::getPin(const uint8_t pin) {
  return _binary[getChipNumber(pin)];
}
