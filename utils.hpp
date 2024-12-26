#pragma once

#define PRINT(x)            Serial.print(x)
#define PRINTLN(x, d)       Serial.println(x); delay(d)
#define PRINTVAL(x, v, d)   Serial.print(x); Serial.print(" \""); Serial.print(v); Serial.println("\""); delay(d)

namespace utils {
void trimStringEx(String& str) {
  str.remove(0, 1);
  str.remove(str.length() - 1);
}
}
