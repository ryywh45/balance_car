#ifndef __CAR_MAIN_PID__
#define __CAR_MAIN_PID__


int balance(float, float);
#define Balance_angle 0
#define Kp_b 2
#define Kd_b 0.1

int speed(float, float);
#define Kp_s 2
#define Ki_s 0.1

int direction(float);
#define Kd_d 0.1


#endif // __CAR_MAIN_PID__