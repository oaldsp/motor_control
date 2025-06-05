#include <stdint.h>
#include "motor.h"
#include "gpio.h"
#include "controller.h"
#include "assembly.h"
#include "lcd.h"

void MoveMotor(char* degress, char* rotation, char* speed){
	char error[] = {'E','r','r'};
	
	int size = 8;
	uint8_t steps[8] = {0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00};
	
	if(*rotation == 'A' && *speed == 'A'){
	/*Mapeamento da rotação Horária e Passo-Completo*/	
		for(int i = 0 ; i < size ; i++) {
			steps[i] = 0x01 << i;
		}
	}else if(*rotation == 'B' && *speed == 'A'){
	/*Mapeamento da rotação Anti-Horária e Passo-Completo*/
		for(int i = 0 ; i < size ; i++) {
			steps[i] = 0x01 << (size -1 -i);
		}
	}//else if(*rotation == 'A' && *speed == 'B'){
	///*Mapeamento da rotação Horária e Meio-Passo*/
	//	for(int i = 0 ; i < size ; i+=2) {
	//		steps[i] = 0x01 << i;
	//		steps[i+1] = 0x03 << i;
	//	}
	//}else if(*rotation == 'B' && *speed == 'B'){
	///*Mapeamento da rotação Anti-Horária e Meio-Passo*/
	//	for(int i = 0 ; i < size ; i+=2) {
	//		steps[i] = 0x01 << (size -1 - i);
	//		steps[i+1] = 0x03 << (size -1 -i);
	//	}
	//}
	else{
		WriteWord_LCD(error);
	}
	
	for (int i = 0; i < 100; i++) {
		for (int s = 0; s < 4; s++) {
			PortH_Output(~steps[s]);
			SysTick_Wait1ms(10);
		}
	}
	ShowStatus(degress, rotation, speed);
}
