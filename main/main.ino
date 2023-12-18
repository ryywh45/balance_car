#include "motor.h"
#include "mpu9250.h"
#include "timer.h"
#include "bluetooth.h"

void setup(){
    //Motor_init();
    //MPU9250_init();
    //Timer_init();
    BT_init();
}

void loop(){
    //Motor_ctrl();
    //delay(5);
    BT_read();
}