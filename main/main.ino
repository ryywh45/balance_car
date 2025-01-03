#include "motor.h"
#include "MPU.h"
#include "timer.h"
//#include "bluetooth.h"

void setup(){
    MPU9250_init();
    // calibrateIMU();
    loadCalibration();
    Motor_init();
    Timer_init();
}

void loop(){
    if (check_timer()){
        MPU9250_updata();
        MPU9250_test();
        // Motor_ctrl();
    }
}