#include "ADS1015.h"

// Externs
volatile uint16_t sensorValArr[NUM_ADC_CHANNELS] = {0, 0, 0, 0};
volatile float sensorVoltageArr[NUM_ADC_CHANNELS] = {0, 0, 0, 0};

// Constants
static const float VOLT_PER_LSB = 3.3f / 2047.0f;

// Variables


void ADS1015_get_all_channels()
{
  for (int i=0; i<NUM_ADC_CHANNELS; i++)
  {
    sensorValArr[i] = adcSensor.getSingleEnded(i);
    sensorVoltageArr[i] = (float)sensorValArr[i] * VOLT_PER_LSB;
    Serial.printf("Value %d: %0.2f  ", i, sensorVoltageArr[i]);
  }
  
  Serial.println();
}
