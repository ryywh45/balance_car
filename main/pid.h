#ifndef __PID_H__
#define __PID_H__


int balance(float angle, float angular_velocity);
#define Balance_angle 0
#define Kp_b 200
#define Kd_b 0.1

int speed(float angle, float speed);
#define Kp_s 10
#define Ki_s 0.08

int direction(float angular_velocity);
#define Kp_d 15
#define Kd_d 0.5


#endif // __PID_H__