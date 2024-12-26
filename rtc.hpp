#pragma once

#include "utils.hpp"

#include <I2C_RTC.h>
#include <StringUtils.h>


namespace rtc {
   DS1307 instance;

   void begin() {
    instance.begin();

    while (!instance.isConnected()) {
      PRINTLN("RTC module is not connected!", 1000);
    }
    
    instance.startClock();
    instance.setHourMode(CLOCK_H24);
  }

   time_t getTimestamp() {
    return instance.getEpoch();
  }

   void setDateTime(int day, int month, int year, int hour, int minute, int second) {
    instance.setDay((uint8_t)day);
    instance.setMonth((uint8_t)month);
    instance.setYear((uint16_t)year);
    instance.setHours((uint8_t)hour);
    instance.setMinutes((uint8_t)minute);
    instance.setSeconds((uint8_t)second);
  }

   void setDateTime(String dateTimeStr) {
    Text dateTimeText = Text(dateTimeStr);

    su::TextList dateTimeTextList(dateTimeText, ' ');
    if (dateTimeTextList.length() != 2) {
      PRINTLN("Wrong datetime format", 20);
      return;
    }

    Text dateTxt = Text(dateTimeTextList[0]);
    if (dateTxt.count('.') != 3) {
      PRINTLN("Wrong date format", 20);
      return;
    }
    
    Text timeTxt = Text(dateTimeTextList[1]);
    if (timeTxt.count(':') != 3) {
      PRINTLN("Wrong time format", 20);
      return;
    }
    
    char buffer[20];
    int day, month, year, hour, minute, second;
    sscanf(dateTimeStr.c_str(), "%d.%d.%d %d:%d:%d", &day, &month, &year, &hour, &minute, &second);
    setDateTime(day, month, year, hour, minute, second);
  }

   String getDateTimeString() {
    char buffer[20];

    uint8_t   day =     instance.getDay();
    uint8_t   month =   instance.getMonth();
    uint16_t  year =    instance.getYear();

    uint8_t   hour =    instance.getHours();
    uint8_t   minute =  instance.getMinutes();
    uint8_t   second =  instance.getSeconds();

    sprintf(buffer, "%02u.%02u.%04u %02u:%02u:%02u", day, month, year, hour, minute, second);

    return String(buffer);
  }
}