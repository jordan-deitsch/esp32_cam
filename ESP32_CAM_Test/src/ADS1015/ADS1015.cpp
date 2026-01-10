#include "ADS1015.h"

// Externs
volatile uint16_t sensorValArr[NUM_ADC_CHANNELS];
volatile float sensorVoltageArr[NUM_ADC_CHANNELS];

// Constants
static const uint16_t MAX_VALUE_SINGLE_END = 2047;
static const float ADC_VCC = 3.3f;
static const float VOLT_PER_LSB = ADC_VCC / (float)MAX_VALUE_SINGLE_END;

// Variables

void ADS1015_get_all_channels()
{
  for (int i=0; i<NUM_ADC_CHANNELS; i++)
  {
    uint16_t sensorRead = adcSensor.getSingleEnded(i);
    if (sensorRead <= MAX_VALUE_SINGLE_END)
    {
      sensorValArr[i] = sensorRead;
    }
    sensorVoltageArr[i] = (float)sensorValArr[i] * VOLT_PER_LSB;
    Serial.printf("Value %d: %d  ", i, sensorValArr[i]);
  }
  
  Serial.println();
}
