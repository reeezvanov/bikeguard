#pragma once

#include "settings.hpp"
#include "rtc.hpp"
#include "siren.hpp"


namespace alarm {
  void disableAlarm() {
    settings::instance.isAlarm = false;
    settings::sync();
    siren::stop();
  }

  void unlock() {
    settings::instance.isLocked = false;
    settings::instance.unlockedAt = rtc::getTimestamp();

    if (settings::instance.isAlarm) {
      disableAlarm();
      siren::playUnlockAlarm();
    } else {
      siren::playUnlock();
    }

    settings::sync();
  }

  void lock() {
    if (settings::instance.isAlarm) {
      return;
    }

    settings::instance.isLocked = true;
    settings::sync();
    siren::playLock();
  }

  void enableAlarm() {
    if (settings::instance.isAlarm) {
      return;
    }

    if (!settings::instance.isLocked) {
      return;
    }

    settings::instance.isAlarm = true;
    settings::sync();

    siren::play();
  }
}