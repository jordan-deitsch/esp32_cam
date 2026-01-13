#include "SX1509.h"

// Externs
SX1509 gpio;                      // Create an SX1509 object
const byte SX1509_ADDRESS = 0x3E; // SX1509 I2C address: set by ADDR1 and ADDR0 (00 by default)
const byte SX1509_LED_PIN = 0;    // LED to SX1509's pin 0

// Constants
static const int MAX_BRIGHTNESS = 255;

// Variables
static uint8_t led_brightness = 1;
static bool fade_up = true;


void SX1509_fade_led()
{
  if (led_brightness >= MAX_BRIGHTNESS | led_brightness <= 0)
  {
    fade_up = !fade_up;
  }

  if (fade_up)
  {
    led_brightness++;
  }
  else
  {
    led_brightness--;
  }

  gpio.analogWrite(SX1509_LED_PIN, led_brightness);
}
