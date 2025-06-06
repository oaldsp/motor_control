
#include <stdio.h>//Para spintf
#include <stdlib.h> //Para strtol

#include <stdint.h>
#include "motor.h"
#include "gpio.h"
#include "controller.h"
#include "assembly.h"
#include "lcd.h"

#define MOTOR_STEPS_PER_LAP 512 //Dadasheet

void MoveMotor(uint8_t* degress, uint8_t* rotation, uint8_t* speed){
	/*Calcula passos para andar 15 graus. *Arredonda para o piso* */
	double steps15 = (15.0 / 360.0)*MOTOR_STEPS_PER_LAP;
	
	//int32_t size = 8;
	int16_t offset = 0;
	int16_t step = 1;
	
	InitParameters(rotation, speed, &offset, &step);
	
	uint16_t iterations = strtol/*converte str para int*/((char*)degress, NULL, 10)/15;
	for(uint16_t i = 1; i <= iterations; i++){
		
		sprintf((char*)degress,"%d", 15*i);
		
		ShowStatus(degress, rotation, speed);
		if(i % 3 == 0){
		/*Multiplo de 45 graus*/
			/*=============================
				TODO - ACENDER LED AQUI
			=============================*/
		}
		Move15degrees(&offset, &step, steps15);
	}
}

void InitParameters(uint8_t* rotation, uint8_t* speed, int16_t* offset, int16_t* step){
	uint8_t error[] = {'E','r','r',' ','M','M'};
	
	if(*rotation == 'A'){
		/*Se for Horario permanece em 1*/
		/*Anti - Horario*/
		*offset = 8;
		*step *= -1;
	}else if(*rotation != 'B'){
		WriteWord_LCD(error);
	}
	
	if(*speed == 'A'){
		/*Se for Meio-Passo permanece em 1*/
		/*Passo-compleo*/
		*step *= 2; 
	}else if(*speed != 'B'){
		WriteWord_LCD(error);
	}
}

void Move15degrees(int16_t* offset, int16_t* step, double steps15){
	uint8_t steps[9] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09, 0x01};
		
	for (uint16_t i = 0; i < steps15; i++) {
		for (int16_t s = *offset; (s > -1) && (s < 9)  ; s += *step) {
			PortH_Output(~steps[s]);
			SysTick_Wait1ms(10);
		}
	}
}
