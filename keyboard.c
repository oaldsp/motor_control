#include "keyboard.h"
#include "gpio.h"
#include "assembly.h"

char keyboard[4][4] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'},
};

char GetKey(void)
{
	for(int column = 0; column < 4 ; column++){
		
		SetOneExitM(column);//Ativa uma coluna por vez 
		uint8_t lines = Return_PortL() & 0x0F;
		
		for(int line = 0; line < 4; line++){
			
			uint8_t analyzed_bit = 1 << line;
			
			if(!(lines & analyzed_bit))/*Se achar tecla apertada*/{
				//Espera ocupada ate soltar a tecla
				while(!(Return_PortL() & analyzed_bit)){
					SysTick_Wait1ms(10);
				}
				
				return keyboard[line][column]; 
			}
		}
	}
	return '\0';//Nenhuma tecla
}
