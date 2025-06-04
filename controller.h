#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>

void GetInitialInformation(char* degress, char* rotation, char* speed);
void GetDegress(char* degress);
void GetRotation(char* rotation);
void GetSpeed(char* speed);
void ShowStatus(char* degress, char* rotation, char* speed);
void ShowRotation(char* rotation, char* Error);
void ShowSpeed(char* speed, char* error);
void ShowDegress(char* degress);

#endif
