#ifndef __MPU9250_H__
#define __MPU9250_H__

float pitch_angle;
float pitch_angular_v;
float speed_x;
float yaw_angular_v;


void MPU9250_init();
void MPU9250_update();
void MPU9250_test();

#endif // __MPU9250_H__