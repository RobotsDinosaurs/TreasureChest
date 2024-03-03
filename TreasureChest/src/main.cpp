/*
    MagiQuest Treasure Chest controlled by the magic wand
    
    IR Receiver 
    IR Value equal to the value from the MagiQuest magic wand will activate the stepper motor.

    Stepper Motor 28BYJ-48
    Shaft of the stepper motor rotates quarter revolution clockwise, lights up the LEDs, then rotates back CCW.

    Connections (ULN2003 - ARDUINO):
    * IN1 --> 11
    * IN2 --> 10
    * IN3 --> 9
    * IN4 --> 8
    * VCC --> 5V
    * GND --> GND
 */

#include <Arduino.h>
#include <IRremote.hpp>
#include <Stepper.h>

const int IR_RECEIVE_PIN = 7;
const int LED_PIN = 3;
const int stepsPerRevolution = 500;

// initialize the stepper library on pins 8 through 11 (mind the order!)
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 
  myStepper.setSpeed(15);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  if (IrReceiver.decode()) 
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);

    switch(IrReceiver.decodedIRData.decodedRawData)
    {
      //MagiQuest wand
      case 0x4392E281: 
        Serial.println("open box");
        myStepper.step(stepsPerRevolution);
        digitalWrite(LED_PIN, HIGH);
        delay(7000);
        digitalWrite(LED_PIN, LOW);
        Serial.println("close box");
        myStepper.step(-stepsPerRevolution);
        break;
      default:
        break;
    }

    IrReceiver.resume(); // Enable receiving of the next value
  }
}