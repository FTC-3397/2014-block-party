#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     sound1,          sensorSoundDBA)
#pragma config(Sensor, S4,     sound2,           sensorSoundDBA)
#pragma config(Motor,  motorA,          balls,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     right,         tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    crateLeftServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    crateRightServo,           tServoStandard)
#pragma config(Motor,  mtr_S1_C3_1,     scissor,       tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     crateLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     crateRight,    tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int snd1, snd2;
string dir;

int GetDir(int snd1, int snd2)
{
  //string dir;

  if(abs(snd1-snd2)>10)
  {
	  if(snd1>snd2)
	  {
	    dir = "left";
	  }
	  else
	  {
	    dir = "right";
	  }
	}
	else
	{
	  if(snd1>10 && snd2 >10)
	    dir = "center";
	  else
	    dir = "centerquiet";
	}/*
	if(snd1>20 && snd2>20)
	{
	  dir = "everywhere";
	}*/
	return 1/*r*/;
}

task main()
{
  wait10Msec(200);
  nVolume = 10;
  while(true && nNxtButtonPressed != kButtonCenter)
  {

    snd1 = SensorValue(sound1);
    snd2 = SensorValue(sound2);
    nxtDisplayTextLine(0,"SND1: %d  SND2: %d",snd1,snd2);
    nxtDisplayTextLine(2,"Diff: %d",abs(snd1-snd2));
    GetDir(snd1,snd2);
    nxtDisplayTextLine(4,"Sound is to the");
    nxtDisplayTextLine(5,"%s.",dir);
    /*if(dir=="everywhere")
    {
      PlaySoundFile("everywhere.rso");
	    wait10Msec(50);
	    ClearSounds();
	  }*/
    if(dir=="left")
	  {
	    //PlaySoundFile("left.rso");
	    //PlaySound(soundShortBlip);
	    //wait10Msec(50);
	    //ClearSounds();
	    motor[left] = -snd1/2;
	    motor[right] = snd1/2;
	  }
	  else if(dir=="right")
	  {
	    //PlaySound(soundBlip);
	    //PlaySoundFile("right.rso");
	    //wait10Msec(50);
	    //ClearSounds();
	    motor[left] = snd2/2;
	    motor[right] = -snd2/2;
	  }
	  else if(dir == "center")
	  {
	    motor[left] = (snd1+snd2)/4;
	    motor[right] = (snd1+snd2)/4;
	  }
	  else
	  {
	    motor[left] = 0;
	    motor[right] = 0;
	  }
  }
}
