#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

void MoveMotor(uint8_t* degress, uint8_t* rotation, uint8_t* speed);
void InitParameters(uint8_t* rotation, uint8_t* speed, int16_t* offset, int16_t* step);
void Move15degrees(int16_t* offset, int16_t* step, double steps15);
	
#endif
