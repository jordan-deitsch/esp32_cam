#ifndef SX1509_H
#define SX1509_H

#include "DeviceSetup.h"
#include <SparkFunSX1509.h>

// External Variables
extern SX1509 gpio;

// Functions
void SX1509_Setup();
void SX1509_fade_led();
void SX1509_motor_CW();
void SX1509_motor_CCW();
void SX1509_motor_stop();
void SX1509_set_motor_speed(int motor_speed);
void SX1509_set_motor_standby(uint8_t stby);

// Timed function
void SX1509_reverse_motor();

#endif
