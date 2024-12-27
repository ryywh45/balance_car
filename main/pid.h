#ifndef __PID_H__
#define __PID_H__


int balance(float angle, float angular_velocity);
#define Balance_angle 0.005

int speed(float angle, float speed);

int direction(float angular_velocity);


#endif // __PID_H__