#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>

void GetInitialInformation(uint8_t* degress, uint8_t* rotation, uint8_t* speed);
void GetDegress(uint8_t* degress);
void GetRotation(uint8_t* rotation);
void GetSpeed(uint8_t* speed);
void ShowStatus(uint8_t* degress, uint8_t* rotation, uint8_t* speed);
void ShowRotation(uint8_t* rotation, uint8_t* Error);
void ShowSpeed(uint8_t* speed, uint8_t* error);
void ShowDegress(uint8_t* degress);
void ResetInformation(uint8_t* degress, uint8_t* rotation, uint8_t* speed);

#endif
