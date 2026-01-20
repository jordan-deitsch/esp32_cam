#include "ADS1015.h"

// Externs
ADS1015 adcSensor;
volatile uint16_t adcValueArr[NUM_ADC_CHANNELS];
volatile float adcScaledArr[NUM_ADC_CHANNELS];

// Static Constants
static const uint32_t MAX_VALUE_SINGLE_END = 2047;
static const float ADC_VCC = 3.3f;
static const float VOLT_PER_LSB = ADC_VCC / (float)MAX_VALUE_SINGLE_END;

// Static Variables


void ADS1015_get_all_channels()
{
  uint16_t sensorRead;
  
  for (int i=0; i<NUM_ADC_CHANNELS; i++)
  {
    adcSensor.getSingleEnded(i);  // Dummy read to confirm address register is set
    sensorRead = adcSensor.getSingleEnded(i);
    if (sensorRead > MAX_VALUE_SINGLE_END)
    {
      sensorRead = 0;
    }
    adcValueArr[i] = sensorRead;
    adcScaledArr[i] = (float)adcValueArr[i] / (float)MAX_VALUE_SINGLE_END;
  }
}

void ADS1015_print_all_channels()
{
  for (int i=0; i<NUM_ADC_CHANNELS; i++)
  {
    Serial.printf("Value %d: %d  ", i, adcValueArr[i]);
  }
  Serial.println();
}
