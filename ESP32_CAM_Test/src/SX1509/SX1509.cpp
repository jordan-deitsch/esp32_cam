#include "SX1509.h"

// Externs
SX1509 gpio;

// Static Constants
static const uint8_t SX1509_MAX_PWM = 0;    // Inverted, so PWM = 0 results in 100% duty cycle
static const uint8_t SX1509_MIN_PWM = 255;  // Inverted, so PWM = 255 results in 0% duty cycle

// Static Variables
static uint8_t led_brightness = 0;
static bool fade_up = false;
static bool motor_fwd = true;

void SX1509_setup()
{
  // Set pinMode of GPIO expander pins
  gpio.pinMode(SX1509_LED_RED_PIN, ANALOG_OUTPUT);
  gpio.pinMode(SX1509_LED_GREEN_PIN, ANALOG_OUTPUT);
  gpio.pinMode(SX1509_LED_BLUE_PIN, ANALOG_OUTPUT);
  gpio.pinMode(SX1509_AI1_PIN, OUTPUT);
  gpio.pinMode(SX1509_AI2_PIN, OUTPUT);
  gpio.pinMode(SX1509_PWMA_PIN, ANALOG_OUTPUT);
  gpio.pinMode(SX1509_STBY_PIN, OUTPUT);
  
  // Initialize LED pin
  gpio.analogWrite(SX1509_LED_RED_PIN, SX1509_MIN_PWM);
  gpio.analogWrite(SX1509_LED_GREEN_PIN, SX1509_MIN_PWM);
  gpio.analogWrite(SX1509_LED_BLUE_PIN, SX1509_MIN_PWM);

  // Initialize motor driver to be enabled but in brake state
  gpio.digitalWrite(SX1509_STBY_PIN, HIGH);
  SX1509_motor_stop();
}

void SX1509_fade_led()
{
  if (led_brightness <= SX1509_MAX_PWM | led_brightness >= SX1509_MIN_PWM)
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

  gpio.analogWrite(SX1509_LED_RED_PIN, led_brightness);
}

void SX1509_motor_CW()
{
  gpio.digitalWrite(SX1509_AI1_PIN, HIGH);
  gpio.digitalWrite(SX1509_AI2_PIN, LOW);
  gpio.analogWrite(SX1509_PWMA_PIN, SX1509_MAX_PWM);
}


void SX1509_motor_CCW()
{
  gpio.digitalWrite(SX1509_AI1_PIN, LOW);
  gpio.digitalWrite(SX1509_AI2_PIN, HIGH);
  gpio.analogWrite(SX1509_PWMA_PIN, SX1509_MAX_PWM);
}


void SX1509_motor_stop()
{
  gpio.digitalWrite(SX1509_AI1_PIN, HIGH);
  gpio.digitalWrite(SX1509_AI2_PIN, HIGH);
  gpio.analogWrite(SX1509_PWMA_PIN, SX1509_MIN_PWM);
}


void SX1509_set_motor_standby(uint8_t stby)
{
  gpio.digitalWrite(SX1509_STBY_PIN, stby);
}

// Timed functions
void SX1509_reverse_motor()
{
  motor_fwd = !motor_fwd;
  if (motor_fwd)
  {
    SX1509_motor_CW();
  }
  else 
  {
    SX1509_motor_CCW();
  }

}