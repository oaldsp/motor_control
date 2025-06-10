#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#include "tm4c1294ncpdt.h"
#include "ledBlinking.h"

extern volatile int activated;

void init_timer();
void enable_counting();
void start_counting();
void stop_counting();
void Timer2A_Handler(void);


#endif