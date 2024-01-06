#ifndef __MPU9250_H__
#define __MPU9250_H__


#define RtoD 57.2958 // radians to degree: 180/pi

void MPU9250_init();
void MPU9250_updata();
void MPU9250_test();
void calibrateIMU();

#endif // __MPU9250_H__