#pragma config(Sensor, S2,     light,           sensorLightInactive)
#pragma config(Sensor, S3,     sonar,          sensorSONAR)
#pragma config(Sensor, S4,     IRsense,          sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "drivers/LEGOUS-driver.h"
#include "rdpartyrobotcdr-v2.2/drivers/HTIRS2-driver.h";

int acS1,acS2,acS3,acS4,acS5;
int dcS1,dcS2,dcS3,dcS4,dcS5;

int n = 1;
int SonarValue;
int IRValue;
int LightValue;
bool LeftPressed;
bool RightPressed;

string acdc;

float oldy;

/*int round(float f)
{
  if(f>0) return (int)(f + 0.5);
  else    return (int)(f - 0.5);
} */

int GetStrongestSensor()
{
  int sensor;
  if(nNxtButtonPressed == kEnterButton)
  {
  HTIRS2readAllDCStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
  }
  else
  {
  HTIRS2readAllACStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
  }
  if(acS1>acS2 && acS1>acS3 && acS1>acS4 && acS1>acS5)
    sensor=1;
  if(acS2>acS1 && acS2>acS3 && acS2>acS4 && acS2>acS5)
    sensor=2;
  if(acS3>acS1 && acS3>acS2 && acS3>acS4 && acS3>acS5)
    sensor=3;
  if(acS4>acS1 && acS2>acS2 && acS2>acS3 && acS2>acS5)
    sensor=4;
  if(acS5>acS1 && acS2>acS2 && acS2>acS3 && acS2>acS4)
    sensor=5;
  return sensor;
}

	//if(abs(acS1-acS2)<20)
	//{
//	  sensor = acS1
	//}

int GetSensorStrength(int Sensor)
{
  if(nNxtButtonPressed == kEnterButton)
  {
  HTIRS2readAllDCStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
  acdc="(DC)";
  }
  else
  {
  HTIRS2readAllACStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
  acdc="(AC)";
  }
  //HTIRS2readAllDCStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5);
  int value;
  switch (Sensor)
    {
    case 1: value = acS1;
      break;

    case 2: value = (acS1 + acS2) / 2;
      break;

    case 3: value = acS2;
      break;

    case 4: value = (acS2 + acS3) / 2;
      break;

    case 5: value = acS3;
      break;

    case 6: value = (acS3 + acS4) / 2;
      break;

    case 7: value = acS4;
      break;

    case 8: value = (acS4 + acS5) / 2;
      break;

    case 9: value = acS5;
      break;

    case -1: return -1;
      break;
    }
  return value;
}

/*task GetIRSensorsStrength()
{
 while(true)
   {
     HTIRS2readAllACStrength(IRsense, acS1, acS2, acS3, acS4, acS5);
     sensorIR = HTIRS2readACDir(IRsense);
    }
}*/

task main()
{
  ClearTimer(T1);
  while(true)
  {
    if(n>100)
    {
      n=1;
      eraseDisplay();
    }
    //SonarValue=SensorValue(sonar);
    //IRValue = GetSensorStrength(GetStrongestSensor());
    IRValue = GetSensorStrength(4);

    //if(nNxtButtonPressed == kEnterButton)
      //acdc="(DC)";
   // else
      //acdc="(AC)";
    if(nNxtButtonPressed == kButtonLeft)
    {
      LeftPressed = true;
    }

    nxtDisplayTextLine(1, "Infrared %s: %d",acdc, IRValue);
    //float y = 64.00000*(IRValue/255.00);

    LightValue = SensorValue(light);

    float y = 64.00000*(LightValue/100.00);
    //nxtSetPixel(n,y);
    if(time100[T1]==1)
    {
      ClearTimer(T1);
      nxtDrawLine(n,oldy,n,y);
      n++;
    }
    nxtDisplayTextLine(2, "Light: %d", LightValue);
    /*if(oldy != y)
    {
    n++;
    oldy=y;
    }*/
  }
}
