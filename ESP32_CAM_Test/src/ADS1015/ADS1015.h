#ifndef ADS1015_H
#define ADS1015_H

#include <ADS1X15.h>
#include "DeviceSetup.h"

#define NUM_ADC_CHANNELS (4)

// External Variables
extern ADS1115 adcSensor;
extern volatile uint16_t adcValueArr[NUM_ADC_CHANNELS];
extern volatile float adcScaledArr[NUM_ADC_CHANNELS];

// General Driver Functions
void ADS1015_get_all_channels();
void ADS1015_print_all_channels();

#endif
