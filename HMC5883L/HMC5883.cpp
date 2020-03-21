#include "HMC5883.h"

#include <Wire.h>

void HMC5883::setAddress(uint8_t addr){
  address = addr;
}

void HMC5883::WriteReg(byte Reg,byte val){
  Wire.beginTransmission(address); //start talking
  Wire.write(Reg); // Tell the HMC5883 to Continuously Measure
  Wire.write(val); // Set the Register
  Wire.endTransmission();
}

void HMC5883::init(){
  WriteReg(0x0B,0x01);
  //Define Set/Reset period
  setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_512);
  /*
  Define
  OSR = 512
  Full Scale Range = 8G(Gauss)
  ODR = 200HZ
  set continuous measurement mode
  */
}

void HMC5883::setMode(uint16_t mode,uint16_t odr,uint16_t rng,uint16_t osr){
  WriteReg(0x09,mode|odr|rng|osr);
}


void HMC5883::softReset(){
  WriteReg(0x0A,0x80);
}

void HMC5883::read(uint16_t* x,uint16_t* y,uint16_t* z){
  Wire.beginTransmission(address);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(address, 6);// DATA OF EACH AXIX IS 16 BIT 2S COMP HENCE MSB IS SHIFTED WITH EIGHT ZEROS AND ORED WITH LSB BYTE
  *x = Wire.read(); //LSB  x
  *x |= Wire.read() << 8; //MSB  x
  *y = Wire.read(); //LSB  z
  *y |= Wire.read() << 8; //MSB z
  *z = Wire.read(); //LSB y
  *z |= Wire.read() << 8; //MSB y
}

void HMC5883::read(uint16_t* x,uint16_t* y,uint16_t* z,int* a){
  read(x,y,z);
  *a = azimuth(y,x);
}

void HMC5883::read(uint16_t* x,uint16_t* y,uint16_t* z,float* a){
  read(x,y,z);
  *a = azimuth(y,x);
}


float HMC5883::azimuth(uint16_t *a, uint16_t *b){
  float azimuth = atan2((int)*a,(int)*b) * 180.0/PI;
  return azimuth < 0?360 + azimuth:azimuth;
}
