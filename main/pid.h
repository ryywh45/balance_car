#ifndef __PID_H__
#define __PID_H__

extern float pitch_integral;

int balance(float angle, float angular_velocity);
#define Balance_angle 0.6

int speed(float angle, float speed);

int direction(float angular_velocity);


#endif // __PID_H__