#pragma once

#include <time.h>
#include <ADXL345_WE.h>
#include "fram.hpp"

namespace settings {
struct Settings {
public:
  Settings() {
    ////////////////////////////// ADJUST ME!!! //////////////////////////////
    String("q1w2e3r4")      .toCharArray(masterString, sizeof(masterString));
    String("+7XXXXXXXXXX")  .toCharArray(alarmSystemPhoneNum, sizeof(alarmSystemPhoneNum));
    String("+7XXXXXXXXXX")  .toCharArray(ownerPhoneNum, sizeof(ownerPhoneNum));
    unlockTimeout =         60;      // Seconds
    //////////////////////////////////////////////////////////////////////////
    
    isLocked =              false;
    unlockedAt =            0;
    isAlarm =               false;

    activityThresold =      1.5; // G 
    inactivityThresold =    1.8; // G
    dataRange =             adxl345_range::ADXL345_RANGE_4G;
    dataRate =              adxl345_dataRate::ADXL345_DATA_RATE_12_5;

    onStartUpNotify =       true;
    onAlarmSMSNotify =      true;
    onAlarmCallNotify =     true;
    onLowVoltageNotify =    true;
  }

public:
  // Common
  char        masterString[9]; 
  char        alarmSystemPhoneNum[32];
  char        ownerPhoneNum[32];
  time_t      unlockTimeout;
  // Lockstate
  bool        isLocked;
  time_t      unlockedAt;
  bool        isAlarm;
  // Accelerometer
  float       activityThresold;
  float       inactivityThresold;
  int         dataRange;
  int         dataRate;
  // Notifications
  bool        onStartUpNotify;
  bool        onAlarmSMSNotify;
  bool        onAlarmCallNotify;
  bool        onLowVoltageNotify;
};

Settings instance;

void sync() {
  fram::write<Settings>(fram::ADDRESS::SETTINGS, &instance);
}

void begin() {
  Settings ethalon = Settings();
  fram::read<Settings>(fram::ADDRESS::SETTINGS, &instance);

  if (String(ethalon.masterString) != String(instance.masterString)) {
    instance = ethalon;
    sync();
  }
}
}