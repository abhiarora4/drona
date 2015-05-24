void mpu()
{
  if(imu==false)
  {
    terminal.println("imu disconnected");
  }
  
  while (i2cRead(0x3B, i2cData, 14));

  accX1 = ((i2cData[0] << 8) | i2cData[1]) /*+ 2000.0*/;
  accY1 = ((i2cData[2] << 8) | i2cData[3]) /*+ 3319.84*/;
  accZ1 = ((i2cData[4] << 8) | i2cData[5])  /* + 664.48*/;
  tempRaw = (i2cData[6] << 8) | i2cData[7];
  gyroX = (i2cData[8] << 8) | i2cData[9];
  gyroY = (i2cData[10] << 8) | i2cData[11];
  gyroZ = (i2cData[12] << 8) | i2cData[13];
  
  accX1*= (Gain_accel_x/scale_accel8);
  accY1*= (Gain_accel_y/scale_accel8);
  accZ1*= (Gain_accel_z/scale_accel8);

  accX=(compAcc*accX + (1 - compAcc)*(accX1))/100.00;
  accY=(compAcc*accY + (1 - compAcc)*(accY1))/100.00;
  accZ=(compAcc*accZ + (1 - compAcc)*(accZ1))/100.00;

  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();

  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;

  
  
  gyroXrate = gyroX /scale_gyro1000; // Convert to deg/s
  gyroYrate = gyroY / scale_gyro1000; // Convert to deg/s
  gyroZrate = gyroZ /scale_gyro1000;
  
  gyroRate();

  if ((roll < -90 && kalRoll > 90) || (roll > 90 && kalRoll < -90)) 
  {
    kalmanX.setAngle(roll);

    kalRoll = roll;
    gyroXangle = roll;
  } 
  else
    kalRoll = kalmanX.getAngle(roll, gyroRoll, dt); 

  if (abs(kalRoll) > 90)
  {
    kalPitch = kalmanY.getAngle(pitch, -gyroPitch, dt);
    gyroYangle -= gyroPitch * dt;
  } 
  else
  {
     kalPitch = kalmanY.getAngle(pitch, gyroPitch, dt);
     gyroYangle += gyroPitch * dt;
  }
 

  gyroXangle += gyroRoll * dt; 
  
  compAngleX = compAngle * (compAngleX + gyroRoll * dt) + (1-compAngle) * roll; // Calculate the angle using a Complimentary filter
  compAngleY = compAngle * (compAngleY + gyroPitch * dt) + (1-compAngle) * pitch;

  if (gyroXangle < -180 || gyroXangle > 180)
    gyroXangle = kalRoll;
  if (gyroYangle < -180 || gyroYangle > 180)
    gyroYangle = kalPitch;
}

void mpuIntialize()
{
  mode(); 

  //i2c scanner
  while (i2cRead(0x75, i2cData, 1));
  terminal.print("STATUS-");
  if (i2cData[0] != 0x68) 
  { 
    terminal.println(0);
    imu=false;
    resetFunc();

  }
  else
  {
    imu=true;
    terminal.println(1);
  }


  delay(100); // Wait for IMU sensor to stabilize

  while (i2cRead(0x3B, i2cData, 6));
  accX1 = (i2cData[0] << 8) | i2cData[1];
  accY1 = (i2cData[2] << 8) | i2cData[3];
  accZ1 = (i2cData[4] << 8) | i2cData[5];

  double roll  = atan2(accY1, accZ1) * RAD_TO_DEG;
  double pitch = atan(-accX1 / sqrt(accY1 * accY1 + accZ1 * accZ1)) * RAD_TO_DEG;

  kalmanX.setAngle(roll); 
  kalmanY.setAngle(pitch);
  gyroXangle = roll;
  gyroYangle = pitch;

  timer = micros();
}


void setAttitudeAndRate()
{
  if(!zero_ref)
  {
    if(millis()- timer_sp > 4000&&!(millis()- timer_sp > 7000))
    {
      /*
      zero_angle_roll=compAngleSet*zero_angle_roll + (1-compAngleSet)*kalRoll;
      zero_angle_pitch=compAngleSet*zero_angle_pitch + (1-compAngleSet)*kalPitch;
      */
      
      double alt = barometer.GetAltitude(seaLevelPressure);
      
      height=0.75*height + (1-0.75)*alt;
 
      zero_angle_roll=2.20;
      zero_angle_pitch=-0.59;
      zero_rate_roll=compRateSet*zero_rate_roll + (1-compRateSet)*gyroRoll;
      zero_rate_pitch=compRateSet*zero_rate_pitch + (1-compRateSet)*gyroPitch;
      zero_rate_yaw=compRateSet*zero_rate_yaw + (1-compRateSet)*gyroYaw;

    }

    else if(millis()- timer_sp > 7000)
    {
      zero_ref=true;
      zero_height=height;
    }
  }
}

void gyroRate()
{
  gyroRoll=(compGyroFilter*gyroRoll+(1-compGyroFilter)*gyroXrate);
  gyroPitch=(compGyroFilter*gyroPitch+(1-compGyroFilter)*gyroYrate);
  gyroYaw=(compGyroFilter*gyroYaw+(1-compGyroFilter)*gyroZrate);
}

