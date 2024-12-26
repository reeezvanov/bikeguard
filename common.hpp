#pragma once

#include <Wire.h>
#include <GyverPower.h>

namespace common {
   void begin() {
    power.setSystemPrescaler(PRESCALER_2);
    power.setSleepMode(POWERDOWN_SLEEP);

    Serial.begin(9600); 
    delay(100);

    Wire.begin(); 
    delay(100);
  }
}