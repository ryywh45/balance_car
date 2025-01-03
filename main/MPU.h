#ifndef __MPU_H__
#define __MPU_H__


#define RtoD 57.2958 // radians to degree: 180/pi

void MPU9250_init();
void MPU9250_updata();
void MPU9250_test();
void calibrateIMU();
void print_calibration();
void saveCalibration();
void loadCalibration();
void writeByte(int address, byte value);
void writeFloat(int address, float value);
byte readByte(int address);
float readFloat(int address);
void clearCalibration();
bool isCalibrated();

#endif // __MPU9250_H__