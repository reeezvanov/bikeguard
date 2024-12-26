#pragma once

#include <Wire.h>

#include "utils.hpp"

#define FRAM_I2C_ADDR 0x50

namespace fram {
enum class ADDRESS : int {
  SETTINGS = 0,
  MAX = 32767
};

template<typename T>
 bool read(ADDRESS addr, void* data) {
  int len = sizeof(T);

  Wire.beginTransmission(FRAM_I2C_ADDR);
  Wire.write((byte*)&addr, 2);
  Wire.endTransmission();

  Wire.requestFrom(FRAM_I2C_ADDR, len);

  byte c;
  byte* p;
  for (c = 0, p = (byte*)data; Wire.available() && c < len; c++, p++) {
    *p = Wire.read();
  }

  delay(1);

  return true;
}

template<typename T>
 bool write(ADDRESS addr, void* data) {
  Wire.beginTransmission(FRAM_I2C_ADDR);
  Wire.write((byte*)&addr, 2);

  int len = sizeof(T);
  Wire.write((byte*)data, len);
  Wire.endTransmission(true);

  delay(1);

  return true;
}
}
