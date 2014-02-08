#pragma config(Sensor, S1,     HTIRS2,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: HTIRS2-test1.c 48 2011-02-13 20:35:38Z xander $
 */

/**
 * HTIRS2-driver.h provides an API for the HiTechnic IR Seeker V2.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Partial rewrite by Dick Swan, waits a little longer for sensor initialisation<br>
 *        Nicer intro screen<br>
 *        Less screen flickering, only updated if there's been a change in data.
 * - 0.3: More comments
 * - 0.4: Driver renamed to HTIRS2, all functions have been renamed to HRIRS2
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * Dick Swan
 * 06 April 2010
 * version 0.4
 */

#include "drivers/HTIRS2-driver.h"

// global variables
long nNumbCyles;
long nInits = 0;
string sTextLines[8];

// function prototypes
void displayText(int nLineNumber, string cChar, int nValueDC, int nValueAC);
void displayInstructions();

// main task
task main ()
{
  int _dirDC = 0;
  int _dirAC = 0;
	int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
	int acS1, acS2, acS3, acS4, acS5 = 0;

	// the default DSP mode is 1200 Hz.
  tHTIRS2DSPMode _mode = DSP_1200;

  // show the user what to do
  displayInstructions();

  while(true)
  {
    // You can switch between the two different DSP modes by pressing the
    // orange enter button

    PlaySound(soundBeepBeep);
    while(bSoundActive)
    {}
    eraseDisplay();
    nNumbCyles = 0;
    ++nInits;
    while (true)
    {
      if ((nNumbCyles & 0x04) == 0)
        nxtDisplayTextLine(0, "Initializing...");
      else
        nxtDisplayTextLine(0, "");
      nxtDisplayCenteredBigTextLine(1, "IR Seekr");

      // set the DSP to the new mode
      if (HTIRS2setDSPMode(HTIRS2, _mode))
        break; // Sensor initialized

      ++nNumbCyles;
      PlaySound(soundShortBlip);
      nxtDisplayTextLine(4, "Inits: %d / %d", nInits, nNumbCyles);
      nxtDisplayCenteredTextLine(6, "Connect Sensor");
      nxtDisplayCenteredTextLine(7, "to Port S1");
      wait1Msec(100);
    }

    eraseDisplay();
    for (int i = 0; i < 8; ++i)
      sTextLines[i] = "";

    // display the current DSP mode
    if (_mode == DSP_1200)
      nxtDisplayTextLine(0, "      DC  1200");
    else
      nxtDisplayTextLine(0, "      DC   600");

    while (true)
    {
      ++nNumbCyles;
      if (nNxtButtonPressed == kEnterButton)
      {
        // "Enter" button has been pressed. Need to switch mode

        _mode = (_mode == DSP_1200) ?  DSP_600 : DSP_1200;
        while(nNxtButtonPressed == kEnterButton)
        {
          // Wait for "Enter" button release
        }
        break;
      }

      // Read the current non modulated signal direction
      _dirDC = HTIRS2readDCDir(HTIRS2);
      if (_dirDC < 0)
        break; // I2C read error occurred

      // read the current modulated signal direction
      _dirAC = HTIRS2readACDir(HTIRS2);
      if (_dirAC < 0)
        break; // I2C read error occurred

      // Read the individual signal strengths of the internal sensors
      // Do this for both unmodulated (DC) and modulated signals (AC)
      if (!HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5))
        break; // I2C read error occurred
      if (!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 ))
        break; // I2C read error occurred

      displayText(1, "D", _dirDC, _dirAC);
      displayText(2, "0", dcS1, acS1);
      displayText(3, "1", dcS2, acS2);
      displayText(4, "2", dcS3, acS3);
      displayText(5, "3", dcS4, acS4);
      displayText(6, "4", dcS5, acS5);
      nxtDisplayTextLine(7, "Enter to switch");
    }
  }
}

// Display the instructions to the user
void displayInstructions()
{
  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "IR Seekr");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Press enter to");
  nxtDisplayCenteredTextLine(6, "switch between");
  nxtDisplayCenteredTextLine(7, "600 and 1200 Hz");
  wait1Msec(2000);
}

// Minimize LCD screen flicker by only updating LCD when data has changed
void displayText(int nLineNumber, string cChar, int nValueDC, int nValueAC)
{
  string sTemp;

  StringFormat(sTemp, "%4d  %4d", nValueDC, nValueAC);
  // Check if the new line is the same as the previous one
  // Only update screen if it's different.
  if (sTemp != sTextLines[nLineNumber])
  {
    string sTemp2;

    sTextLines[nLineNumber] = sTemp;
    StringFormat(sTemp2, "%s:  %s", cChar, sTemp);
    nxtDisplayTextLine(nLineNumber, sTemp2);
  }
}

/*
 * $Id: HTIRS2-test1.c 48 2011-02-13 20:35:38Z xander $
 */
