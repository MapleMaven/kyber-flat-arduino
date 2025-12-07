#include <Arduino.h>
extern "C" uint64_t ESP_getEfuseMac(void) {
  return ESP.getEfuseMac();
}