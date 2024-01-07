#include "motor.h"
#include "mpu9250.h"
#include "bluetooth.h"

void setup(){
    //MPU9250_init();
    BT_init();
}

void loop(){
    //Motor_ctrl();
    //MPU9250_updata();
    //MPU9250_test();
    BT_read();
    delay(50);
}