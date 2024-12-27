#include "motor.h"
#include "MPU9250.h"
#include "timer.h"
//#include "bluetooth.h"

void setup(){
    MPU9250_init();
    Motor_init();
    Timer_init();
}

void loop(){
    // MPU9250_updata();
    // calibrateIMU();
    if (check_timer()){
        MPU9250_updata();
        //MPU9250_test();
        Motor_ctrl();
    }
}