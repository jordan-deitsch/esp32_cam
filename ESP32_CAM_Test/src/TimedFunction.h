#ifndef TIMED_FUNCTION_H
#define TIMED_FUNCTION_H


typedef void (*TimedFuctionPtr)();

struct TimedFunction
{
  unsigned long expire_time;
  unsigned long start_time;
  TimedFuctionPtr callback;
};

// Functions
void setup_timed_functions();
void check_timed_functions();

#endif
