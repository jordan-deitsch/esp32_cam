#include "SX1509.h"

// Local functions
static void SX1509_stepper_shift(int dir);
static void SX1509_stepper_set_phases();

// External variables
SX1509 gpio;

// Static Constants
static const uint8_t SX1509_MAX_PWM = 0;    // Inverted, so PWM = 0 results in 100% duty cycle
static const uint8_t SX1509_MIN_PWM = 255;  // Inverted, so PWM = 255 results in 0% duty cycle
static const uint16_t STEPPER_MIN_DELAY_PER_STEP_MSEC = 1;
static const uint16_t STEPPER_MAX_DELAY_PER_STEP_MSEC = 100;
static const uint8_t STEPPER_NUM_PHASES = 4;
static const uint8_t STEPPER_PIN_ARR[] = {SX1509_A_PIN, 
                                          SX1509_B_PIN, 
                                          SX1509_C_PIN, 
                                          SX1509_D_PIN};

// Static Variables
static uint8_t stepper_shift_reg;
static uint16_t step_time_msec = 1;
static bool GPIO_PIN_STATE_ARR[STEPPER_NUM_PHASES];

void SX1509_setup()
{
  // Set pinMode of GPIO expander pins
  gpio.pinMode(SX1509_A_PIN, OUTPUT);
  gpio.pinMode(SX1509_B_PIN, OUTPUT);
  gpio.pinMode(SX1509_C_PIN, OUTPUT);
  gpio.pinMode(SX1509_D_PIN, OUTPUT);

  // Initialize stepper motor in known state (A)
  stepper_shift_reg = 0x03; // Phase A = 8'b0000_0011
  gpio.digitalWrite(SX1509_A_PIN, HIGH);
  gpio.digitalWrite(SX1509_B_PIN, LOW);
  gpio.digitalWrite(SX1509_C_PIN, LOW);
  gpio.digitalWrite(SX1509_D_PIN, LOW);

  GPIO_PIN_STATE_ARR[0] = true;
  GPIO_PIN_STATE_ARR[1] = false;
  GPIO_PIN_STATE_ARR[2] = false;
  GPIO_PIN_STATE_ARR[3] = false;

  // Set default stepper speed
  SX1509_set_stepper_speed(5);
}

void SX1509_stepper_move(int num_steps)
{
  if(num_steps == 0)
  {
    return;
  }

  for(int i=0; i<abs(num_steps); i++)
  {
    SX1509_stepper_shift(num_steps);
    SX1509_stepper_set_phases();
    delay(step_time_msec);
  }
}

void SX1509_set_stepper_speed(int speed_rpm)
{
  step_time_msec = (uint16_t)(60000.0f / ((float)STEPPER_STEPS_PER_REV * (float)speed_rpm));

  if(step_time_msec < STEPPER_MIN_DELAY_PER_STEP_MSEC)
  {
    step_time_msec = STEPPER_MIN_DELAY_PER_STEP_MSEC;
  }
  else if(step_time_msec > STEPPER_MAX_DELAY_PER_STEP_MSEC)
  {
    step_time_msec = STEPPER_MAX_DELAY_PER_STEP_MSEC;
  }

  Serial.printf("Stepper delay at %d RPM = %d msec", speed_rpm, step_time_msec);
  Serial.println();
}

static void SX1509_stepper_shift(int dir)
{
  uint8_t wrap_bit;
  
  if(dir > 0)
  {
    wrap_bit = (stepper_shift_reg >> 7) & 0x1;  // Get only the MSB of shift reg
    stepper_shift_reg = stepper_shift_reg << 1; // shift register 1 bit left
  }
  else
  {
    wrap_bit = (stepper_shift_reg & 0x1) << 7;  // Get only the LSB of shift reg
    stepper_shift_reg = stepper_shift_reg >> 1; // shift register 1 bit right
  }

  stepper_shift_reg = stepper_shift_reg | wrap_bit;
}

static void SX1509_stepper_set_phases()
{
  uint8_t phase_mask = 0x3;

  for(int i=0; i<STEPPER_NUM_PHASES; i++)
  {
    if((stepper_shift_reg & phase_mask) != 0)
    {
      if(GPIO_PIN_STATE_ARR[i] == false)
      {
        gpio.digitalWrite(STEPPER_PIN_ARR[i], HIGH);
        GPIO_PIN_STATE_ARR[i] = true;
      }
    }
    else
    {
      if(GPIO_PIN_STATE_ARR[i] == true)
      {
        gpio.digitalWrite(STEPPER_PIN_ARR[i], LOW);
        GPIO_PIN_STATE_ARR[i] = false;
      }
    }

    phase_mask = phase_mask << 2;
  }
}