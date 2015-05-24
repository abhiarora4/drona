void resetVirtual()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    motorArm();
    terminal.println(VERSION);

    throtle=1000;
    toggleChan=1800;

    //rx_detected = false;
    rx_functional=false;
    //rx_frame_gap = 0;
    /*
  ppm[0]=0;
     ppm[1]=0;
     ppm[2]=0;
     ppm[3]=0;
     ppm[4]=0;
     ppm[5]=0;
     ppm[6]=0;
     ppm[7]=0;
     */

    chan[0]=0;
    chan[1]=0;
    chan[2]=0;
    chan[3]=0;
    chan[4]=0;
    chan[5]=0;
    chan[6]=0;
    chan[7]=0;

    gyroRoll=0.0;
    gyroPitch=0.0;
    gyroYaw=0.0;

    accX=0.00;
    accY=0.00;
    accZ=0.00;

    set_angle_roll=0.00;
    set_angle_pitch=0.00;

    zero_angle_roll=0.00;
    zero_angle_pitch=0.00;

    zero_rate_roll=0.00;
    zero_rate_pitch=0.00;
    zero_rate_yaw=0.00;

    out_rate_x=0.00;
    out_rate_y=0.00;
    out_rate_z=0.00;

    //pid_rate=false;
    //pid_set=false;

    // connectionRC = false;
    rx_initial=true;


    ultraShort1=false;
    ultraShort2=false;


    toggle=false;
    zero_ref=false;
    delay(100);

    timer_sp = millis();
  }
}





