//This code will take information from a joystick
//potentiometer and relay it to turn the stepper
//motor clockwise and counterclockwise


#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *Motor1 = AFMS.getStepper(200, 1);

Adafruit_StepperMotor *Motor2 = AFMS.getStepper(200, 2);


void setup()
{


  //further research necessary
  //myStepper.setSpeed(10);//RPM
//    myStepper.setSpeed(10);
  Serial.begin(9600);
    AFMS.begin();
    Motor1->setSpeed(60);
    Motor2->setSpeed(30);
}

void loop()
{
//
//  Motor1->step(100, FORWARD, SINGLE); 
//  delay(500);
//  Motor1->step(100, BACKWARD, SINGLE); 
//  delay(500);
  
    Motor2->step(1, FORWARD, SINGLE); 
    delay(50);
//    Motor2->step(1, BACKWARD, SINGLE); 
//    delay(500);
    
//  Serial.print("Y-Val:");
//  Serial.print(analogRead(stickY));
//  Serial.print("\n");
//  Serial.print("X-Val:");
//  Serial.print(analogRead(stickX));
//  Serial.print("\n");
//
//  if (analogRead(stickY) < 300  & analogRead(stickX) > 300 & analogRead(stickX) < 700  ) {
//    myStepper.step(-100); //backwards
//    Serial.print("Backward");
//    Serial.print("\n");
//  }
//
//  if (analogRead(stickY) > 700  & analogRead(stickX) > 300 & analogRead(stickX) < 700  ) {
//    myStepper.step(100); //forwards
//    Serial.print("Forward");
//    Serial.print("\n");
//
//
//  }
//  else {
//
//    Serial.print("NEUTRAL");
//    Serial.print("\n");
//  }
//delay(500); //may comment out and use setSpeed to a low RPM
}
