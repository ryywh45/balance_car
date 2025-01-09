#include "motor.h"
#include "MPU.h"
#include "timer.h"
#include "bluetooth.h"

BluetoothHelper btHelper("ESP32-BT-Slave");
extern BluetoothHelper btHelper;

void setup(){
    MPU9250_init();
    // calibrateIMU();
    loadCalibration();
    Motor_init();
    Timer_init();
    btHelper.BT_init();
}

void loop(){
    if (check_timer()){
        btHelper.BT_read();
        MPU9250_updata();
        // MPU9250_test();
        Motor_ctrl();
    }
}