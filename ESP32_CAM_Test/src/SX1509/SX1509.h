#ifndef SX1509_H
#define SX1509_H

#include <SparkFunSX1509.h>

extern SX1509 gpio;
extern const byte SX1509_ADDRESS;
extern const byte SX1509_LED_PIN;

void SX1509_fade_led();

#endif
