#ifndef LED_BLINKER_H
#define LED_BLINKER_H

#include <Arduino.h>

// 이 함수는 LED 핀을 준비하는 함수다.
void led_blinker_init(void);

// 이 함수는 주기적으로 호출되어 LED를 깜빡이게 한다.
void led_blinker_update(void);

// 이 함수는 LED 깜빡임 주기를 바꾸는 함수다.
void led_blinker_set_interval_ms(unsigned long interval_ms);

// 이 함수는 LED를 켜는 함수다.
void led_blinker_turn_on(void);

// 이 함수는 LED를 끄는 함수다.
void led_blinker_turn_off(void);

#endif
