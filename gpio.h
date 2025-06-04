#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void GPIO_Init(void);
void PortK_Output(uint8_t valor);
void PortM_Output(uint8_t valor);
uint32_t Return_PortM(void);

#endif
