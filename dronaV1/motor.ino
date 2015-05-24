void motorArm()
{
  sm1(1000);
  sm2(1000);
  sm3(1000);
  sm4(1000);
  /*
  sm1.writeMicroseconds(1000);
  sm2.writeMicroseconds(1000);
  sm3.writeMicroseconds(1000);
  sm4.writeMicroseconds(1000);
  */

}
void timerInitialize()
{
  
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
  TCCR3A=0x00;
  TCCR4A=0x00;
  TCCR3B=0x00;
  TCCR4B=0x00;
  TCCR3C=0x00;
  TCCR4C=0x00;

  TCCR3A=(1<<COM3A1)/*|(1<<COM3B1)|(1<<COM3C1)*/|(1<<WGM31);
  TCCR3B=(1<<CS31)|(1<<WGM32)|(1<<WGM33);

  TCCR4A=(1<<COM4A1)|(1<<COM4B1)|(1<<COM4C1)|(1<<WGM41);
  TCCR4B=(1<<CS41)|(1<<WGM42)|(1<<WGM43);

  TCNT3=0;
  ICR3=3999;
  OCR3A=1999;
  OCR3B=1999;
  OCR3C=1999;

  TCNT4=0;
  ICR4=3999;
  OCR4A=1999;
  OCR4B=1999;
  OCR4C=1999;
 }

}
