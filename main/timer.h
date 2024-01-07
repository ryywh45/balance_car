#ifndef __TIMER_H__
#define __TIMER_H__


#define Period 10 // milli second

void ARDUINO_ISR_ATTR onTimer();
void Timer_init();
bool check_timer();


#endif // __TIMER_H__