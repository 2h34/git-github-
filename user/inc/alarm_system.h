#ifndef ALARM_SYSTEM_H
#define ALARM_SYSTEM_H

#include <stdint.h>

void blink_led(uint8_t led_num,
               uint16_t times,
               uint32_t delay_ms);

void beep(uint32_t beep_ms);

void alarm_sys_func(void);

#endif