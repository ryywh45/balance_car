#ifndef __MPU9250_H__
#define __MPU9250_H__

extern float pitch_angle;
extern float pitch_angular_v;
extern float speed_x;
extern float yaw_angular_v;


void MPU9250_init();
void MPU9250_update();
void MPU9250_test();

#endif // __MPU9250_H__