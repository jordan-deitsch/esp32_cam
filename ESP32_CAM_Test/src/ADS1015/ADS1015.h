#ifndef ADS1015_H
#define ADS1015_H

#include <SparkFun_ADS1015_Arduino_Library.h>
#include "DeviceSetup.h"

#define NUM_ADC_CHANNELS (4)

// External Variables
extern ADS1015 adcSensor;
extern volatile uint16_t adcValueArr[NUM_ADC_CHANNELS];
extern volatile float adcScaledArr[NUM_ADC_CHANNELS];

// General Driver Functions
void ADS1015_get_all_channels();

#endif
