#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

// 이 함수는 Wi-Fi 연결을 시작하는 함수다.
void wifi_manager_begin(void);

// 이 함수는 Wi-Fi 상태를 갱신하고 필요하면 재시도하는 함수다.
void wifi_manager_update(void);

// 이 함수는 Wi-Fi가 연결되었는지 알려주는 함수다.
bool wifi_manager_is_connected(void);

// 이 함수는 현재 Wi-Fi 상태를 출력하는 함수다.
void wifi_manager_print_status(void);

#endif
