#include "tm4c1294ncpdt.h"
#include "gpio.h"

//#define GPIO_PORTJ  (0x0100) //bit 8
//#define GPIO_PORTN  (0x1000) //bit 12
#define GPIO_PORTK  (1 << 9) //bit 9
#define GPIO_PORTM  (1 << 11) //bit 11

void GPIO_Init(void)
{
	//1a. Ativar o clock para a porta setando o bit correspondente no registrador RCGCGPIO
	SYSCTL_RCGCGPIO_R = (/*GPIO_PORTJ | GPIO_PORTN*/ GPIO_PORTK | GPIO_PORTM);
	//1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
  while((SYSCTL_PRGPIO_R & (/*GPIO_PORTJ | GPIO_PORTN*/GPIO_PORTK | GPIO_PORTM) ) != (/*GPIO_PORTJ | GPIO_PORTN*/GPIO_PORTK | GPIO_PORTM) ){};
	
	// 2. Limpar o AMSEL para desabilitar a analógica
	//GPIO_PORTJ_AHB_AMSEL_R = 0x00;
	//GPIO_PORTN_AMSEL_R = 0x00;
	GPIO_PORTK_AMSEL_R = 0x00;
	GPIO_PORTM_AMSEL_R = 0x00;
		
	// 3. Limpar PCTL para selecionar o GPIO
	//GPIO_PORTJ_AHB_PCTL_R = 0x00;
	//GPIO_PORTN_PCTL_R = 0x00;
	GPIO_PORTK_PCTL_R = 0x00; //PK0-PK7
	GPIO_PORTM_PCTL_R = 0x00;
		
	// 4. DIR para 0 se for entrada, 1 se for saída
	//GPIO_PORTJ_AHB_DIR_R = 0x00;
	//GPIO_PORTN_DIR_R = 0x03; //BIT0 | BIT1
	GPIO_PORTK_DIR_R	 = 0xFF; //PK0-PK7
  GPIO_PORTM_AFSEL_R = 0x07; //PM0-PM3
		
	// 5. Limpar os bits AFSEL para 0 para selecionar GPIO sem função alternativa	
	//GPIO_PORTJ_AHB_AFSEL_R = 0x00;
	//GPIO_PORTN_AFSEL_R = 0x00; 
	GPIO_PORTK_AFSEL_R = 0x00;
	GPIO_PORTM_AFSEL_R = 0x00;
	
	// 6. Setar os bits de DEN para habilitar I/O digital	
	//GPIO_PORTJ_AHB_DEN_R = 0x03;   //Bit0 e bit1
	//GPIO_PORTN_DEN_R = 0x03; 		   //Bit0 e bit1
	GPIO_PORTK_DEN_R = 0xFF; //PK0-PK7
	GPIO_PORTM_DEN_R = 0x07;
	
	// 7. Habilitar resistor de pull-up interno, setar PUR para 1
	//GPIO_PORTJ_AHB_PUR_R = 0x03;   //Bit0 e bit1	

}	

/*==================================================================================================================
		FUNCOES DE ABSTRACAO DE ENTRADA PARA AS PORTAS	
==================================================================================================================*/
/*uint32_t PortJ_Input(void)
{
	return GPIO_PORTJ_AHB_DATA_R;
}*/

/*==================================================================================================================
		FUNCOES DE ABSTRACAO DE SAIDA PARA AS PORTAS	
==================================================================================================================*/
/*void PortN_Output(uint32_t valor)
{
    uint32_t temp;
    //vamos zerar somente os bits menos significativos
    //para uma escrita amigável nos bits 0 e 1
    temp = GPIO_PORTN_DATA_R & 0xFC;
    //agora vamos fazer o OR com o valor recebido na função
    temp = temp | valor;
    GPIO_PORTN_DATA_R = temp; 
}*/

void PortK_Output(uint8_t valor)
{
	GPIO_PORTK_DATA_R = valor; 
}

void PortM_Output(uint8_t valor)
{
	/*
		PM0	-> RS
		PM1 -> R/W
		PM2 -> E
	*/
	uint32_t temp;
	temp = GPIO_PORTM_DATA_R & 0xF8;
	//agora vamos fazer o OR com o valor recebido na função
	temp = temp | valor;
	GPIO_PORTM_DATA_R = temp; 
}
/*==================================================================================================================
		FUNCOES DE ABSTRACAO DE RETURN PARA DEFINES 
==================================================================================================================*/
uint32_t Return_PortM()
{
	return GPIO_PORTN_DATA_R; 
}



