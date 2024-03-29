#include "Arduino.h"
#include "mpu9250.h"
#include "MPU9250.h"
#include <Adafruit_AHRS_Madgwick.h>

bfs::Mpu9250 mpu;
Adafruit_Madgwick filter;

// unit of acc [m/s2], gyro [deg/s], angle [deg]
float pitch_angle;
float pitch_angular_v;
float speed_x;
float yaw_angular_v;
float aX, aY, aZ, gX, gY, gZ;
float accErrorX = 0.19641, accErrorY = 0.42531, accErrorZ = -0.16247;
float gyroErrorX = -0.04489, gyroErrorY = -0.07271, gyroErrorZ = 0.01201;
float previousTime = 0, currentTime = 0, elaspTime = 0;
float sampleRate = 17.45;       // sampleRate = 1/((1/1000+中斷時間)(57.2958))

// initial
void MPU9250_init() {
  /* Serial to display data */
  Serial.begin(115200);
  while(!Serial) {}
  /* Start the I2C bus */
  Wire.begin();
  Wire.setClock(400000);
  /* I2C bus,  0x68 address */
  mpu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);
  /* Initialize and configure IMU */
  if (!mpu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {}
  }
  /* Set the sample rate divider */
  if (!mpu.ConfigSrd(0)) {                   //imu freguency = 1000/(function_input+1) function_input = 0
    Serial.println("Error configured SRD");
    while(1) {}
  }
  //calibrateIMU();
  filter.begin(sampleRate);
  previousTime = millis();
}

// update speed_x, pitch_angular_v, pitch_angle, yaw_angular_v
void MPU9250_updata() {
  currentTime = millis();
  mpu.Read();
  elaspTime = (currentTime - previousTime)/1000;
  previousTime = currentTime;
  aX = (mpu.accel_x_mps2() - accErrorX) / 10;
  aY = (mpu.accel_y_mps2() - accErrorY) / 10;
  aZ = (mpu.accel_z_mps2() - accErrorZ) / 10;
  gX = mpu.gyro_x_radps() - gyroErrorX;
  gY = mpu.gyro_y_radps() - gyroErrorY;
  gZ = mpu.gyro_z_radps() - gyroErrorZ;
  filter.updateIMU(gX, gY, gZ, aX, aY, aZ);
  speed_x = -(aX*elaspTime*10);            //向前是正
  pitch_angular_v = gY * RtoD;     //向前傾斜角度是正
  pitch_angle = filter.getPitch();   
  yaw_angular_v = -gZ * RtoD;      //向右轉是正
}

// print acc,gyro,pitch
void MPU9250_test(){
  Serial.println("ax,ay,az,gx,gy,gz,pitch");
  Serial.print(mpu.accel_x_mps2());
  Serial.print("\t");
  Serial.print(mpu.accel_y_mps2());
  Serial.print("\t");
  Serial.print(mpu.accel_z_mps2());
  Serial.print("\t");
  Serial.print(mpu.gyro_x_radps()*RtoD);
  Serial.print("\t");
  Serial.print(mpu.gyro_y_radps()*RtoD);
  Serial.print("\t");
  Serial.print(mpu.gyro_z_radps()*RtoD);
  Serial.print("\t");
  Serial.print(filter.getPitch());
  Serial.println("");
}

// update Bias(XXXError)
void calibrateIMU() {

  Serial.println("Start Calibrate.Please don't move imu");

  bool judge = 0;
  while (1) {
    int times = 0;
    float accErX = 0;
    float accErY = 0;
    float accErZ = 0;
    float gyroErX = 0;
    float gyroErY = 0;
    float gyroErZ = 0;

    // get mean value
    while (times < 300) {
      mpu.Read();
      accErX += (mpu.accel_x_mps2() - accErrorX);
      accErY += (mpu.accel_y_mps2() - accErrorY);
      accErZ += (mpu.accel_z_mps2() - accErrorZ);
      gyroErX += (mpu.gyro_x_radps() - gyroErrorX);
      gyroErY += (mpu.gyro_y_radps() - gyroErrorY);
      gyroErZ += (mpu.gyro_z_radps() - gyroErrorZ);
      times++;
      delay(3);
    }

    accErX = accErX / 300;
    accErY = accErY / 300;
    accErZ = (accErZ / 300);
    gyroErX = gyroErX / 300;
    gyroErY = gyroErY / 300;
    gyroErZ = gyroErZ / 300;

    // judge mean value error
    judge = (abs(accErX) > 0.01 || abs(accErY) > 0.01 || abs(accErZ + 10) > 0.01 || abs(gyroErX) > 0.001 || abs(gyroErY) > 0.001 || abs(gyroErZ) > 0.001);

    Serial.println(accErX, 3);
    Serial.println(accErY, 3);
    Serial.println(accErZ, 3);
    Serial.println(gyroErX, 5);
    Serial.println(gyroErY, 5);
    Serial.println(gyroErZ, 5);
    Serial.println("Calibrating");

    if (judge) {
      accErrorX += accErX;
      accErrorY += accErY;
      accErrorZ += (accErZ + 10);
      gyroErrorX += gyroErX;
      gyroErrorY += gyroErY;
      gyroErrorZ += gyroErZ;
    } else break;
  }

  Serial.println("Calibrate Done");

  Serial.print("accelerometerErrorX:");
  Serial.println(accErrorX, 5);
  Serial.print("accelerometerErrorY:");
  Serial.println(accErrorY, 5);
  Serial.print("accelerometerErrorZ:");
  Serial.println(accErrorZ, 5);
  Serial.print("gyroErrorX:");
  Serial.println(gyroErrorX, 5);
  Serial.print("gyroErrorY:");
  Serial.println(gyroErrorY, 5);
  Serial.print("gyroErrorZ:");
  Serial.println(gyroErrorZ, 5);

  delay(3000);
}