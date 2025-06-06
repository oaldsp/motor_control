#include "gpio.h"
#include "lcd.h"
#include "assembly.h"

void LCD_Init(){
	SysTick_Wait1ms(40);//Espera LCD iniciar
	
	SendData_LCD(0x38,0);// 0x28 = função: 8 bits, 2 linhas, 5x8 pontos
  SysTick_Wait1ms(5);
	SendData_LCD(0x38,0);
  SysTick_Wait1us(150);
	SendData_LCD(0x38,0);
  SysTick_Wait1us(150);
		
	SendData_LCD(0x0C,0);// 0x0C = liga o display, sem cursor, sem blink
  MoveCursor_LCD();
  clearDisplay();
	SysTick_Wait1ms(20);
}

void Enable_LCD(){
	PortM_Output_LCD(Return_PortM() | 0x04);//Enable ON
	SysTick_Wait1us(20);
	PortM_Output_LCD(Return_PortM() & ~0x04);////Enable OFF
	SysTick_Wait1us(200);
}

void SendData_LCD(uint8_t data, uint8_t rs){
	/*
		RS = 0 -> INTRUCAO
		RS = 1 -> DADO
	*/
	PortM_Output_LCD(rs);//set RS e RW =  0
	PortK_Output(data);
	Enable_LCD();
}

void WriteWord_LCD(const uint8_t* w){
	while(*w != '\0'){
		WriteLetter_LCD(*w++);
	}
}

void WriteLetter_LCD(uint8_t c){
	SendData_LCD(c, 1);
	MoveCursor_LCD();
}

void clearDisplay(){
	SysTick_Wait1ms(100);
	SendData_LCD(0x01,0);
	SysTick_Wait1ms(100);
}
/*==================================================================================================================
		FUNCOES DE ABSTRACAO
==================================================================================================================*/
void MoveCursor_LCD(){
	SendData_LCD(0x06,0);
}

void SkipLine(){
	SendData_LCD(0xC0,0);
}

