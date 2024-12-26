#pragma once

#include <PinChangeInterrupt.h>

#include "utils.hpp"

#define ACCEL_INT_PIN               2
#define GSM_INT_PIN                 3
#define RADIO_OPEN_BTN_INT_PIN      4
#define RADIO_CLOSE_BTN_INT_PIN     5
#define MICROSWITCH_INT_PIN         6
#define POWERDOWN_INT_PIN           7


namespace interrupts {
  volatile bool __isAccelInterrupted            = false;
  volatile bool __isGSMInterrupted              = false;
  volatile bool __isRadioOpenBtnInterrupted     = false;
  volatile bool __isRadioCloseBtnInterrupted    = false;
  volatile bool __isMicroswitchInterrupted      = false;
  volatile bool __isPowerdownInterrupted        = false;

  //////////////////////////////////////////////////////////////////////////////////

  void accelISR() {
    __isAccelInterrupted = true;
  }

  void GSMISR() {
    __isGSMInterrupted = true;
  }

  void radioOpenBtnISR() {
    __isRadioOpenBtnInterrupted = true;
  }

  void radioCloseBtnISR() {
    __isRadioCloseBtnInterrupted = true;
  }

  void microswitchISR() {
    __isMicroswitchInterrupted = true;
  }

  void powerdownISR() {
    __isPowerdownInterrupted = true;
  }

  //////////////////////////////////////////////////////////////////////////////////

  bool isAccelInterrupted() {
    bool result = __isAccelInterrupted;
    if (result) {
      __isAccelInterrupted = false;
    }
    return result;
  }

  bool isGSMInterrupted() {
    bool result = __isGSMInterrupted;
    if (result) {
      __isGSMInterrupted = false;
    }
    return result;
  }

  bool isRadioOpenBtnInterrupted() {
    bool result = __isRadioOpenBtnInterrupted;
    if (result) {
      __isRadioOpenBtnInterrupted = false;
    }
    return result;
  }

  bool isRadioCloseBtnInterrupted() {
    bool result = __isRadioCloseBtnInterrupted;
    if (result) {
      __isRadioCloseBtnInterrupted = false;
    }
    return result;
  }

  bool isMicroswitchInterrupted() {
    bool result = __isMicroswitchInterrupted;
    if (result) {
      __isMicroswitchInterrupted = false;
    }
    return result;
  }

  bool isPowerdownInterrupted() {
    bool result = __isPowerdownInterrupted;
    if (result) {
      __isPowerdownInterrupted = false;
    }
    return result;
  }

  void begin() {
    pinMode(ACCEL_INT_PIN, INPUT);
    pinMode(GSM_INT_PIN, INPUT);
    pinMode(RADIO_OPEN_BTN_INT_PIN, INPUT);
    pinMode(RADIO_CLOSE_BTN_INT_PIN, INPUT);
    pinMode(MICROSWITCH_INT_PIN, INPUT);
    pinMode(POWERDOWN_INT_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(ACCEL_INT_PIN), accelISR, RISING);
    attachInterrupt(digitalPinToInterrupt(GSM_INT_PIN), GSMISR, FALLING);

    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(RADIO_OPEN_BTN_INT_PIN), radioOpenBtnISR, FALLING);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(RADIO_CLOSE_BTN_INT_PIN), radioCloseBtnISR, FALLING);

    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(MICROSWITCH_INT_PIN), microswitchISR, FALLING);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(POWERDOWN_INT_PIN), powerdownISR, FALLING);
  }
}