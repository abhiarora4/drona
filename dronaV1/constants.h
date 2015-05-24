#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

//ULTRASONIC SENSORS
volatile float distance1;
volatile float distance2;

bool ultraShort1=false;
bool ultraShort2=false;

uint32_t schedulerBMP;

const int maximumRange = 70; // Maximum range needed
const float minimumRange = 3.00; // Minimum range needed
//pin 46 is paired with pin 2
//pin 44 is paired with pin 3

//IMU DATA
bool imu=false;

double accX1, accY1, accZ1;
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double gyroXrate;
double gyroYrate;
double gyroZrate;

Kalman kalmanX; 
Kalman kalmanY;

double gyroXangle, gyroYangle; 
double kalRoll, kalPitch; 
double compAngleX, compAngleY;

bool zero_ref=false;//becomes true when zero_ref of gyro, kalman angles are calculated

int16_t tempRaw;
uint32_t timer;
uint8_t i2cData[14];

double gyroRoll=0.0;
double gyroPitch=0.0;
double gyroYaw=0.0;

#endif // CONSTANTS_H_INCLUDED
