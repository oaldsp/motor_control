#include "lcd.h"
#include "gpio.h"
#include "assembly.h"

void LCD_Init(){
	SysTick_Wait1ms(40);//Espera LCD iniciar
	SendData4_LCD(0x03);
	SysTick_Wait1ms(10);
	SendData4_LCD(0x02);
	SendData8_LCD(0x28,0);// 0x28 = função: 4 bits, 2 linhas, 5x8 pontos
  SendData8_LCD(0x0C,0);// 0x0C = liga o display, sem cursor, sem blink
  SendData8_LCD(0x06,0);// 0x06 = modo de entrada: move cursor para frente
  SendData8_LCD(0x01,0);// 0x01 = limpa display
	SysTick_Wait1ms(4);
}

void SendData4_LCD(uint8_t data){
	PortK_Output(data);
	Enable_LCD();
}

void Enable_LCD(){
	PortM_Output(Return_PortM() | 0x04);//Enable ON
	SysTick_Wait1us(2);
	PortM_Output(Return_PortM() & ~0x04);////Enable OFF
	SysTick_Wait1us(200);
}

void SendData8_LCD(uint8_t data, uint8_t rs){
	/*
		RS = 0 -> INTRUCAO
		RS = 1 -> DADO
	*/
	PortM_Output(rs);//set RS e RW =  0
	SendData4_LCD(data >> 4);//4 Bits mais significativos 
	SendData4_LCD(data & 0x0F);//4 Bits menos significativos 
}

void WriteLetter_LCD(char c){
	SendData8_LCD(c, 1);
}

void WriteWord_LCD(const char* w){
	while(*w){
		WriteLetter_LCD(*w++);
	}
}
