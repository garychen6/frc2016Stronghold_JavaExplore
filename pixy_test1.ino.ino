//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP port.  For more information go here:
//
// http://cmucam.org/projects/cmucam5/wiki/Hooking_up_Pixy_to_a_Microcontroller_(like_an_Arduino)
//
// It prints the detected blocks once per second because printing all of the 
// blocks for all 50 frames per second would overwhelm the Arduino's serial port.
//
   
#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;

void setup()
{
  pinMode(3, OUTPUT);   // sets the pin as output
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%10==0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      int valx;
      valx = pixy.blocks[0].x;
        if (valx < 150)
        {
          if (valx < 100)
          {
            digitalWrite(3, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(8, HIGH);
          }
          else
          {
            digitalWrite(3, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(8, LOW); 
          }
        }
        else if (valx > 170)
        {
          if (valx > 220)
          {
            digitalWrite(3, LOW);
            digitalWrite(4, HIGH);
            digitalWrite(8, HIGH);
          }
          else
          {
            digitalWrite(3, LOW);
            digitalWrite(4, HIGH);
            digitalWrite(8, LOW);
          }
        }
        else
        {
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(8, LOW);
        }


      int valy;
      valy = pixy.blocks[0].y;
        if (valy < 93)
        {
          if (valy < 76)
          {
            digitalWrite(5, HIGH);
            digitalWrite(6, LOW);
            digitalWrite(9, HIGH);
          }
          else
          {
            digitalWrite(5, HIGH);
            digitalWrite(6, LOW);
            digitalWrite(9, LOW); 
          }
        }
        else if (valy > 107)
        {
          if (valy > 124)
          {
            digitalWrite(5, LOW);
            digitalWrite(6, HIGH);
            digitalWrite(9, HIGH);
          }
          else
          {
            digitalWrite(5, LOW);
            digitalWrite(6, HIGH);
            digitalWrite(9, LOW);
          }
        }
        else
        {
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          digitalWrite(9, LOW);
        }
      Serial.print("x: ");
      Serial.print(valx);
      Serial.print("      y: ");
      Serial.println(valy);
      //Serial.println(pixy.blocks[0].x);
      //analogWrite(A0, pixy.blocks[0].x);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255

    }
  }  
}

