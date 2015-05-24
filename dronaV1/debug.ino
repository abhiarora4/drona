void debug()
{
#if gyro
  //terminal.print(gyroXrate); 
  //terminal.print("\t");
  terminal.print(gyroRoll); 
  terminal.print("\t");
  //terminal.print(gyroYrate); 
  //terminal.print("\t");
  terminal.print(gyroPitch); 
  terminal.print("\t");
  //terminal.print(gyroZrate); 
  //terminal.print("\t");
  //terminal.print(gyroYaw); 
 // terminal.print("\t");
#endif

#if bmp
  terminal.print(zero_height-height); 
  terminal.print("\t");
#endif

#if ultrasonic
  terminal.print(distance1);
  terminal.print("\t");
  terminal.print(distance2);
  terminal.print("\t");
#endif

#if acc
  terminal.print(accX); 
  terminal.print("\t");
  terminal.print(accY); 
  terminal.print("\t");
  terminal.print(accZ); 
  terminal.print("\t");
#endif


#if angle
  terminal.print(kalRoll); 
  terminal.print("\t");
  //terminal.print(kalPitch); 
  //terminal.print("\t"); 
  terminal.print(compAngleX); 
  terminal.print("\t"); 
  //terminal.print(compAngleY); 
  //terminal.print("\t"); 
#endif


#if calibrate
  terminal.print(k[0]/100); 
  terminal.print("\t");
  terminal.print(k[1]/100); 
  terminal.print("\t"); 
  terminal.print(k[2]/100); 
  terminal.print("\t"); 
  terminal.print(k[3]/100); 
  terminal.print("\t"); 
#endif

#if txrx
  terminal.print(xMotion);
  terminal.print("\t");
  terminal.print(yMotion);
  terminal.print("\t");
  terminal.print(throtle);
  terminal.print("\t");
  terminal.print(yawMotion);
  terminal.print("\t");
  terminal.print(toggleChan);
  terminal.print("\t");
  terminal.print(cThrotle);
  terminal.print("\t");
  terminal.print(knob);
  terminal.print("\t");
  terminal.print(modeSelect);
  terminal.print("\t");
  
#endif

#if chanPrint
for(int i=0;i<=7;i++)
  {
    terminal.print(chan[i]);
    terminal.print("\t");
  }
#endif

#if pid
  terminal.print(out_rate_x);
  terminal.print("\t");
  terminal.print(out_rate_y);
  terminal.print("\t");
  terminal.print(out_rate_z);
  terminal.print("\t");
  terminal.print(out_angle_x);
  terminal.print("\t");
  terminal.print(out_angle_y);
  terminal.print("\t");
#endif

#if outputsm
  terminal.print("sm1=");
  terminal.print(OCR3A);
  terminal.print("sm2=");
  terminal.print(OCR4A);
  terminal.print("sm3=");
  terminal.print(OCR4B);
  terminal.print("sm4=");
  terminal.print(OCR4C);
#endif

#if zero_reference
  terminal.print(zero_angle_roll); 
  terminal.print("\t"); 
  terminal.print(zero_angle_pitch); 
  terminal.print("\t");
  terminal.print(zero_rate_roll); 
  terminal.print("\t");
  terminal.print(zero_rate_pitch); 
  terminal.print("\t");
  //terminal.print(set_angle_roll); 
  //terminal.print("\t");
#endif

#if trans
terminal.print(rolling); 
  terminal.print("\t"); 
  terminal.print(pitching); 
  terminal.print("\t");
  terminal.print(yawing); 
  terminal.print("\t");
  
#endif


#if (zero_reference) || (outputsm) ||  (pid) ||  (gyro) || (acc) ||  (angle) || (txrx) || (chanPrint) || (trans) || (ultrasonic) ||(bmp) || (calibrate)
  terminal.print("\r\n");
#endif

}







