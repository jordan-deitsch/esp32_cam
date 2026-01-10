#ifndef ADS1015_H
#define ADS1015_H

#include <SparkFun_ADS1015_Arduino_Library.h>

#define NUM_ADC_CHANNELS (4)

extern ADS1015 adcSensor;
extern volatile uint16_t adcValueArr[NUM_ADC_CHANNELS];

void ADS1015_get_all_channels();

#endif
