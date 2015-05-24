ISR(PCINT0_vect){
  static uint32_t start0[4];

  if(PCMSK0&(1<<PCINT4)){
    if(PINB&(1<<PB4))
    {
      start0[0]=micros();
    }
    else{
      PCMSK0=1<<PCINT5;
      chan[0]=(uint32_t)(micros()-start0[0]);
      frame_RC_time=start0[0]/1000;
      rx_detected=true;
    }
  }
  else if(PCMSK0&(1<<PCINT5)){
    if(PINB&(1<<PB5))
    {
      start0[1]=micros();
    }
    else{
      PCMSK0=1<<PCINT6;
      chan[2]=(uint32_t)(micros()-start0[1]);
    }
  }

  else if(PCMSK0&(1<<PCINT6)){
    if(PINB&(1<<PB6))
    {
      start0[2]=micros();
    }
    else{
      PCMSK0=1<<PCINT7;
      chan[4]=(uint32_t)(micros()-start0[2]);
    }
  }
  else if(PCMSK0&(1<<PCINT7)){
    if(PINB&(1<<PB7))
    {
      start0[3]=micros();
    }
    else{
      PCMSK0=1<<PCINT4;
      chan[6]=(uint32_t)(micros()-start0[3]);
    }
  }
}


ISR(PCINT2_vect){

  static uint32_t start2[4];
  if(PCMSK2&(1<<PCINT16)){
    if(PINK&(1<<PK0))
    {
      start2[0]=micros();
    }
    else{
      PCMSK2=1<<PCINT17;
      chan[1]=(uint32_t)(micros()-start2[0]);
      if(chan[1]<1000&&rx_detected)
        rx_functional=true;


    }
  }
  else if(PCMSK2&(1<<PCINT17)){
    if(PINK&(1<<PK1))
    {
      start2[1]=micros();
    }
    else{
      PCMSK2=1<<PCINT19;
      chan[3]=(uint32_t)(micros()-start2[1]);
    }
  }
  /*
  else if(PCMSK2&(1<<PCINT18)){
   if(PINK&(1<<PK2))
   {
   start2[2]=micros();
   }
   else{
   PCMSK2=1<<PCINT19;
   chan[5]=(uint32_t)(micros()-start2[2]);
   }
   }
   */
  else if(PCMSK2&(1<<PCINT19)){
    if(PINK&(1<<PK3))
    {
      start2[3]=micros();   
    }
    else{
      PCMSK2=1<<PCINT16;
      chan[7]=(uint32_t)(micros()-start2[3]);
      if(rx_functional)
        channelExtract();
    }
  }
}

void initRC(){

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    ADCSRA=0;
    ADCSRB=0;

    DIDR2=0;
    DIDR0=0;

    DDRB&=~((1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7));
    DDRK&=~((1<<PK0)|(1<<PK1)|(1<<PK2)|(1<<PK3));

    PCICR=(1<<PCIE0)|(1<<PCIE2);
    PCMSK0=1<<PCINT4;
    PCMSK2=1<<PCINT16;
  }
}


inline void channelExtract()
{
  xMotion=chan[2];
  yMotion=chan[0];
  //throtle=chan[2];
  throtle=compTx*throtle + (1-compTx)*chan[1];
  yawMotion=chan[3];
  toggleChan=chan[4];
  //cThrotle=chan[5];
  knob=compTx*knob+(1-compTx)*chan[6];
  knob=constrain(knob, 1000, 1800);
  modeSelect=chan[7];

  virtualSemaphore=2;
  vS1=1;

}

void ReceiverCaution()
{

  if(!toggle)
  {
    static bool one=false;
    if(uint32_t(millis()-frame_RC_time)>1000)
    {
      rx_detected=false;
      rx_functional=false;
      //motorArm();
    }

    if(zero_ref&&rx_initial)
    {
      while(!rx_detected);
      static boolean one=true;
      while(!rx_functional)
      {
        if(one)
        {
          terminal.println("rx problem");
          one=false;
        }
      }
      rx_initial=false;
      //connectionRC=true;

      PIDrol_rate.reset();
      PIDpitch_rate.reset();
      PIDyaw_rate.reset();

      PIDrol_angle.reset();
      PIDpitch_angle.reset();
      previous_value=knob;
      

    }

  }


}

void calibration()
{
  if(calibration_tx)
  {
    static uint8_t i=0;
    
    static uint8_t previous_k[4]={0,0,0,0};
    static bool set=true;
    static double max_k=1.00;
    static bool one_time=false;
    static uint32_t knob_t;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    knob_t=knob; 
  }
    
    if(modeSelect>1600){
  
      if(one_time){
        set=true;
        
        for(int j=0;j<4;j++)
          previous_k[j]=k[j];
        i>2?i=0:i++;
        one_time=false;
      }
    }
    else{
      //Serial.println("break");
      previous_value=knob_t;
      set=false;
      one_time=true;
    }

    if(set==true){
      
      if(knob_t>previous_value+20)
      {
        k[i]=map(knob_t, previous_value, 1800, previous_k[i], max_k*100);
        //k[i]/=100.00;
      }
      else if(previous_value-20>knob_t)
      {
        k[i]=map(knob_t, 1000, previous_value, 0, previous_k[i]);
        //k[i]/=100.00;
      }
      //Serial.println(k[i]);
      
      switch(i){
        case 0:
          PIDrol_rate.SetTunings(k[0]/100, previous_k[1]/100 , 0.00);
          PIDpitch_rate.SetTunings(k[0]/100, previous_k[1]/100 , 0.00);
          break;
        case 1:
          PIDrol_rate.SetTunings(previous_k[0]/100, k[1]/100 , 0.00);
          PIDpitch_rate.SetTunings(previous_k[0]/100, k[1]/100 , 0.00);
          break;
        case 2:
          PIDrol_angle.SetTunings(k[2]/100, previous_k[3]/100 , 0.00);
          PIDpitch_angle.SetTunings(k[2]/100, previous_k[3]/100 , 0.00);
          break;
          
        case 3:
          PIDrol_angle.SetTunings(previous_k[2]/100, k[3]/100 , 0.00);
          PIDpitch_angle.SetTunings(previous_k[2]/100, k[3]/100 , 0.00);
          break;
      }
    }
    /*
    double set_kp_1, set_kd_1;
     set_kp_1=map(int(Chan3_width),1050,1800,0,500);
     set_kp_1=set_kp_1/(100.00);
     
     set_kd_1=map(int(Chan4_width),1060,1800,0,200);
     set_kd_1=set_kd_1/(100.00);
     
     set_kp=0.95*set_kp+0.05*set_kp_1;
     set_kd=0.95*set_kd+0.05*set_kd_1;
     if(set_kp<0)
     set_kp= -set_kp;
     
     if(set_kd<0)
     set_kd= - set_kd;
     
     PIDrol_angle.SetTunings(set_kp, 0.00 , 0.00);
     PIDpitch_angle.SetTunings(set_kd, 0.00, 0.00);
     */
  }
}

void translational_motion()
{
  if(translational==true)
  {
    static double maxi=100.00;
    static double maxYaw=10.00;
    if(xMotion<=1450&&xMotion>=1350)
    {
      rolling=0.00;
    }
    else if(xMotion>1450)
    {
      rolling=map(int(xMotion),1450,1800,0,int(maxi*100));
      rolling=constrain(rolling,-int(maxi*100),int(maxi*100));
      rolling=rolling/(100.00);

    }
    else if(xMotion<1350)
    {
      rolling=map(int(xMotion),1050,1350,-int(maxi*100),0);
      rolling=constrain(rolling,-int(maxi*100),int(maxi*100));
      rolling=rolling/(100.00);

    }


    if(yMotion<=1450&&yMotion>=1350)
    {
      pitching=0.00;
    }
    else if(yMotion>1450)
    {
      pitching=map(int(yMotion),1450,1800,0,int(maxi*100));
      pitching=constrain(pitching,-int(maxi*100),int(maxi*100));
      pitching=pitching/(100.00);
    }
    else if(yMotion<1350)
    {
      pitching=map(int(yMotion),1050,1350,-int(maxi*100),0);
      pitching=constrain(pitching,-int(maxi*100),int(maxi*100));
      pitching=pitching/(100.00);
    }

    if(yawMotion<=1450&&yawMotion>=1350)
    {
      yawing=0.00;
    }
    else if(yawMotion>1450)
    {
      yawing=map(int(yawMotion),1450,1800,0,int(maxYaw*100));
      yawing=constrain(yawing,-int(maxYaw*100),int(maxYaw*100));
      yawing=yawing/(100.00);
    }
    else if(yawMotion<1350)
    {
      yawing=map(int(yawMotion),1050,1350,-int(maxYaw*100),0);
      yawing=constrain(yawing,-int(maxYaw*100),int(maxYaw*100));
      yawing=yawing/(100.00);
    }
  }
}











