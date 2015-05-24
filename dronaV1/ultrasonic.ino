void init_ultra(){
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    //timer5 for ultrasonic sensors
    TCCR5A=(1<<COM5A1)|(1<<COM5C1);
    TCCR5B=(1<<CS51);

    TCCR5A|=(1<<WGM51);
    TCCR5B|=(1<<WGM52)|(1<<WGM53);

    ICR5=100000-1;
    OCR5A=19;
    OCR5C=19;

    DDRE&=~(1<<PE4);//PIN 2
    DDRL|=1<<PL3;//PIN 46

    DDRE&=~(1<<PE5);//PIN 2
    DDRL|=1<<PL5;//PIN 44

    //interrupts of PIN 2 
    EICRB=(1<<ISC40);
    EIMSK=(1<<INT4);//PIN 2

    //interrupts of PIN 3
    EICRB|=(1<<ISC50);
    EIMSK|=(1<<INT5);//PIN 2
  }
}

ISR(INT4_vect){
  static uint32_t t_ultra_1;
  if(PINE&(1<<PE4)){//PIN 2
    t_ultra_1=micros();
  }
  else{
    distance1=uint32_t(micros()-t_ultra_1);
    distance1=distance1/58.2;
    if(distance1<=minimumRange){
      ultraShort1=true;
    }
    else if(distance1 >= maximumRange){
      distance1=maximumRange;
    }
  }
}

ISR(INT5_vect){
  static uint32_t t_ultra;
  if(PINE&(1<<PE5)){//PIN 2
    t_ultra=micros();
  }
  else{
    distance2=uint32_t(micros()-t_ultra);
    distance2=distance2/58.2;
    if(distance2<=minimumRange){
      ultraShort2=true;
    }
    else if(distance2 >= maximumRange){
      distance2=maximumRange;
    }
  }
}
