#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void LCD_Init(void);
void SendData_LCD(uint8_t byte, uint8_t rs);
void Enable_LCD(void);
void WriteLetter_LCD(uint8_t c);
void WriteWord_LCD(const uint8_t* w);
void MoveCursor_LCD(void);
void clearDisplay(void);
void SkipLine(void);

#endif
