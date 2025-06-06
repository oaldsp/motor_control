#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void GPIO_Init(void);
void PortK_Output(uint32_t valor);
void PortM_Output_LCD(uint32_t valor);
void PortM_Output_Keyboard(uint32_t value);
uint32_t Return_PortM(void);
uint32_t PortL_Input(void);
void SetOneExitM(uint32_t offset);
uint32_t Return_PortL(void);
void PortH_Output(uint32_t valor);

#endif
