#include <Wire.h>
#include <BMP180.h>
#include <EEPROM.h>
#include "Kalman.h"
#include "constants.h"
#define VERSION "QuadPlus4_4"

#include "atlab.h"
#include <util/atomic.h>

//x corresponds to roll
//y corresponds to pitch
//z corresponds to yaw

//sm1.attach(5);
//sm2.attach(6);
//sm3.attach(7);
//sm4.attach(8);

//TERMINAL FOR DEBUGGING SELECT
#define serial //serial

#if defined serial
#define terminal Serial
#else
#define terminal Serial3
#endif



//DEBUGING
#define txrx 0
#define chanPrint 0
#define angle 0
#define gyro 0
#define pid 0
#define acc 0
#define outputsm 0
#define zero_reference 0
#define trans 0
#define ultrasonic 0
#define bmp 0
#define calibrate 1


//STATE MACHINE
char state;
enum state_m {rest=0, takeoff=1, high=2, landing=3, landed=4, unstable=5};
#define if_state(x) ((1<<x)&&state)


//EPROM
int address=0;
boolean eprom_wrte=false;
boolean eprom_red=false;

//IMU DATA
#define scale_gyro2000	16.4		// Scale gyro +/- 2000º/s
#define scale_gyro1000	32.8		// Scale gyro +/- 1000º/s
#define scale_gyro500	65.5		// Scale gyro +/- 500º/s
#define scale_gyro250	131.0		// Scale gyro +/- 250º/s

#define Gain_accel_z      1.0/1.042			// 1.042 Gravity Z raw reader
#define Gain_accel_x      1.0/1.007			// 1.007 Gravity X raw reader
#define Gain_accel_y      1.0				// 1.000 Gravity Y raw reader
#define scale_accel16	2048				// Scale Accel +/- 16 G
#define scale_accel8	4096				// Scale Accel +/- 8 G
#define scale_accel4	8192				// Scale Accel +/- 4 G

//setpoint
unsigned long timer_sp;
double set_angle_roll=0.00;
double set_angle_pitch=0.00;

//Interrupts	int.0	int.1	int.2	int.3	int.4	int.5
//Mega2560	 2	  3	  21	  20	  19	  18 --->WORKS WITH attachInterrupt() function of arduino mega only!
//ATMEGA 2560    21      20       19      18      2      3
                
//TX-RX 
//Connections to the arduino pins of various channels of the Receiver
/*
CHANNEL 1-PIN10
CHANNEL 2-PIN11
CHANNEL-3 - PK0 - ANALOG8
CHANNEL 4-PK1 - ANALOG9
CHANNEL-5 - PIN12
CHANNEL 6-PK2 - ANALOG10
CHANNEL-7 -PIN13
CHANNEL 8-PK3-ANALOG11
*/

boolean rx_initial=true;

volatile uint32_t chan[10]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

volatile boolean rx_detected = false;
volatile boolean rx_functional=false;
volatile uint32_t frame_RC_time;

volatile uint8_t virtualSemaphore=2;
volatile bool vS1=1;

uint16_t xMotion;
uint16_t yMotion;
uint16_t throtle=1000;
uint16_t yawMotion;
uint16_t toggleChan=1800;
uint16_t cThrotle;
uint16_t knob;
uint16_t modeSelect;

float k[4]={0, 0, 0, 0};
uint16_t previous_value=1000;
//RESET FUNCTION
void(* resetFunc) (void) = 0;

//BMP180
double height;

BMP180 barometer;
float seaLevelPressure = 101325;


//COMPLEMENTARY FILTER
const double compTx=0.85;
const double compAngleSet=0.95;
const double compRateSet=0.95;
const double compGyroFilter=0.80;
const double compAcc=0.80;
const double compAngle=0.95;
const double compPressure=0.95;



//MOTOR
//SERVO VARIABLES
uint16_t minServo=1999;
uint16_t maxServo=3599;
uint16_t maxFrameServo=3999;

//5-OCR3A ---sm1
//6-OCR4A ---sm2
//7-OCR4B ---sm3
//8-OCR4C ---sm4

#define sm1(x) (x>1000?(x<1800?OCR3A=((x*2)-1):OCR3A=3599):OCR3A=1999)
#define sm2(x) (x>1000?(x<1800?OCR4A=((x*2)-1):OCR4A=3599):OCR4A=1999)
#define sm3(x) (x>1000?(x<1800?OCR4B=((x*2)-1):OCR4B=3599):OCR4B=1999)
#define sm4(x) (x>1000?(x<1800?OCR4C=((x*2)-1):OCR4C=3599):OCR4C=1999)

//Servo sm1, sm2, sm3, sm4;

boolean toggle=false;


//XBEE
volatile uint16_t xbee_frame_sent_time = 0;

//REQUIRES ATTENTION-----------------------------------------------------------------------------------------------------------------


boolean calibration_tx=true;
boolean translational=true;
double rolling=0;
double pitching=0;
double yawing=0;

boolean pid_rate_angle = true;
boolean pid_angle=true;
//END--------------------------------------------------------------------------------------------------------------------------------

//PID_ATLAB CLASS

//PID VARIABLES

double zero_angle_roll;
double zero_angle_pitch;

double zero_rate_roll;
double zero_rate_pitch;


double zero_rate_yaw;

double zero_height;

//set_kp_ki_kd
double set_kp;
double set_kd;


//------------------------Self Monitorin Functions Area(Ultrasonics Sensors, State Control, Flip and Instabillity Detection)--------
bool flip=false;
bool instability=false;

void setup() 
{
  
  timerInitialize();
  
  terminal.begin(115200);
  
  #ifndef serial
    intFlowControlXbee(); //attachInterrupt(4, control, CHANGE);
  #endif
  
  Wire.begin();

  terminal.println(VERSION);

  mpuIntialize();
  /*
  sm1.attach(2);
  sm2.attach(3);
  sm3.attach(5);
  sm4.attach(6);
  */

  motorArm();

  //ppmInitialize();
  initRC();
  init_ultra();
  
  initBMP180();
  
  k[0]=p_rol_rate*100;
  k[1]=i_rol_rate*100;
  k[2]=p_rol_angle*100;
  k[3]=i_rol_angle*100;
  delay(1000);
  timer_sp = millis();

}

void loop() 
{

  eprom_read_display();
  mpu();

  setAttitudeAndRate();
  //calculateAcc();
  //calculating velocity();
  //setting PID constants through tx

  //calibration();
  //translational_motion();

  //instabilityDetect();
  //flipDetect();

  ReceiverCaution();
  FlightController();
  
  BMP180read();
  //state_estimate();
  

}





