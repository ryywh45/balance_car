#include "pid.h"

float Target_Speed = 0;
float Speed_Difference = 0;
float Integral_Speed_Diff = 0;
float Target_Direction = 0;
float Kp_b = 200,Kd_b = 0.1;
float Kp_s = 10,Ki_s = 0.08;
float Kp_d = 15,Kd_d = 0.5;

// Keep the car at a balance angle (pitch)
int balance(float angle, float angular_velocity){
    return Kp_b * (Balance_angle - angle) + Kd_b * angular_velocity; // PD
}

// Keep the car at target speed
// angle: pitch angle of a car
int speed(float angle, float speed){
    Speed_Difference = Speed_Difference * 0.8 + (Target_Speed - speed) * 0.2; // low pass
    Integral_Speed_Diff += Speed_Difference;
    if (Integral_Speed_Diff > 1000) Integral_Speed_Diff = 1000;
    if (Integral_Speed_Diff < -1000) Integral_Speed_Diff = -1000;
    if (angle > 80 || angle < -80) Integral_Speed_Diff = 0;
    return Kp_s * Speed_Difference + Ki_s * Integral_Speed_Diff; // PI
}

// Keep the car at a target direction (yaw)
int direction(float angular_velocity){
    if (Target_Direction == 0) return Kd_d * angular_velocity; // D
    else return Kp_d * Target_Direction; // P
}