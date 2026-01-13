#include "SX1509.h"

// Externs
SX1509 gpio;

// Static Constants
static const int MAX_BRIGHTNESS = 255;

// Static Variables
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
