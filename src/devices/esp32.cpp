#include <time.h> // The native ESP32 clock is wrapped by the standard time header
#include <sys/cdefs.h>
#include <sys/time.h>

#include <Wire.h>
#include <string>

#include <devices/esp32.h>

// Following forward declaration to access the interal temperature sensor of the ESP32, which is may not built-in (-> https://gist.github.com/xxlukas42/7e7e18604f61529b8398f7fcc5785251?permalink_comment_id=3532040#gistcomment-3532040)...
#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

void OswDevices::NativeESP32::setup() {
  // Test temperature for 128 (sensor not available) for 10 times
  for(int i = 0; i < 10; i++)
    if(temprature_sens_read() == 128)
      this->tempSensorIsBuiltIn = false;
}

uint32_t OswDevices::NativeESP32::getUTCTime() {
  return time(nullptr);
};

void OswDevices::NativeESP32::setUTCTime(const long& epoch) {
  time_t t = epoch;
  struct timeval now = { .tv_sec = t };
  settimeofday(&now, NULL);
};

float OswDevices::NativeESP32::getTemperature() {
  const uint8_t temp = temprature_sens_read();
  if(!this->tempSensorIsBuiltIn)
    return 0.0f;
  return (temp - 32) / 1.8;
}

bool OswDevices::NativeESP32::isTemperatureSensorAvailable() {
  return this->tempSensorIsBuiltIn;
}