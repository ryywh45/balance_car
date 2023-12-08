#ifndef __MOTOR_H__
#define __MOTOR_H__

extern float pitch_angle;
extern float pitch_angular_v;
extern float speed_x;
extern float yaw_angular_v;

void Motor_ctrl();

void Apply_PWM(int pwm, int motor_num);
#define PWM_L 32
#define LIN1 25
#define LIN2 23
#define PWM_R 12
#define RIN1 27
#define RIN2 14


#endif // __MOTOR_H__