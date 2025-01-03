#include "Arduino.h"
#include "MPU.h"
#include "MPU9250.h"
#include "math.h"
#include <EEPROM.h>

MPU9250 mpu;

// unit of acc [m/s2], gyro [deg/s], angle [deg]
float pitch_angle;
float pitch_angular_v;
float speed_x;
float yaw_angular_v;
float aX, aY, aZ, gX, gY, gZ;
float previousTime = 0, currentTime = 0, elaspTime = 0;

enum EEP_ADDR {
    EEP_CALIB_FLAG = 0x00,
    EEP_ACC_BIAS = 0x01,
    EEP_GYRO_BIAS = 0x0D,
    EEP_MAG_BIAS = 0x19,
    EEP_MAG_SCALE = 0x25
};

// initial
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
}

// update speed_x, pitch_angular_v, pitch_angle, yaw_angular_v
void MPU9250_updata() {
  if (mpu.update()) {
    currentTime = millis();
    elaspTime = (currentTime - previousTime) / 1000;
    previousTime = currentTime;
    aX = mpu.getAccX();
    aY = mpu.getAccY();
    aZ = mpu.getAccZ();
    gX = mpu.getGyroX();
    gY = mpu.getGyroY();
    gZ = mpu.getGyroZ();
    pitch_angle = mpu.getRoll(); //實際pitch與roll相反
    speed_x = -((aX * 10 + 10 * sin(pitch_angle)) * elaspTime);            //向前是正
    pitch_angular_v = gY;     //向前傾斜角度是正 
    yaw_angular_v = -gZ;      //向右轉是正
  }
}
// print acc,gyro,pitch
void MPU9250_test(){
  Serial.println("ax,ay,az,gx,gy,gz,pitch,speed_x");
  Serial.print(aX*9.8,2);
  Serial.print("\t");
  Serial.print(aY*9.8,2);
  Serial.print("\t");
  Serial.print(aZ*9.8,2);
  Serial.print("\t");
  Serial.print(gX,2);
  Serial.print("\t");
  Serial.print(gY,2);
  Serial.print("\t");
  Serial.print(gZ,2);
  Serial.print("\t");
  Serial.print(pitch_angle,2);
  Serial.print("\t");
  Serial.print(pitch_angular_v ,2);
  Serial.print("\t");
  Serial.print(speed_x,2);
  Serial.println("");
}

// update Bias(XXXError)
void calibrateIMU() {
  delay(5000);

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

  saveCalibration();
}

void print_calibration() {
    Serial.println("< calibration parameters >");
    Serial.println("accel bias [g]: ");
    Serial.print(mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.println();
    Serial.println("gyro bias [deg/s]: ");
    Serial.print(mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.println();
    Serial.println("mag bias [mG]: ");
    Serial.print(mpu.getMagBiasX());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasY());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasZ());
    Serial.println();
    Serial.println("mag scale []: ");
    Serial.print(mpu.getMagScaleX());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleY());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleZ());
    Serial.println();
}

void saveCalibration() {
    Serial.println("Write calibrated parameters to EEPROM");
    writeByte(EEP_CALIB_FLAG, 1);
    writeFloat(EEP_ACC_BIAS + 0, mpu.getAccBias(0));
    writeFloat(EEP_ACC_BIAS + 4, mpu.getAccBias(1));
    writeFloat(EEP_ACC_BIAS + 8, mpu.getAccBias(2));
    writeFloat(EEP_GYRO_BIAS + 0, mpu.getGyroBias(0));
    writeFloat(EEP_GYRO_BIAS + 4, mpu.getGyroBias(1));
    writeFloat(EEP_GYRO_BIAS + 8, mpu.getGyroBias(2));
    writeFloat(EEP_MAG_BIAS + 0, mpu.getMagBias(0));
    writeFloat(EEP_MAG_BIAS + 4, mpu.getMagBias(1));
    writeFloat(EEP_MAG_BIAS + 8, mpu.getMagBias(2));
    writeFloat(EEP_MAG_SCALE + 0, mpu.getMagScale(0));
    writeFloat(EEP_MAG_SCALE + 4, mpu.getMagScale(1));
    writeFloat(EEP_MAG_SCALE + 8, mpu.getMagScale(2));
#if defined(ESP_PLATFORM) || defined(ESP8266)
    EEPROM.commit();
#endif
}

void loadCalibration() {
    Serial.println("Load calibrated parameters from EEPROM");
    if (isCalibrated()) {
        Serial.println("calibrated? : YES");
        Serial.println("load calibrated values");
        mpu.setAccBias(
            readFloat(EEP_ACC_BIAS + 0),
            readFloat(EEP_ACC_BIAS + 4),
            readFloat(EEP_ACC_BIAS + 8));
        mpu.setGyroBias(
            readFloat(EEP_GYRO_BIAS + 0),
            readFloat(EEP_GYRO_BIAS + 4),
            readFloat(EEP_GYRO_BIAS + 8));
        mpu.setMagBias(
            readFloat(EEP_MAG_BIAS + 0),
            readFloat(EEP_MAG_BIAS + 4),
            readFloat(EEP_MAG_BIAS + 8));
        mpu.setMagScale(
            readFloat(EEP_MAG_SCALE + 0),
            readFloat(EEP_MAG_SCALE + 4),
            readFloat(EEP_MAG_SCALE + 8));
    } else {
        Serial.println("calibrated? : NO");
        Serial.println("load default values");
        mpu.setAccBias(0., 0., 0.);
        mpu.setGyroBias(0., 0., 0.);
        mpu.setMagBias(0., 0., 0.);
        mpu.setMagScale(1., 1., 1.);
    }
}

void writeByte(int address, byte value) {
    EEPROM.put(address, value);
}

void writeFloat(int address, float value) {
    EEPROM.put(address, value);
}

byte readByte(int address) {
    byte valueIn = 0;
    EEPROM.get(address, valueIn);
    return valueIn;
}

float readFloat(int address) {
    float valueIn = 0;
    EEPROM.get(address, valueIn);
    return valueIn;
}

void clearCalibration() {
    writeByte(EEP_CALIB_FLAG, 0);
}

bool isCalibrated() {
    return (readByte(EEP_CALIB_FLAG) == 0x01);
}
