#ifndef ADS1015_H
#define ADS1015_H

#include <SparkFun_ADS1015_Arduino_Library.h>

#define NUM_ADC_CHANNELS (4)

extern ADS1015 adcSensor;
extern volatile uint16_t sensorValArr[NUM_ADC_CHANNELS];
extern volatile float sensorVoltageArr[NUM_ADC_CHANNELS];

void ADS1015_get_all_channels();

#endif
