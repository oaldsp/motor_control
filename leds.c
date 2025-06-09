#include "leds.h"


void enable_leds(){
	uint32_t data = Return_PortP();
	data = data | 0x20;
	PortP_Output(data);
}

void turn_off_all(){
	uint32_t a_data = Return_PortA();
	uint32_t q_data = Return_PortQ();
	a_data = a_data & ~(LED0 | LED1 | LED2 | LED3);
	PortA_Output(a_data);
	q_data = q_data & ~(LED4 | LED5 | LED6 | LED7);
	PortQ_Output(q_data);
}
void turn_on_all(){
	uint32_t a_data = Return_PortA();
	uint32_t q_data = Return_PortQ();
	a_data = a_data | (LED0 | LED1 | LED2 | LED3);
	PortA_Output(a_data);
	q_data = q_data | (LED4 | LED5 | LED6 | LED7);
	PortQ_Output(q_data);

}
void turn_on(enum LED led){
	switch (led){
		case LED0: case LED1: case LED2: case LED3: {
			uint32_t a_data = Return_PortA();
			a_data = a_data | led;
			PortA_Output(a_data);
		}break;
		case LED4: case LED5: case LED6: case LED7:{
			uint32_t q_data = Return_PortQ();
			q_data = q_data | led;
			PortQ_Output(q_data);
		}break;
	}
}

void turn_on_int(uint8_t led){
	switch (led){
		case 0: turn_on(LED0);break;
		case 1: turn_on(LED1);break;
		case 2: turn_on(LED2);break;
		case 3: turn_on(LED3);break;
		case 4: turn_on(LED4);break;
		case 5: turn_on(LED5);break;
		case 6: turn_on(LED6);break;
		case 7: turn_on(LED7);break;
	}
}

void turn_off(enum LED led){
	switch (led){
		case LED0: case LED1: case LED2: case LED3: {
			uint32_t a_data = Return_PortA();
			a_data = a_data & ~(led);
			PortA_Output(a_data);
		}break;
		case LED4: case LED5: case LED6: case LED7:{
			uint32_t q_data = Return_PortQ();
			q_data = q_data & ~(led);
			PortQ_Output(q_data);
		}break;
	}
}

void turn_off_int(uint8_t led){
	switch (led){
		case 0: turn_off(LED0);break;
		case 1: turn_off(LED1);break;
		case 2: turn_off(LED2);break;
		case 3: turn_off(LED3);break;
		case 4: turn_off(LED4);break;
		case 5: turn_off(LED5);break;
		case 6: turn_off(LED6);break;
		case 7: turn_off(LED7);break;
	}
}