#include "wifi_manager.h"

#include <WiFi.h>

#include "app_config.h"

namespace {
static bool wifi_has_started = false;
static bool wifi_was_connected = false;
static unsigned long last_connect_attempt_ms = 0;

void wifi_manager_start_connect(void) {
  Serial.printf("[WIFI] Trying to connect to SSID: %s\n", APP_WIFI_SSID);
  WiFi.begin(APP_WIFI_SSID, APP_WIFI_PASSWORD);
  last_connect_attempt_ms = millis();
}

bool wifi_manager_connect_with_timeout(void) {
  wifi_manager_start_connect();

  unsigned long start_ms = millis();
  while (millis() - start_ms < APP_WIFI_CONNECT_TIMEOUT_MS) {
    if (WiFi.status() == WL_CONNECTED) {
      return true;
    }

    delay(100);
  }

  return WiFi.status() == WL_CONNECTED;
}
}  // namespace

void wifi_manager_begin(void) {
  WiFi.mode(WIFI_STA);
  wifi_has_started = true;

  if (wifi_manager_connect_with_timeout()) {
    wifi_was_connected = true;
    wifi_manager_print_status();
    return;
  }

  wifi_was_connected = false;
  Serial.println("[WIFI] Initial connection timed out. The app will keep retrying.");
}

void wifi_manager_update(void) {
  if (!wifi_has_started) {
    return;
  }

  bool is_connected = WiFi.status() == WL_CONNECTED;
  if (is_connected) {
    if (!wifi_was_connected) {
      wifi_was_connected = true;
      Serial.println("[WIFI] Connection restored.");
      wifi_manager_print_status();
    }
    return;
  }

  if (wifi_was_connected) {
    wifi_was_connected = false;
    Serial.println("[WIFI] Connection lost.");
  }

  unsigned long current_ms = millis();
  if (current_ms - last_connect_attempt_ms < APP_WIFI_RETRY_INTERVAL_MS) {
    return;
  }

  Serial.println("[WIFI] Retrying Wi-Fi connection.");
  wifi_manager_start_connect();
}

bool wifi_manager_is_connected(void) {
  return WiFi.status() == WL_CONNECTED;
}

void wifi_manager_print_status(void) {
  if (!wifi_manager_is_connected()) {
    Serial.println("[WIFI] Not connected.");
    return;
  }

  IPAddress local_ip = WiFi.localIP();
  Serial.printf("[WIFI] Connected. IP=%u.%u.%u.%u RSSI=%d\n",
                local_ip[0],
                local_ip[1],
                local_ip[2],
                local_ip[3],
                WiFi.RSSI());
}
