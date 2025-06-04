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
8
==================================================================================================================*/
#include <stdint.h>
#include "lcd.h"
#include "assembly.h"
#include "gpio.h"
#include "keyboard.h"

int main(void)
{
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	
	LCD_Init();
  while (1){
		WriteLetter_LCD(GetKey());
		SysTick_Wait1ms(5000);
	}
	
	/*
	while (1)
	{
    //Se a USR_SW2 estiver pressionada
		if (PortJ_Input() == 0x1)
			PortN_Output(0x1);
    //Se a USR_SW1 estiver pressionada
		else if (PortJ_Input() == 0x2)
			PortN_Output(0x2);
    //Se ambas estiverem pressionadas
		else if (PortJ_Input() == 0x0)
			Pisca_leds();
    //Se nenhuma estiver pressionada
		else if (PortJ_Input() == 0x3)
			PortN_Output(0x0);        
	}
	*/
}

/*void Pisca_leds(void)
{
	PortN_Output(0x2);
	SysTick_Wait1ms(250);
	PortN_Output(0x1);
	SysTick_Wait1ms(250);
}*/
