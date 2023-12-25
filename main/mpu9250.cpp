#include "Arduino.h"
#include "mpu9250.h"
#include "MPU9250.h"

MPU9250 mpu;

float pitch_angle;
float pitch_angular_v;
float speed_x;
float yaw_angular_v;

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

    mpu.verbose(false);
}

void MPU9250_updata() {
  speed_x = mpu.getAccX();
  pitch_angular_v = mpu.getGyroY();
  pitch_angle = mpu.getPitch();
  yaw_angular_v = mpu.getGyroZ();
}

void MPU9250_test(){
  Serial.print("Accelerometer: ");
  Serial.print(mpu.getAccX());
  Serial.print(", ");
  Serial.print(mpu.getAccY());
  Serial.print(", ");
  Serial.print(mpu.getAccZ());
  Serial.println("");

  Serial.print("Gyro: ");
  Serial.print(mpu.getGyroX());
  Serial.print(", ");
  Serial.print(mpu.getGyroY());
  Serial.print(", ");
  Serial.print(mpu.getGyroZ());
  Serial.println("");
  
  Serial.print("Compass: ");
  Serial.print(mpu.getRow());
  Serial.print(", ");
  Serial.print(mpu.getPitch());
  Serial.print(", ");
  Serial.print(mpu.getYaw());
  Serial.println("");
}
