void FlightController()
{

  if(toggleChan<1200)
  {
    //motorArm();

    if(!toggle)
    {
      toggle=true;
      if(eprom_wrte==true)
      {
        Serial.println("Saving Variables in EPROM");
        eprom_write_routine();
      }
      terminal.println("toggle");
    }
  }

  else if(toggleChan>1500 &&toggle==true )
  {
    resetVirtual();
    //resetFunc();
  }

  else
  {
    
  }


  if(!toggle && zero_ref &&rx_functional)
  {
    calibration();

    translational_motion();

    if(pid_angle==true)
    {
      out_angle_x=PIDrol_angle.ComputeFixedHz(compAngleX, zero_angle_roll,20,-rolling);
      out_angle_y=PIDpitch_angle.ComputeFixedHz(compAngleY, zero_angle_pitch,20, pitching);
    }

    if(pid_rate_angle==false)

    {
      out_rate_x=PIDrol_rate.Compute(gyroRoll,zero_rate_roll);
      out_rate_y=PIDpitch_rate.Compute(gyroPitch, zero_rate_pitch);
      out_rate_z=PIDyaw_rate.Compute(gyroYaw, zero_rate_yaw);
    }
    else if(pid_angle==true)
    {
      out_rate_x=PIDrol_rate.Compute(gyroRoll,zero_rate_roll, out_angle_x);
      out_rate_y=PIDpitch_rate.Compute(gyroPitch, zero_rate_pitch, out_angle_y);
      out_rate_z=PIDyaw_rate.Compute(gyroYaw, zero_rate_yaw);
    }

    //motor output   
    uint16_t s1=constrain(throtle - int(out_rate_y) + int(out_rate_z),1000,1800);
    uint16_t s2=constrain(throtle - int(out_rate_x) - int(out_rate_z),1000,1800);
    uint16_t s3=constrain(throtle + int(out_rate_y) + int(out_rate_z),1000,1800);
    uint16_t s4=constrain(throtle + int(out_rate_x) - int(out_rate_z),1000,1800);
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
  sm1(s1);
  sm2(s2);
  sm3(s3);
  sm4(s4);
  }
/*
    sm1.writeMicroseconds(constrain(throtle + int(out_rate_y) - int(out_rate_z),1000,1800));
    sm2.writeMicroseconds(constrain(throtle - int(out_rate_x) + int(out_rate_z),1000,1800));
    sm3.writeMicroseconds(constrain(throtle - int(out_rate_y) - int(out_rate_z),1000,1800));
    sm4.writeMicroseconds(constrain(throtle + int(out_rate_x) + int(out_rate_z),1000,1800));
*/
    //debug
    #ifndef serial
    if((millis()-xbee_frame_sent_time)>100){
    
      xbee_frame_sent_time=millis();
    #endif
      debug();
    #ifndef serial
    }
    #endif    
  }
  
  else if(toggle && rx_functional){
    motorArm();
  }
  
  else if(toggle&&!rx_functional){
    motorArm();
  }
  else if(!rx_functional){
    motorArm();
  }


}












