#include <Wire.h>
#include <HMC5883.h>
//0.1uf vdd and vddio to gnds//2.2k pullups to 3.3v
HMC5883 hmc;
//0x0D address of ic
//0x3D read address
//0x3C write address
//12 bit adc 1-2 degree resloution
void setup() {
  Wire.begin();
  //200us iic startup
  //50 ms adc startup
  // 400khz iic
  //pin dsyc :Data Ready, Interrupt Pin.  Internally pulled high.  Optional connection.  Low for 250 µsec when data is placed in the data output registers
  Serial.begin(9600);
  hmc.init();
  //qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);
 /*
Mode : Mode_Standby / Mode_Continuous

ODR : ODR_10Hz / ODR_50Hz / ODR_100Hz / ODR_200Hz
ouput data update rate
//75-160hz
RNG : RNG_2G / RNG_8G // G=gaussian 1G=100uT, (200,800)uT MAX
magneticfield measurement range -+8 gauss and 2mill gauss sens
The magnitude of the Earth's magnetic field at its surface ranges from 25 to 65 microteslas (0.25 to 0.65 gauss).

OSR : OSR_512 / OSR_256 / OSR_128 / OSR_64
over sampling rate
*/

}

void loop() {
  int x, y, z;
 //int azimuth //int also works
  float azimuth; 
  hmc.read(&x, &y, &z,&azimuth);
  //azimuth = qmc.azimuth(&y,&x);//you can get custom azimuth
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.print(z);
  Serial.print(" a: ");
  Serial.print(azimuth);
  Serial.println();
  delay(100);
}
