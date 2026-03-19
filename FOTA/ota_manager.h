#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

#include <Arduino.h>

// 이 함수는 OTA 서비스를 준비하는 함수다.
void ota_manager_begin(void);

// 이 함수는 OTA 요청이 들어왔는지 확인하는 함수다.
void ota_manager_update(void);

// 이 함수는 OTA가 준비되었는지 알려주는 함수다.
bool ota_manager_is_ready(void);

#endif
