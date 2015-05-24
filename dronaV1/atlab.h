#ifndef ATLAB_H_INCLUDED
#define ATLAB_H_INCLUDED


class PID_ATLAB
{

public:

  PID_ATLAB(double, double, double, double=-500, double=500);

  double Compute(double input, double zero, double Setpoint=0.00);

  double ComputeFixedHz(double input, double zero, double sampletime, double Setpoint=0.00);

  void SetOutputLimits(double, double);

  void SetTunings(double, double, double);
  void reset();

private:

  double kp;
  double ki;
  double kd;
  int controllerDirection;

  unsigned long lastTime;
  double ITerm, lastInput;

  unsigned long SampleTime;
  double outMin, outMax;
  double output;

  double error;
  double SampleTimeInSec;
  double dInput;
  double lastDerivative;
  double derivative;

  // Low pass filter cut frequency for derivative calculation.
  // 20 Hz becasue anything over that is probably noise
  // Examples for _filter:
    // f_cut = 10 Hz -> _filter = 15.9155e-3
    // f_cut = 15 Hz -> _filter = 10.6103e-3
    // f_cut = 20 Hz -> _filter =  7.9577e-3
    // f_cut = 25 Hz -> _filter =  6.3662e-3
    // f_cut = 30 Hz -> _filter =  5.3052e-3

  static const uint8_t fCut = 7.9577e-3;

};


//ROLL RATE PID
double p_rol_rate = 0.6;
double i_rol_rate = 0.02;
double d_rol_rate = 0.0;

PID_ATLAB PIDrol_rate(p_rol_rate , i_rol_rate , d_rol_rate);
double out_rate_x;


//PITCH RATE PID
double p_pitch_rate = 0.6;
double i_pitch_rate = 0.02;
double d_pitch_rate = 0.00;

PID_ATLAB PIDpitch_rate(p_pitch_rate ,i_pitch_rate , d_pitch_rate);
double out_rate_y;


//YAW RATE PID
double p_yaw_rate = 1.0;
double i_yaw_rate = 0;
double d_yaw_rate = 0;

PID_ATLAB PIDyaw_rate(p_yaw_rate ,i_yaw_rate , d_yaw_rate);
double out_rate_z;


//ROLL ANGLE STABILIZE PID
double p_rol_angle = 0.4;
double i_rol_angle = 0.02;
double d_rol_angle = 0.0;

PID_ATLAB PIDrol_angle(p_rol_angle , i_rol_angle , d_rol_angle); 
double out_angle_x;


//PITCH ANGLE STABILIZE PID
double p_pitch_angle = 0.4;
double i_pitch_angle = 0.02;
double d_pitch_angle = 0.0;
PID_ATLAB PIDpitch_angle(p_pitch_angle ,i_pitch_angle , d_pitch_angle); 
double out_angle_y;


#endif // ATLAB_H_INCLUDED
