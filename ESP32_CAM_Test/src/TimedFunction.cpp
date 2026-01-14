#include <sys/_types.h>
#include "TimedFunction.h"

#include "src/SX1509/SX1509.h"
#include "src/ADS1015/ADS1015.h"

// Available timed functions
static TimedFunction tf_fade_led;
static TimedFunction tf_get_sensors;
static TimedFunction tf_reverse_motor;

static const unsigned long CHECK_LED_TIME = 10UL; // Update LED every 10 msec
static const unsigned long CHECK_SENSORS_TIME = 200UL; // Check sensors every 100 msec
static const unsigned long REVERSE_MOTOR_TIME = 1000UL; // Reverse motor direction every 1 sec

TimedFunction* timed_function_arr[NUM_TIMED_FUNCTIONS];

void setup_timed_functions()
{
  int i = 0;

  tf_fade_led.expire_time = CHECK_LED_TIME;
  tf_fade_led.start_time = millis();
  tf_fade_led.callback = &SX1509_fade_led;
  timed_function_arr[i++] = &tf_fade_led;

  tf_get_sensors.expire_time = CHECK_SENSORS_TIME;
  tf_get_sensors.start_time = millis();
  tf_get_sensors.callback = &ADS1015_get_all_channels;
  timed_function_arr[i++] = &tf_get_sensors;

  tf_reverse_motor.expire_time = REVERSE_MOTOR_TIME;
  tf_reverse_motor.start_time = millis();
  tf_reverse_motor.callback = &SX1509_reverse_motor;
  timed_function_arr[i++] = &tf_reverse_motor;
}

void check_timed_functions()
{
  unsigned long current_time = millis();
  for(int i=0; i<NUM_TIMED_FUNCTIONS; i++){
    if((current_time - timed_function_arr[i]->start_time) >= timed_function_arr[i]->expire_time) {
      timed_function_arr[i]->callback();            // Perform callback when time is reached
      timed_function_arr[i]->start_time = millis(); // Reset start time at end of performing callback
    }
  }
}
