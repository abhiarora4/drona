void eprom_write(double value)
{
  EEPROM.write(address, int(value));
  address++;
  double next = value - int(value);
  EEPROM.write(address, int(next*10));
  address++;
}

double eprom_read()
{
  double output1,output2;
  output2 = EEPROM.read(address);
  address++;
  output1 = EEPROM.read(address);
  output1=output2+(output1/10);
  address++;
  return output1;

}

void eprom_read_display()
{
  if(eprom_red==true)
  {
    address = 0;
    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);

    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);

    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);

    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);

    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);
    Serial.println(eprom_read());
    delay(4);



    while(1)
    {
      if(eprom_red)
      {
        Serial.println("END OF EPROM");
        eprom_red=false;
      }
      //motorArm();
    }
  }
}

void eprom_write_routine()
{
  //eprom_write(k[0]);
  //eprom_write(k[1]);
  //eprom_write(d_rol_rate);

  //eprom_write(p_pitch_rate);
  //eprom_write(i_pitch_rate);
  //eprom_write(d_pitch_rate);

  //eprom_write(p_yaw_rate);
  //eprom_write(i_yaw_rate);
  //eprom_write(d_yaw_rate);

  //eprom_write(k[2]);
  //eprom_write(k[3]);
  //eprom_write(d_rol_angle);

  //eprom_write(p_pitch_angle);
  //eprom_write(i_pitch_angle);
  //eprom_write(d_pitch_angle);
  address=0;
}
