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

/*
pedir codigo de teste placa
entregar ate quando
posso ficar com a placa 
*/

int main(void)
                               {
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	
	LCD_Init();
	/*
	uint8_t steps[4] = {
  0b0001, // A1
  0b0010, // B1
  0b0100, // A2
  0b1000  // B2
	};
	*/
	
	while (1){
		//PortH_Output(0x01); SysTick_Wait1ms(5);
		//PortH_Output(0x02); SysTick_Wait1ms(5);
		//PortH_Output(0x04); SysTick_Wait1ms(5);
		//PortH_Output(0x08); SysTick_Wait1ms(5);
		uint8_t steps[4] = {~0x01, ~0x02, ~0x04, ~0x08}; // PH0 ? PH3
    for (int i = 0; i < 1000; i++) {
        for (int s = 0; s < 4; s++) {
            PortH_Output(steps[s]);
						WriteLetter_LCD(i);
            SysTick_Wait1ms(10);
        }
				clearDisplay();
    }
	}
	
	
	char degress[3] = {'\0','\0','\0'};
	char rotation = '\0';
	char speed = '\0';   	
	
	GetInitialInformation(degress, &rotation, &speed);	
	ShowStatus(degress, &rotation, &speed);
	
}
