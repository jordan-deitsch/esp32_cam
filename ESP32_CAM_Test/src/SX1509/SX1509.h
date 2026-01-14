#ifndef SX1509_H
#define SX1509_H

#include "DeviceSetup.h"
#include "src/TB6612FNG/SparkFun_TB6612.h"
#include <SparkFunSX1509.h>

// External Variables
extern SX1509 gpio;
extern Motor motorA;
extern const byte SX1509_ADDRESS;
extern const byte SX1509_LED_PIN;

// Functions
void SX1509_fade_led();
void SX1509_motor_CW();
void SX1509_motor_CCW();
void SX1509_motor_stop();
void SX1509_motor_speed();

#endif
