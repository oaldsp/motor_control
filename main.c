/*==================================================================================================================
Autores: Otávio Pepe, Bruno Camargo e Alexandre Vinicius
Descrição: Programa em C para controlar motor de passo através da placa EK-TM4C1294-XL.
Data: 30/05/2025 

TODO - OQUE FALTA
-> FLUXOGRAMA
-> Item 4 olhar o TODO no motor.c
-> Item 7
==================================================================================================================*/
#include <stdint.h>
#include "lcd.h"
#include "assembly.h"
#include "gpio.h"
#include "keyboard.h"
#include "controller.h"
#include "motor.h"

int main(void){
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	
	LCD_Init();	
	
	uint8_t end[] = {'E','n','d'};
	uint8_t degress[3] = {'\0','\0','\0'};
	uint8_t rotation = '\0';
	uint8_t speed = '\0';   	
	
	while (1){
		GetInitialInformation(degress, &rotation, &speed);	
		MoveMotor(degress, &rotation, &speed);
		ResetInformation(degress,&rotation,&speed);
		clearDisplay();
		WriteWord_LCD(end);
		while(GetKey() != '*'){
			SysTick_Wait1ms(10);
		}
		clearDisplay();
	}
	
}
