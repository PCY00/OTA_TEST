#include "ota_manager.h"

#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFi.h>

#include "app_config.h"

namespace {
static bool ota_is_ready = false;
static bool ota_has_logged_waiting_for_wifi = false;

void ota_manager_handle_start(void) {
  Serial.println("[OTA] Update started.");
}

void ota_manager_handle_end(void) {
  Serial.println("[OTA] Update finished.");
}

void ota_manager_handle_progress(unsigned int progress, unsigned int total) {
  unsigned int percent = 0;
  if (total > 0) {
    percent = (progress * 100U) / total;
  }

  Serial.printf("[OTA] Progress: %u%%\n", percent);
}

void ota_manager_handle_error(ota_error_t error) {
  Serial.printf("[OTA] Error code: %u\n", static_cast<unsigned int>(error));

  switch (error) {
    case OTA_AUTH_ERROR:
      Serial.println("[OTA] Auth failed.");
      break;
    case OTA_BEGIN_ERROR:
      Serial.println("[OTA] Begin failed.");
      break;
    case OTA_CONNECT_ERROR:
      Serial.println("[OTA] Connect failed.");
      break;
    case OTA_RECEIVE_ERROR:
      Serial.println("[OTA] Receive failed.");
      break;
    case OTA_END_ERROR:
      Serial.println("[OTA] End failed.");
      break;
    default:
      Serial.println("[OTA] Unknown OTA error.");
      break;
  }
}
}  // namespace

void ota_manager_begin(void) {
  if (ota_is_ready) {
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    if (!ota_has_logged_waiting_for_wifi) {
      Serial.println("[OTA] Wi-Fi is not ready. OTA init will wait.");
      ota_has_logged_waiting_for_wifi = true;
    }
    return;
  }

  ota_has_logged_waiting_for_wifi = false;

  ArduinoOTA.setHostname(APP_OTA_HOSTNAME);
  if (APP_USE_OTA_PASSWORD) {
    ArduinoOTA.setPassword(APP_OTA_PASSWORD);
  }

  ArduinoOTA.onStart(ota_manager_handle_start);
  ArduinoOTA.onEnd(ota_manager_handle_end);
  ArduinoOTA.onProgress(ota_manager_handle_progress);
  ArduinoOTA.onError(ota_manager_handle_error);
  ArduinoOTA.begin();

  ota_is_ready = true;
  Serial.printf("[OTA] OTA is ready. hostname=%s\n", APP_OTA_HOSTNAME);
}

void ota_manager_update(void) {
  if (!ota_is_ready) {
    return;
  }

  ArduinoOTA.handle();
}

bool ota_manager_is_ready(void) {
  return ota_is_ready;
}
