#include "SX1509.h"

// Externs
SX1509 gpio;
int motorSpeedA = 0;

// Static Constants
static const int MAX_BRIGHTNESS = 255;
static const int MAX_MOTOR_SPEED = 255;

// Static Variables
static uint8_t led_brightness = 1;
static bool fade_up = true;
static bool motor_fwd = true;

void SX1509_Setup()
{
  // Set pinMode of GPIO expander pins
  gpio.pinMode(SX1509_LED_PIN, ANALOG_OUTPUT);
  gpio.pinMode(SX1509_AI1_PIN, OUTPUT);
  gpio.pinMode(SX1509_AI2_PIN, OUTPUT);
  gpio.pinMode(SX1509_PWMA_PIN, ANALOG_OUTPUT);
  gpio.pinMode(SX1509_STBY_PIN, OUTPUT);
  
  // Initialize LED pin
  gpio.analogWrite(SX1509_LED_PIN, LOW);

  // Initialize motor driver to be enabled but in brake state
  gpio.digitalWrite(SX1509_STBY_PIN, HIGH);
  SX1509_motor_stop();
}

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

void SX1509_motor_CW()
{
  gpio.digitalWrite(SX1509_AI1_PIN, HIGH);
  gpio.digitalWrite(SX1509_AI2_PIN, LOW);
  gpio.analogWrite(SX1509_PWMA_PIN, motorSpeedA);
}


void SX1509_motor_CCW()
{
  gpio.digitalWrite(SX1509_AI1_PIN, LOW);
  gpio.digitalWrite(SX1509_AI2_PIN, HIGH);
  gpio.analogWrite(SX1509_PWMA_PIN, motorSpeedA);
}


void SX1509_motor_stop()
{
  gpio.digitalWrite(SX1509_AI1_PIN, HIGH);
  gpio.digitalWrite(SX1509_AI2_PIN, HIGH);
  gpio.analogWrite(SX1509_PWMA_PIN, LOW);
}


void SX1509_set_motor_speed()
{
  // PWM output is reversed: 0 = 100%, 255 = 0% duty cycle
  int adjustedPWM = MAX_MOTOR_SPEED - motorSpeedA;
  if (adjustedPWM < 0)
  {
    adjustedPWM = 0;
  }
  gpio.analogWrite(SX1509_PWMA_PIN, adjustedPWM);
}


void SX1509_set_motor_standby(uint8_t stby)
{
  gpio.digitalWrite(SX1509_STBY_PIN, stby);
}


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