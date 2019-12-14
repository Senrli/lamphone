

#include "ESPBluetooth.h"
#include "LightCtr.h"
#include "PhoneDetect.h"
#include "TouchRead.h"


void setup() {
  Serial.begin(115200);
  bluetoothInit();
  lightInit();
  phoneInit();
  touchInit();
}

void loop() {
  bluetoothRead();
  phoneDetect();
  lightChg();
  lightAutoOff();
  touchAcq();
}
