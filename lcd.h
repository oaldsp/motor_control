#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void LCD_Init(void);
void SendData4_LCD(uint8_t data);
void SendData8_LCD(uint8_t byte, uint8_t rs);
void Enable_LCD(void);
void WriteLetter_LCD(char c);
void WriteWord_LCD(const char* w);

#endif
