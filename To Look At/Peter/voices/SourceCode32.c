#pragma config(Sensor, S1,     IR,                  sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S2,     Sonar,               sensorSONAR)
#pragma config(Motor,  motorA,          motorL,        tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          motorR,        tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  while(true)
  {
      while( SensorValue(IR) < 5 && SensorValue(IR) > 0)
      {
        motor[motorR] = 2555;
      }
      while( SensorValue(IR) > 5)
      {
        motor[motorL] = 2555;
      }
      //if(!SensorValue(IR))
      while( SensorValue(IR) == 5)
      {
        motor[motorR] = 2555;
        motor[motorL] = 2555;
        if(SensorValue(Sonar) < 35)
        {
          //PlaySoundFile("ceps.rso");
        //PlaySound(soundFastUpwardTones);
        motor[motorR] = 0;
        motor[motorL] = 0;
          //PlaySound(soundFastUpwardTones);
        //PlaySoundFile("floor.rso");
        //PlaySoundFile("obstacle.rso");
        //PlaySoundFile("on.rso");
        //PlaySoundFile("is.rso");
        //PlaySoundFile("30.rso")
        //PlaySoundFile("4.rso");
        //PlaySoundFile("centimeters.rso");
        //PlaySoundFile("away.rso");
        }
      }
      motor[motorR] = 0;
      motor[motorL] = 0;
  }
}
