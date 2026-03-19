#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <Arduino.h>

// 이 상수는 프로젝트 이름을 저장한다.
static const char* APP_PROJECT_NAME = "ESP32-S3 FOTA LED Study Starter";

// 이 상수는 시리얼 통신 속도를 저장한다.
static const unsigned long APP_SERIAL_BAUD_RATE = 115200;

// 이 상수는 Wi-Fi SSID를 저장한다.
static const char* APP_WIFI_SSID = "embedded";

// 이 상수는 Wi-Fi 비밀번호를 저장한다.
static const char* APP_WIFI_PASSWORD = "00000011";

// 이 상수는 OTA에서 보일 장치 이름을 저장한다.
static const char* APP_OTA_HOSTNAME = "esp32s3-fota-led";

// 이 상수는 OTA 비밀번호를 저장한다.
static const char* APP_OTA_PASSWORD = "1234";

// 이 상수는 OTA 비밀번호 사용 여부를 저장한다.
static const bool APP_USE_OTA_PASSWORD = true;

// 이 상수는 단순 디지털 LED 사용 여부를 저장한다.
static const bool APP_LED_IS_SIMPLE_DIGITAL = true;

// 이 상수는 RGB LED 보드 여부를 저장한다.
static const bool APP_LED_IS_RGB = false;

// 이 상수는 RGB LED 데이터 핀 후보를 저장한다.
static const int APP_LED_RGB_DATA_PIN = -1;

// 이 상수는 LED가 켜질 때 출력해야 하는 레벨을 저장한다.
static const uint8_t APP_LED_ON_LEVEL = HIGH;

#ifdef LED_BUILTIN
// 이 상수는 LED 핀 번호를 저장한다.
static const int APP_LED_PIN = LED_BUILTIN;
#else
// 이 상수는 LED 핀 번호를 저장한다.
static const int APP_LED_PIN = 2;
#endif

// 이 상수는 LED 깜빡임 주기를 밀리초 단위로 저장한다.
static const unsigned long APP_BLINK_INTERVAL_MS = 5000;

// 이 상수는 Wi-Fi 최초 연결 대기 시간을 밀리초 단위로 저장한다.
static const unsigned long APP_WIFI_CONNECT_TIMEOUT_MS = 15000;

// 이 상수는 Wi-Fi 재시도 간격을 밀리초 단위로 저장한다.
static const unsigned long APP_WIFI_RETRY_INTERVAL_MS = 10000;

#endif
