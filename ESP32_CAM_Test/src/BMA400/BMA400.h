#ifndef BMA400_H
#define BMA400_H

#include <SparkFun_BMA400_Arduino_Library.h>
#include "DeviceSetup.h"

#define NUM_BMA400_CHANNELS (3)

// External Variables
extern BMA400 accelerometer;
extern volatile float bma400ValueArr[NUM_BMA400_CHANNELS];

// General Driver Functions
void BMA400_get_all_channels();
void BMA400_print_all_channels();

#endif
