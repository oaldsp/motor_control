#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

#include "gpio.h"

enum LED{
	LED0 = 0x80,
	LED1 = 0x40,
	LED2 = 0x20,
	LED3 = 0x10,
	LED4 = 0x08,
	LED5 = 0x04,
	LED6 = 0x02,
	LED7 = 0x01
};
void enable_leds();
void turn_off_all();
void turn_on_all();
void turn_on(enum LED led);
void turn_on_int(uint8_t led);
void turn_off(enum LED led);
void turn_off_int(uint8_t led);
	
#endif
