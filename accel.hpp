#pragma once
#include <ADXL345_WE.h>

#include "utils.hpp"
#include "settings.hpp"

#define ACCEL_I2C_ADDR        0x53
#define ACCEL_CORR_FACTORS    -250.0, 284.0, -266.0, 269.0, -220.0, 296.0  // X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX

namespace accel {
 ADXL345_WE instance = ADXL345_WE(ACCEL_I2C_ADDR);

 void begin() {
  while (!instance.init()) {
    PRINTLN("Accelerometer not connected!", 1000);
  }

  instance.setCorrFactors(ACCEL_CORR_FACTORS);
  instance.setRange(settings::instance.dataRange);
  instance.setDataRate(settings::instance.dataRate); 

  instance.deleteInterrupt(ADXL345_ACTIVITY);
  instance.deleteInterrupt(ADXL345_INACTIVITY);
  
  instance.setActivityParameters(ADXL345_DC_MODE, ADXL345_XYZ, settings::instance.activityThresold);
  instance.setInactivityParameters(ADXL345_DC_MODE, ADXL345_XYZ, settings::instance.inactivityThresold, 3);
  
  instance.setInterrupt(ADXL345_ACTIVITY, INT_PIN_2);
  instance.setInterrupt(ADXL345_INACTIVITY, INT_PIN_2);
  
  instance.setLinkBit(true);
  instance.setSleep(false);
  instance.setAutoSleep(false);
}
}
