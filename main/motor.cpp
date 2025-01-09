#include "Arduino.h"
#include "motor.h"
#include "pid.h"
#include "MPU.h"

const int PWM_LIMIT = 4095;
//
void Motor_init(){
    // pinMode(PWM_L, OUTPUT);
    ledcAttach(PWM_L, 12000, 12);
    pinMode(LIN1, OUTPUT);
    pinMode(LIN2, OUTPUT);
    // pinMode(PWM_R, OUTPUT);
    ledcAttach(PWM_R, 12000, 12);
    pinMode(RIN1, OUTPUT);
    pinMode(RIN2, OUTPUT);
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, 1);
    digitalWrite(LIN1, 0);
    digitalWrite(LIN2, 0);
    digitalWrite(RIN1, 0);
    digitalWrite(RIN2, 0);
    // analogWriteResolution(PWM_L, 12); // 0 ~ 4095
    // analogWriteResolution(PWM_R, 12); // 0 ~ 4095
    // analogWriteResolution(PWM_L, 10); // 0 ~ 1023
    // analogWriteResolution(PWM_R, 10); // 0 ~ 1023
}

//
void Motor_ctrl(){
    int d_pwm = 0;//direction(yaw_angular_v);
    int pwm = balance(pitch_angle, pitch_angular_v)/* + speed(pitch_angle, speed_x)*/;

    int pwm_l = pwm + d_pwm;
    int pwm_r = pwm - d_pwm;

    //change 1023 to pwm_lim
    if (pwm_l > PWM_LIMIT) pwm_l = PWM_LIMIT;
    if (pwm_r > PWM_LIMIT) pwm_r = PWM_LIMIT;
    if (pwm_l < -PWM_LIMIT) pwm_l = -PWM_LIMIT;
    if (pwm_l < -PWM_LIMIT) pwm_r = -PWM_LIMIT;

    Apply_PWM(pwm_l, 1); // left
    Apply_PWM(pwm_r, 2); // right

    print_io_data(pwm_l);
}

//
void Apply_PWM(int pwm, int motor_num){
    if (pwm > 0){
        if (motor_num == 1){
            ledcWrite(PWM_L, pwm);
            digitalWrite(LIN1, 1); // (1,0) -> clockwise
            digitalWrite(LIN2, 0);
        }
        else{
            ledcWrite(PWM_R, pwm);
            digitalWrite(RIN1, 0); // 兩個馬達線接反的
            digitalWrite(RIN2, 1);
        }
    }
    else{
        if (motor_num == 1){
            ledcWrite(PWM_L, -pwm);
            digitalWrite(LIN1, 0); // (0,1) -> counter clockwise
            digitalWrite(LIN2, 1);
        }
        else{
            ledcWrite(PWM_R, -pwm);
            digitalWrite(RIN1, 1);
            digitalWrite(RIN2, 0);
        }
    }
}

void Motor_test(int pwm_max){
    for (int i=0; i<pwm_max; i+=10){
        Apply_PWM(i, 1); // left
        Apply_PWM(i, 2); // right
        delay(500);
    }
    for (int i=pwm_max; i>0; i-=10){
        Apply_PWM(i, 1); // left
        Apply_PWM(i, 2); // right
        delay(500);
    }
    for (int i=0; i<pwm_max; i+=10){
        Apply_PWM(-i, 1); // left
        Apply_PWM(-i, 2); // right
        delay(500);
    }
    for (int i=pwm_max; i>0; i-=10){
        Apply_PWM(-i, 1); // left
        Apply_PWM(-i, 2); // right
        delay(500);
    }
}