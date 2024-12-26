#pragma once

#include <GyverPower.h>

#include "common.hpp"
#include "utils.hpp"
#include "alarm.hpp"
#include "accel.hpp"
#include "interrupts.hpp"


// void handleGSMInterrupt() {
//   if (!interrupts::isGSMInterrupted()) {
//     return;
//   }
// }

void handleRadioOpenBtnInterrupt() {
  if (!interrupts::isRadioOpenBtnInterrupted()) {
    return;
  }
  PRINTLN("Open button pressed", 30);
  alarm::unlock();
}

void handleRadioCloseBtnInterrupt() {
  if (!interrupts::isRadioCloseBtnInterrupted()) {
    return;
  }
  PRINTLN("Close button pressed", 30);
  alarm::lock();
}

void handleAccelInterrupt() {
  if (!interrupts::isAccelInterrupted()) {
    return;
  }

  byte source = accel::instance.readAndClearInterrupts();
  if (accel::instance.checkInterrupt(source, ADXL345_ACTIVITY)) {
    PRINTLN("Accel interrupted!", 20);
    alarm::enableAlarm();
  }

  accel::instance.readAndClearInterrupts();
}

void handleMicroswitchInterrupt() {
  if (!interrupts::isMicroswitchInterrupted()) {
    return;
  } 

  alarm::enableAlarm();
  PRINTLN("Microswitch interrupted", 30);
}

void handlePowerdownInterrupt() {
  if (!interrupts::isPowerdownInterrupted()) {
    return;
  }

  alarm::enableAlarm();
  PRINTLN("Powerdown interrupted", 30);
}

void handleUnlockTimeout() {
  if (rtc::getTimestamp() > (settings::instance.unlockedAt + settings::instance.unlockTimeout)) {
    alarm::lock();
  }
}

void setup() {
  delay(2000);
  common::begin();
  settings::begin();
  rtc::begin();
  siren::begin();
  accel::begin();
  interrupts::begin();
}

void loop() {
  PRINTLN("LOOP", 20);

  // handleGSMInterrupt();
  handleRadioOpenBtnInterrupt();
  handleRadioCloseBtnInterrupt();

  if (!settings::instance.isAlarm) {
    handleAccelInterrupt();
    handleMicroswitchInterrupt();
    handlePowerdownInterrupt();
  }

  if (!settings::instance.isLocked) {
    handleUnlockTimeout();
    power.sleep(SLEEP_2048MS);
    return;
  } 

  power.sleep(SLEEP_FOREVER);
}