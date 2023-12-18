#include "Arduino.h"
#include "mpu9250.h"
#include "MPU9250.h"

MPU9250 mpu;

void MPU9250_init() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }

    // calibrate anytime you want to
    Serial.println("Accel Gyro calibration will start in 5sec.");
    Serial.println("Please leave the device still on the flat plane.");
    mpu.verbose(true);
    delay(5000);
    mpu.calibrateAccelGyro();

    Serial.println("Mag calibration will start in 5sec.");
    Serial.println("Please Wave device in a figure eight until done.");
    delay(5000);
    mpu.calibrateMag();

    print_calibration();
    mpu.verbose(false);
}

void MPU9250_updata() {
  speed_x = mpu.getAccX();
  pitch_angular_v = mpu.getGyroY();
  pitch_angle = mpu.getPitch();
  yaw_angular_v = mpu.getGyroZ();
}

void MPU9250_test(){
  Serial.println("ax, gy, pitch, gz")
  Serial.print(mpu.getAccX());
  Serial.print(", ");
  Serial.print(mpu.getGyroY());
  Serial.print(", ");
  Serial.print(mpu.getPitch());
  Serial.print(", ");
  Serial.printmpu.getGyroZ());
  Serial.println(", ");
}
