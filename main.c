/*==================================================================================================================
Autores: Ot�vio Pepe, Bruno Camargo e Alexandre Vinicius
Descri��o: Programa em C para controlar motor de passo atrav�s da placa EK-TM4C1294-XL.
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
#include "leds.h"
#include "timer.h"

int main(void){
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	
	init_timer();
	LCD_Init();	
	enable_leds();
	turn_off_all();
	
	uint8_t end[] = {'E','n','d'};
	uint8_t degress[3] = {'\0','\0','\0'};
	uint8_t rotation = '\0';
	uint8_t speed = '\0';  
	
	while (1){
		GetInitialInformation(degress, &rotation, &speed);	
		start_counting();
		MoveMotor(degress, &rotation, &speed);
		stop_counting();
		ResetInformation(degress,&rotation,&speed);
		clearDisplay();
		WriteWord_LCD(end);
		while(GetKey() != '*'){
			SysTick_Wait1ms(10);
		}
		clearDisplay();
		turn_off_all();
	}
	
}
