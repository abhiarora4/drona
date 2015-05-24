void flipDetect(){
  if(abs(kalRoll-zero_angle_roll)>30)
  {
    flip=true;
  }
  else if(abs(kalPitch-zero_angle_pitch)>30)
    flip=true;
    
  
}

void instabilityDetect(){
  if(abs(gyroRoll-zero_rate_roll)>20)
    instability=true;
    
  else if(abs(gyroPitch-zero_rate_pitch)>20)
    instability=true;
}

void state_estimate(){
  if(throtle>1400&&if_state(rest)){
    state=1<<takeoff;
  }
  else if(throtle>1600&&if_state(takeoff)){
    state=1<<high;
  }


}
