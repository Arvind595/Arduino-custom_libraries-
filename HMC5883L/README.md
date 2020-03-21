#HMC5883L Library
## Arduino Code

There are a few simple rules for using that library. Please read the following summary and apply it to your project

### Basic Elements

Required header files (#include ...) and Setup side code.

```cpp
#include <Wire.h>
#include <HMC5883.h>

void setup(){
  Wire.begin();
}
```

### Object Declaration

The object declaration method. It is used outside the setup statement, and a name such as hmc can be changed to any other name you want.

```cpp
#include <Wire.h>
#include <HMC5883.h>

HMC5883 hmc;
```

### initialization

HMC5883 Sensor's setting function.

The init function allows you to take advantage of the features of the HMC5883 sensor by default.

```cpp
void setup(){
    Wire.begin();
    hmc.init();
}
```

If you want more detailed settings, you can use it as follows.

```cpp
void setup(){
  Wire.begin();
  hmc.init();
  hmc.setMode(Mode_Standby,ODR_200Hz,RNG_8G,OSR_512);
}
```

The values ​​used for setMode can take the following values:

```
Mode : Mode_Standby / Mode_Continuous

ODR : ODR_10Hz / ODR_50Hz / ODR_100Hz / ODR_200Hz
ouput data update rate

RNG : RNG_2G / RNG_8G // G=gaussian 1G=100uT, (200,800)uT MAX
magneticfield measurement range
The magnitude of the Earth's magnetic field at its surface ranges from 25 to 65 microteslas (0.25 to 0.65 gauss).

OSR : OSR_512 / OSR_256 / OSR_128 / OSR_64
over sampling rate
```

### Read values

How to read the measured sensor value is as follows.

```cpp
void loop(){
  int x,y,z;

  hmc.read(&x,&y,&z);
}
```

and we can get azimuth too.

```cpp
void loop(){
  int x,y,z;
  int a;
  //float a; //can get float value

  hmc.read(&x,&y,&z,&a);
}
```

also can claculate azimuth you want

```cpp
void loop(){
  int x,y,z;
  int a;

  hmc.read(&x,&y,&z);
  a = hmc.azimuth(&y,&x);
}
```

## Basic example

It can be seen as a collection of the contents mentioned above.

```cpp
#include <Wire.h>
#include <HMC5883.h>

HMC5883 hmc;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  hmc.init();
  //hmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);
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
```
