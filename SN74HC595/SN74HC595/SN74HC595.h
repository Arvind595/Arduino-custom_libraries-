 /**
 * \SN74HC595.h
 * \date 25 april 2020
 * \version 1.1
 * \author=Aravind Anirudh
 * \url=https://github.com/Arvind595/Arduino-custom_libraries-
 */
 
#ifndef SN74HC595_H
#define SN74HC595_H

#if defined(__AVR__)
#include "Arduino.h"
#endif
#define MAX_CHIP_COUNT 255 // max size is 255 because of uint8_t data type used.
class SN74HC595 {
  public:
    SN74HC595(const uint8_t registers, const uint8_t dataPin, const uint8_t latchPin, const uint8_t clockPin);
    SN74HC595(const uint8_t registers, const uint8_t dataPin, const uint8_t latchPin, const uint8_t clockPin, const uint8_t outputEnablePin);
    void setAllHigh();
    void setAllLow();
    void setPin(uint8_t pin, bool voltage);
    void set(uint8_t chipNumber,uint8_t value);
    void disableOutput();
    void enableOutput();
    void setBrightness(uint8_t value);
    uint8_t getAll(uint8_t chip);
    bool getPin(const uint8_t pin);

  private:
    uint8_t getChipNumber(uint8_t pin);
    void updateRegister();
    uint8_t modifyBit(uint8_t number, uint8_t position, bool value);
    uint8_t _registers;
    uint8_t _dataPin;
    uint8_t _latchPin;
    uint8_t _clockPin;
    uint8_t _outputEnablePin;
    uint8_t _binary[MAX_CHIP_COUNT];

};
#endif
