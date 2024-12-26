#pragma once

#include "common.hpp"

#define SIREN_PIN     10

namespace siren {
  bool isPlaying = false;

  void begin() {
    pinMode(SIREN_PIN, OUTPUT);
    digitalWrite(SIREN_PIN, LOW);
  }

  void play() {
    if (isPlaying) {
      return;
    }

    digitalWrite(SIREN_PIN, HIGH);
    isPlaying = true;
  }

  void stop() {
    if (!isPlaying) {
      return;
    }
    digitalWrite(SIREN_PIN, LOW);
    isPlaying = false;
  }
  
  void playUnlockAlarm() {
    stop();
    for (int i = 0; i < 5; i++) {
      play();
      delay(70);
      stop();
      delay(100);
    }
  }

  void playLock() {
    play();
    delay(100);
    stop();
  }

  void playUnlock() {
    play();
    delay(70);
    stop();
    delay(100);
    play();
    delay(70);
    stop();
  }
}

