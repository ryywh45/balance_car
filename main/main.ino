#include "motor.h"
#include "mpu9250.h"

void setup(){
    MPU9250_init();
}

void loop(){
    //Motor_ctrl();
  MPU9250_test();
}