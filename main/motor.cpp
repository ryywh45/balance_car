#include "Arduino.h"
#include "motor.h"
#include "pid.h"

//
void Motor_init(){
    digitalWrite(LIN1, 0);
    digitalWrite(LIN2, 0);
    digitalWrite(RIN1, 0);
    digitalWrite(RIN2, 0);
    analogWriteResolution(PWM_L, 12); // 0 ~ 4095
    analogWriteResolution(PWM_R, 12); // 0 ~ 4095
}

//
void Motor_ctrl(){
    int d_pwm = direction(yaw_angular_v);
    int pwm = balance(pitch_angle, pitch_angular_v) + speed(pitch_angle, speed_x);
    int pwm_l = pwm + d_pwm;
    int pwm_r = pwm - d_pwm;

    if (pwm_l > 4095) pwm_l = 4095;
    if (pwm_r > 4095) pwm_r = 4095;
    if (pwm_l < -4095) pwm_l = -4095;
    if (pwm_l < -4095) pwm_r = -4095;

    Apply_PWM(pwm_l, 1); // left
    Apply_PWM(pwm_r, 2); // right
}

//
void Apply_PWM(int pwm, int motor_num){
    if (pwm > 0){
        if (motor_num == 1){
            analogWrite(PWM_L, pwm);
            digitalWrite(LIN1, 1); // (1,0) -> clockwise
            digitalWrite(LIN2, 0);
        }
        else{
            analogWrite(PWM_R, pwm);
            digitalWrite(RIN1, 1);
            digitalWrite(RIN2, 0);
        }
    }
    else{
        if (motor_num == 1){
            analogWrite(PWM_L, -pwm);
            digitalWrite(LIN1, 0); // (0,1) -> counter clockwise
            digitalWrite(LIN2, 1);
        }
        else{
            analogWrite(PWM_R, -pwm);
            digitalWrite(RIN1, 0);
            digitalWrite(RIN2, 1);
        }
    }

}
