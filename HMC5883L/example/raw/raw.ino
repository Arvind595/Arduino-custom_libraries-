#include <Wire.h>
#include <HMC5883.h>

HMC5883 hmc;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  hmc.init();
  //qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);
}

void loop() {
  int x,y,z;
  hmc.read(&x,&y,&z);

  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.print(z);
  Serial.println();
  delay(100);
}
