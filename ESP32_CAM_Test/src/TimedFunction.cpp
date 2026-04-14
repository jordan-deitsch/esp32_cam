#include <sys/_types.h>
#include "TimedFunction.h"

#include "src/ADS1015/ADS1015.h"

// Available timed functions
static TimedFunction tf_fade_led;
static TimedFunction tf_get_sensors;
static TimedFunction tf_reverse_motor;

// Time delays for each timed function
static const unsigned long CHECK_SENSORS_TIME = 200UL; // Check sensors every 100 msec

// Define array for all timed functions
static const int NUM_TIMED_FUNCTIONS = 1;
static TimedFunction* timed_function_arr[NUM_TIMED_FUNCTIONS];

void setup_timed_functions()
{
  int i = 0;

  tf_get_sensors.expire_time = CHECK_SENSORS_TIME;
  tf_get_sensors.callback = &ADS1015_get_all_channels;
  timed_function_arr[i++] = &tf_get_sensors;

  // Initialize start time for all timed functions
  for (i=0; i<NUM_TIMED_FUNCTIONS; i++)
  {
    timed_function_arr[i]->start_time = millis();
  }
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
