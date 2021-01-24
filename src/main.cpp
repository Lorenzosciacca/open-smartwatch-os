#include <Arduino.h>
#include <Wire.h>
#include <osw_app.h>
#include <osw_app_autumn.h>
#include <osw_app_ble_media_ctrl.h>
#include <osw_app_dnatilt.h>
#include <osw_app_fadein_display.h>
#include <osw_app_fireworks.h>
#include <osw_app_map.h>
#include <osw_app_pauls_watchface.h>
#include <osw_app_power_demo.h>
#include <osw_app_print_debug.h>
#include <osw_app_runtime_test.h>
#include <osw_app_show_display_size.h>
#include <osw_app_watchface_demo.h>
#include <osw_app_water_level.h>
#include <osw_hal.h>
#include <osw_pins.h>

OswHal *hal = new OswHal();
// OswAppPrintDebug *printDebug = new OswAppPrintDebug();
// OswAppFadeInDisplay *fadeIn = new OswAppFadeInDisplay(8 * 255);
// OswAppWatchFaceDemo *watchFace = new OswAppWatchFaceDemo();
// OswAppAutumn *autumn = new OswAppAutumn();
// OswAppShowDisplaySize *displaySize = new OswAppShowDisplaySize();
// OswAppPowerDemo *powerDemo = new OswAppPowerDemo();
// OswAppWaterLevel *waterLevel = new OswAppWaterLevel();
// OswAppMap *osmMap = new OswAppMap();
// OswAppFireworks *appFireworks = new OswAppFireworks();
// OswAppPaulsWatchface *paulsWatchFace = new OswAppPaulsWatchface();
// OswAppRuntimeTest *runtimeTest = new OswAppRuntimeTest();
OswAppBLEMEdiaCtrl *bleCtrl = new OswAppBLEMEdiaCtrl();

// #include "esp_task_wdt.h"
// TaskHandle_t Task1;
// void backgroundLoop(void *pvParameters) {
//   while (true) {
//     // hal->gpsParse();
//     // delay(1);
//   }
// }

void IRAM_ATTR isrStepDetect() { Serial.println("Step"); }

void setup() {
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, LOW);
  Serial.begin(115200);

  hal->setupPower();
  hal->setupButtons();
  hal->setupSensors();
  hal->setupDisplay();
  hal->setBrightness(128);

  Serial.print("B: ");
  Serial.println(hal->getBatteryRaw());
  // hal->setupGps();
  // hal->setupSD();

  // xTaskCreatePinnedToCore(backgroundLoop, "backgroundLoop", 1000 /*stack*/, NULL /*input*/, 0 /*prio*/,
  //                         &Task1 /*handle*/, 0);

  // call your watch app setup here
  // autumn->setup(hal);
  // powerDemo->setup(hal);
  // osmMap->setup(hal);
  // appFireworks->setup(hal);
  bleCtrl->setup(hal);
}

bool printDebugInfo = false;
void loop() {
  hal->checkButtons();
  hal->updateAccelerometer();

  // call your watch app loop here

  // fadeIn->loop(hal);
  // autumn->loop(hal);
  // displaySize->loop(hal);
  // powerDemo->loop(hal);
  // waterLevel->loop(hal);
  // appFireworks->loop(hal);
  // paulsWatchFace->loop(hal);
  // runtimeTest->loop(hal);
  bleCtrl->loop(hal);

  // if (hal->btn1Down()) {
  //   printDebugInfo = !printDebugInfo;
  //   hal->getCanvas()->getGraphics2D()->fill(rgb565(0,100,0));
  //   hal->flushCanvas();
  //   hal->setDebugGPS(printDebugInfo);
  //   delay(250);
  // }
  // if (printDebugInfo) {
  // printDebug->loop(hal);
  // } else {
  //   osmMap->loop(hal);
  // }

  // Serial.println(hal->getAccelerationX());

  // hal->deepSleep();
  delay(1000 / 30);
}
