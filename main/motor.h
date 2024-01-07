#ifndef __MOTOR_H__
#define __MOTOR_H__


extern float pitch_angle;
extern float pitch_angular_v;
extern float speed_x;
extern float yaw_angular_v;

void Motor_init();
void Motor_ctrl();
void Motor_test(int pwm_max);

void Apply_PWM(int pwm, int motor_num);
#define PWM_L 33
#define LIN1 26
#define LIN2 25
#define PWM_R 13
#define RIN1 14
#define RIN2 12
#define STBY 27


#endif // __MOTOR_H__