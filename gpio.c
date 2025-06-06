#include "tm4c1294ncpdt.h"
#include "gpio.h"
#include "assembly.h"

/*==================================================================================================================
		DEFINES DA PORTA H
==================================================================================================================*/
#define GPIO_PORTH_BASE     0x4005F000
#define GPIO_PORTH_AMSEL_R  (*((volatile uint32_t *)(GPIO_PORTH_BASE + 0x528)))
#define GPIO_PORTH_PCTL_R   (*((volatile uint32_t *)(GPIO_PORTH_BASE + 0x52C)))
#define GPIO_PORTH_DIR_R    (*((volatile uint32_t *)(GPIO_PORTH_BASE + 0x400)))
#define GPIO_PORTH_AFSEL_R 	(*((volatile uint32_t *)(GPIO_PORTH_BASE + 0x420)))
#define GPIO_PORTH_DEN_R    (*((volatile uint32_t *)(GPIO_PORTH_BASE + 0x51C)))
#define GPIO_PORTH_DATA_R   (*((volatile uint32_t *)(GPIO_PORTH_BASE + 0x3FC)))
/*================================================================================================================*/

#define GPIO_PORTH  (1 << 7) //bit 7 
#define GPIO_PORTK  (1 << 9) //bit 9
#define GPIO_PORTL  (1 << 10) //bit 10
#define GPIO_PORTM  (1 << 11) //bit 11

void GPIO_Init(void)
{
	//1a. Ativar o clock para a porta setando o bit correspondente no registrador RCGCGPIO
	SYSCTL_RCGCGPIO_R = (GPIO_PORTH | GPIO_PORTK | GPIO_PORTL | GPIO_PORTM);
	//1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
  while((SYSCTL_PRGPIO_R & (GPIO_PORTH | GPIO_PORTK | GPIO_PORTL | GPIO_PORTM) ) != (GPIO_PORTH | GPIO_PORTK | GPIO_PORTL | GPIO_PORTM) ){};
	
	// 2. Limpar o AMSEL para desabilitar a analógica
	GPIO_PORTH_AMSEL_R = 0x00; 
	GPIO_PORTK_AMSEL_R = 0x00;
	GPIO_PORTL_AMSEL_R = 0x00;
	GPIO_PORTM_AMSEL_R = 0x00;
		
	// 3. Limpar PCTL para selecionar o GPIO
	GPIO_PORTH_PCTL_R	= 0x00;
	GPIO_PORTK_PCTL_R = 0x00; //PK0-PK7
	GPIO_PORTL_PCTL_R = 0x00;
	GPIO_PORTM_PCTL_R = 0x00;
		
	// 4. DIR para 0 se for entrada, 1 se for saída
	GPIO_PORTH_DIR_R = 0xFF;
	GPIO_PORTK_DIR_R = 0xFF; //PK0-PK7
  GPIO_PORTL_DIR_R = 0x00;
	GPIO_PORTM_DIR_R = 0xFF; //PM7-PM4(Matricial)PM2-PM0(LCD)
		
	// 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função alternativa	
	GPIO_PORTH_AFSEL_R = 0x00;
	GPIO_PORTK_AFSEL_R = 0x00;
	GPIO_PORTL_AFSEL_R = 0x00;
	GPIO_PORTM_AFSEL_R = 0x00;
	
	// 6. Setar os bits de DEN para habilitar I/O digital	
	GPIO_PORTH_DEN_R = 0xFF;
	GPIO_PORTK_DEN_R = 0xFF; //PK0-PK7
	GPIO_PORTL_DEN_R = 0xFF;
	GPIO_PORTM_DEN_R = 0xFF; //PM7-PM4(Matricial)PM2-PM0(LCD)
	
	// 7. Habilitar resistor de pull-up interno, setar PUR para 1
	GPIO_PORTL_PUR_R = 0xFF;
}	

/*==================================================================================================================
		FUNCOES DE ABSTRACAO DE ENTRADA PARA AS PORTAS	
==================================================================================================================*/
uint32_t PortL_Input(void)
{
	return GPIO_PORTL_DATA_R;
}

/*==================================================================================================================
		FUNCOES DE ABSTRACAO DE SAIDA PARA AS PORTAS	
==================================================================================================================*/
void PortK_Output(uint32_t valor)
{
	GPIO_PORTK_DATA_R = valor; 
}

void PortH_Output(uint32_t valor)
{
	GPIO_PORTH_DATA_R = valor; 
}


void PortM_Output_LCD(uint32_t value)
{
	/*
		PM0	-> RS
		PM1 -> R/W
		PM2 -> E
	*/
	uint32_t temp;
	temp = GPIO_PORTM_DATA_R & 0xF8;
	//agora vamos fazer o OR com o valor recebido na função
	temp = temp | value;
	GPIO_PORTM_DATA_R = temp; 
}

void PortM_Output_Keyboard(uint32_t value)
{
	GPIO_PORTM_DATA_R = (GPIO_PORTM_DATA_R & 0x0F) | (value & 0xF0);
}

void SetOneExitM(uint32_t offset){
		uint8_t considered_bit = 0x10 << offset;
	
		GPIO_PORTM_DIR_R &= 0x0F;//Coloca colunas em Alta impedancia com 0
		SysTick_Wait1ms(1);
		
		GPIO_PORTM_DIR_R |= considered_bit;//Tira uma coluna de Alta impedancia colocando 1(Saida)(HABILITO UMA SAIDA)
		PortM_Output_Keyboard(Return_PortM() & ~considered_bit);
		SysTick_Wait1ms(1);
}

/*==================================================================================================================
		FUNCOES DE ABSTRACAO DE RETURN PARA DEFINES 
==================================================================================================================*/
uint32_t Return_PortM()
{
	return GPIO_PORTM_DATA_R /*& 0x07*/; 
}

uint32_t Return_PortL()
{
	return GPIO_PORTL_DATA_R; 
}
