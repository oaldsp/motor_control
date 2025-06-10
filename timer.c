#include "timer.h"

volatile int activated = 0;

void init_timer(){
	//Ativa o temporizador
	SYSCTL_RCGCTIMER_R |= 0x04; //ativa clock do timer2
	while(!(SYSCTL_PRTIMER_R & 0x04)){}  //espera o timer2 estar pronto
  
	//Configura��o do modo
	TIMER2_CTL_R &= ~(0x01); //desabilita o timer
	TIMER2_CFG_R = 0x04; //configura para 16 bits
	TIMER2_TAMR_R = 0x01; //configura one-shot
		
	//Configura��o da temporiza��o para 100 ms	
	TIMER2_TAILR_R = 31249; //steps
	TIMER2_TAPR_R = TIMER2_TAPR_R | 0xFF; //prescale
	
	//Configura��o interrup��es a n�vel de perif�rico
	TIMER2_ICR_R = 0x01; //limpeza da interrup��o
  TIMER2_IMR_R = 0x01; //habilita a interrup��o do perif�rico
	
	//Configura��o da interrup��o NVIC
	NVIC_EN0_R = (1 << 23);
	NVIC_PRI5_R = (NVIC_PRI5_R & ~(7 << 29)) | (4 << 29);
}

void enable_counting(){
	TIMER2_CTL_R |= 0x01;
}

void start_counting(){
	activated = 1;
	enable_counting();
}

void stop_counting(){
	activated = 0;
}

void Timer2A_Handler(void){
	TIMER2_ICR_R = 0x01;
	
	if(activated){
		enable_counting();
		invertLED();
	}
	else{
		turnOffLED();
	}
}
