#include <stdint.h>
#include "controller.h"
#include "keyboard.h"
#include "lcd.h"
#include "assembly.h"

void GetInitialInformation(char* degress, char* rotation, char* speed){
	GetDegress(degress);
	clearDisplay();
	GetRotation(rotation);
	clearDisplay();
	GetSpeed(speed);
	clearDisplay();
}

void GetDegress(char* degress){
	char degress_question[] = {'D','e','g','r','e','s','s',':',' ','\0'};
	WriteWord_LCD(degress_question);
	
	for(int cont = 0; cont < 3; cont++){
		while(degress[cont] == '\0'){
			degress[cont] = GetKey();
		}
		WriteLetter_LCD(degress[cont]);
		while(GetKey() != '\0'){
			SysTick_Wait1ms(10);
		}
	}
}

void GetRotation(char* rotation){
	char rotation_description[] = {'A','-','H','o',' ',' ','B','-','A','H','o','\0'};
	WriteWord_LCD(rotation_description);
	
	SkipLine();
	
	char rotation_question[] = {'R','o','t','a','t','i','o','n',':',' ','\0'};
	WriteWord_LCD(rotation_question);
	
	while(*rotation == '\0'){
		*rotation = GetKey();
	}
	WriteLetter_LCD(*rotation);
}

void GetSpeed(char* speed){
	char speed_description[] = {'A','-','P','C',' ',' ','B','-','M','P','\0'};
	WriteWord_LCD(speed_description);
	
	SkipLine();
	
	char speed_question[] = {'S','p','e','e','d',':',' ','\0'};
	WriteWord_LCD(speed_question);
	
	while(*speed == '\0'){
		*speed = GetKey();
	}
	WriteLetter_LCD(*speed);
}

void ShowStatus(char* degress, char* rotation, char* speed){
	char error[] = {'E','r','r'};
	
	clearDisplay();
	
	ShowRotation(rotation, error);
	SysTick_Wait1ms(50);
	ShowSpeed(speed, error);
	SysTick_Wait1ms(50);
	
	SkipLine();
	
	ShowDegress(degress);
	SysTick_Wait1ms(50);
}

void ShowRotation(char* rotation, char* error){
	if  (*rotation == 'A'){
		char clockwise[] = {'R','o',':',' ','H','o',' ',' ','\0'};
		WriteWord_LCD(clockwise);
	}else if (*rotation == 'B'){
		char counterclockwise[] = {'R','o',':',' ','A','H','o',' ',' ','\0'};
		WriteWord_LCD(counterclockwise);
	}else{
		WriteWord_LCD(error);
	}
}

void ShowSpeed(char* speed, char* error){
	if  (*speed == 'A'){
		char full_step[] = {'S','p',':',' ','P','C','\0'};
		WriteWord_LCD(full_step);
	}else if (*speed == 'B'){
		char half_step[] = {'S','p',':',' ','M','C','\0'};
		WriteWord_LCD(half_step);
	}else{
		WriteWord_LCD(error);
	}
}

void ShowDegress(char* degress){
	char degress_value[] = {'D','e','g','r','e','s','s',':',' ','\0'};
	WriteWord_LCD(degress_value);
	WriteWord_LCD(degress);
}
