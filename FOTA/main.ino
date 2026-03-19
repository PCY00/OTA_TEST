#include "app_config.h"
#include "led_blinker.h"
#include "ota_manager.h"
#include "wifi_manager.h"

namespace {
void app_print_startup_info(void) {
  Serial.printf("[APP] Project: %s\n", APP_PROJECT_NAME);
  Serial.printf("[APP] Blink interval: %lu ms\n", APP_BLINK_INTERVAL_MS);
  Serial.printf("[APP] LED pin: %d\n", APP_LED_PIN);
  Serial.printf("[APP] LED simple mode: %s\n", APP_LED_IS_SIMPLE_DIGITAL ? "true" : "false");
  Serial.printf("[APP] LED rgb mode: %s\n", APP_LED_IS_RGB ? "true" : "false");
}
}  // namespace

void setup() {
  Serial.begin(APP_SERIAL_BAUD_RATE);
  delay(200);

  Serial.println("[APP] Boot started.");
  app_print_startup_info();

  led_blinker_init();
  led_blinker_set_interval_ms(APP_BLINK_INTERVAL_MS);

  wifi_manager_begin();
  ota_manager_begin();
}

void loop() {
  led_blinker_update();
  wifi_manager_update();

  if (wifi_manager_is_connected() && !ota_manager_is_ready()) {
    ota_manager_begin();
  }

  ota_manager_update();
}
