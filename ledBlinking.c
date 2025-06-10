#include "ledBlinking.h"

void invertLED(){
	uint32_t n_data = Return_PortN();
  n_data ^= (1 << 1);
  PortN_Output(n_data);
}

void turnOffLED(){
	uint32_t n_data = Return_PortN();
	n_data &= (0 << 1);
	PortN_Output(n_data);
}