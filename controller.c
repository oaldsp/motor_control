#include <stdint.h>
#include "controller.h"
#include "keyboard.h"
#include "lcd.h"
#include "assembly.h"

void GetInitialInformation(uint8_t* degress, uint8_t* rotation, uint8_t* speed){
	GetDegress(degress);
	clearDisplay();
	GetRotation(rotation);
	clearDisplay();
	GetSpeed(speed);
	clearDisplay();
}

void GetDegress(uint8_t* degress){
	uint8_t degress_question[] = {'D','e','g','r','e','s','s',':',' ','\0'};
	WriteWord_LCD(degress_question);
	
	for(uint16_t cont = 0; cont < 3; cont++){
		while(degress[cont] == '\0'){
			degress[cont] = GetKey();
		}
		WriteLetter_LCD(degress[cont]);
		while(GetKey() != '\0'){
			SysTick_Wait1ms(10);
		}
	}
}

void GetRotation(uint8_t* rotation){
	uint8_t rotation_description[] = {'A','-','C','w',' ',' ','B','-','A','C','w','\0'};
	WriteWord_LCD(rotation_description);
	
	SkipLine();
	
	uint8_t rotation_question[] = {'R','o','t','a','t','i','o','n',':',' ','\0'};
	WriteWord_LCD(rotation_question);
	
	while(*rotation == '\0'){
		*rotation = GetKey();
	}
	WriteLetter_LCD(*rotation);
}

void GetSpeed(uint8_t* speed){
	uint8_t speed_description[] = {'A','-','C','S',' ',' ','B','-','H','S','\0'};
	WriteWord_LCD(speed_description);
	
	SkipLine();
	
	uint8_t speed_question[] = {'S','p','e','e','d',':',' ','\0'};
	WriteWord_LCD(speed_question);
	
	while(*speed == '\0'){
		*speed = GetKey();
	}
	WriteLetter_LCD(*speed);
}

void ShowStatus(uint8_t* degress, uint8_t* rotation, uint8_t* speed){
	uint8_t error[] = {'E','r','r'};
	
	clearDisplay();
	
	ShowRotation(rotation, error);
	SysTick_Wait1ms(50);
	ShowSpeed(speed, error);
	SysTick_Wait1ms(50);
	
	SkipLine();
	
	ShowDegress(degress);
	SysTick_Wait1ms(50);
}

void ShowRotation(uint8_t* rotation, uint8_t* error){
	if  (*rotation == 'A'){
		uint8_t clockwise[] = {'R','o',':',' ','C','w',' ',' ','\0'};
		WriteWord_LCD(clockwise);
	}else if (*rotation == 'B'){
		uint8_t counterclockwise[] = {'R','o',':',' ','A','C','w',' ',' ','\0'};
		WriteWord_LCD(counterclockwise);
	}else{
		WriteWord_LCD(error);
	}
}

void ShowSpeed(uint8_t* speed, uint8_t* error){
	if  (*speed == 'A'){
		uint8_t full_step[] = {'S','p',':',' ','C','s','\0'};
		WriteWord_LCD(full_step);
	}else if (*speed == 'B'){
		uint8_t half_step[] = {'S','p',':',' ','M','s','\0'};
		WriteWord_LCD(half_step);
	}else{
		WriteWord_LCD(error);
	}
}

void ShowDegress(uint8_t* degress){
	uint8_t degress_value[] = {'D','e','g','r','e','s','s',':',' ','\0'};
	WriteWord_LCD(degress_value);
	WriteWord_LCD(degress);
}

void ResetInformation(uint8_t* degress, uint8_t* rotation, uint8_t* speed){
	*rotation = '\0';
	*speed = '\0';   	
	for(uint16_t i = 0 ; i < 3;  i++){
		degress[i] = '\0';
	}
}
