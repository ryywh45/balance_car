#ifdef __TIMER_H__
#define __TIMER_H__


void ARDUINO_ISR_ATTR onTimer();
void Timer_init();
void check_timer();


#endif // __TIMER_H__