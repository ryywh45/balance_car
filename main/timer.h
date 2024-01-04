#ifdef __TIMER_H__
#define __TIMER_H__


#define Peroid 50 // milli second

void ARDUINO_ISR_ATTR onTimer();
void Timer_init();
void check_timer();


#endif // __TIMER_H__