/*==================================================================================================================
Autores: Otávio Pepe, Bruno Camargo e Alexandre Vinicius
Descrição: Programa em C para controlar motor de passo através da placa EK-TM4C1294-XL.
Data: 30/05/2025 
1
2
3
4
5
6
7
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
	
	char end[] = {'E','n','d'};
	char degress[3] = {'\0','\0','\0'};
	char rotation = '\0';
	char speed = '\0';   	
	
	while (1){
		GetInitialInformation(degress, &rotation, &speed);	
		MoveMotor(degress, &rotation, &speed);
		WriteWord_LCD(end);
	}
	
}
