#include "led_blinker.h"

#include "app_config.h"

namespace {
static bool led_is_ready = false;
static bool led_is_on = false;
static unsigned long blink_interval_ms = APP_BLINK_INTERVAL_MS;
static unsigned long last_toggle_ms = 0;

bool led_blinker_can_use_simple_led(void) {
  if (!APP_LED_IS_SIMPLE_DIGITAL) {
    Serial.println("[LED] Simple digital LED mode is disabled in config.");
    return false;
  }

  if (APP_LED_IS_RGB) {
    Serial.println("[LED] RGB LED boards need board-specific handling.");
    Serial.println("[LED] Update app_config.h after confirming the real board.");
    return false;
  }

  return true;
}

uint8_t led_blinker_off_level(void) {
  return APP_LED_ON_LEVEL == HIGH ? LOW : HIGH;
}
}  // namespace

void led_blinker_init(void) {
  if (!led_blinker_can_use_simple_led()) {
    led_is_ready = false;
    return;
  }

  pinMode(APP_LED_PIN, OUTPUT);
  digitalWrite(APP_LED_PIN, led_blinker_off_level());

  led_is_ready = true;
  led_is_on = false;
  last_toggle_ms = millis();

  Serial.printf("[LED] LED pin is ready. pin=%d on_level=%u interval=%lu\n",
                APP_LED_PIN,
                APP_LED_ON_LEVEL,
                blink_interval_ms);
}

void led_blinker_update(void) {
  if (!led_is_ready) {
    return;
  }

  unsigned long current_ms = millis();
  if (current_ms - last_toggle_ms < blink_interval_ms) {
    return;
  }

  last_toggle_ms = current_ms;

  if (led_is_on) {
    led_blinker_turn_off();
  } else {
    led_blinker_turn_on();
  }
}

void led_blinker_set_interval_ms(unsigned long interval_ms) {
  blink_interval_ms = interval_ms;
  Serial.printf("[LED] Blink interval updated. interval=%lu\n", blink_interval_ms);
}

void led_blinker_turn_on(void) {
  if (!led_is_ready) {
    return;
  }

  digitalWrite(APP_LED_PIN, APP_LED_ON_LEVEL);
  led_is_on = true;
}

void led_blinker_turn_off(void) {
  if (!led_is_ready) {
    return;
  }

  digitalWrite(APP_LED_PIN, led_blinker_off_level());
  led_is_on = false;
}
