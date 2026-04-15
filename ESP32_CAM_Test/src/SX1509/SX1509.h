#ifndef SX1509_H
#define SX1509_H

#include "DeviceSetup.h"
#include <SparkFunSX1509.h>

const uint16_t STEPPER_STEPS_PER_REV = 4096;  // Half-steps per full revolution

// External Variables
extern SX1509 gpio;

// General Driver Functions
void SX1509_setup();

// Stepper motor control functions
void SX1509_stepper_move(int num_steps);
void SX1509_set_stepper_speed(int speed_rpm);

#endif
