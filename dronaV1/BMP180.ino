void initBMP180(){
  barometer = BMP180();
  if(barometer.EnsureConnected())
  {
    //Serial.println("Connected to BMP180."); 
    barometer.SoftReset();
    barometer.Initialize();
    
    delay(1000);
    
    seaLevelPressure = barometer.GetPressure();
    barometer.SetResolution(0, false);

  }
  else
  { 
    //Serial.println("No sensor found.");
  }

}

void BMP180read(){
  if(barometer.IsConnected&&(millis()-schedulerBMP>20))
  {
    double altitude = barometer.GetAltitude(seaLevelPressure);
    height=compPressure*height + (1-compPressure)*altitude;
    schedulerBMP=millis();
  }

}
