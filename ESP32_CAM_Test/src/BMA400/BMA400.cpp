#include "BMA400.h"

// Externs
BMA400 accelerometer;
volatile float bma400ValueArr[NUM_BMA400_CHANNELS];

// Static Constants

// Static Variables


void BMA400_get_all_channels()
{
  accelerometer.getSensorData();
  bma400ValueArr[0] = accelerometer.data.accelX;
  bma400ValueArr[1] = accelerometer.data.accelY;
  bma400ValueArr[2] = accelerometer.data.accelZ;
}

void BMA400_print_all_channels()
{
  for (int i=0; i<NUM_BMA400_CHANNELS; i++)
  {
    Serial.printf("Value %d: %.3f  ", i, bma400ValueArr[i]);
  }
  Serial.println();
}
