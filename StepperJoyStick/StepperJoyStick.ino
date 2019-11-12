//This code will take information from a joystick
//potentiometer and relay it to turn the stepper
//motor clockwise and counterclockwise


#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

Servo myservo1;
Servo myservo2;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *Motor1 = AFMS.getStepper(200, 1);

Adafruit_StepperMotor *Motor2 = AFMS.getStepper(200, 2);

int stickY = A0;
int stickX = A1;
int angle = 90;
int altitude = 180;
void setup()
{

  myservo1.attach(10);
  myservo2.attach(9);
  //further research necessary
  //myStepper.setSpeed(10);//RPM
//    myStepper.setSpeed(10);
  Serial.begin(9600);
    AFMS.begin();
    Motor1->setSpeed(30);
    Motor2->setSpeed(30);
    myservo1.write(90);
    myservo2.write(180);
    
}

void loop()
{
//    Motor1->step(1, BACKWARD, SINGLE); 
//    Motor2->step(1, FORWARD, SINGLE); 
//if(angle == 180){
//    angle = 0;
//  }

  
//  angle++;
  
  //FORWARD MOVEMENT
  if (analogRead(stickY) < 300  & analogRead(stickX) > 300 & analogRead(stickX) < 700  ) {
    //Motor1->step(1, FORWARD, SINGLE); 
//    Motor2->step(1, FORWARD, SINGLE); 
    altitude+=2;
    myservo2.write(altitude);
    Serial.print("FORWARD");
    Serial.print("\n");
  }

  //BACKWARD MOVEMENT
  if (analogRead(stickY) > 700  & analogRead(stickX) > 300 & analogRead(stickX) < 700  ) {
    Serial.print("BACKWARD");
    Serial.print("\n");
    altitude-=2;
    myservo2.write(altitude);


  }

//  //TURN LEFT
  if (analogRead(stickY) < 700  & analogRead(stickY) > 300 & analogRead(stickX) < 300  ) {
    Serial.print("LEFT");
    Serial.print("\n");
    angle+=2;
    myservo1.write(angle);

  }

  //TURN RIGHT
  if (analogRead(stickY) < 700  & analogRead(stickY) > 300 & analogRead(stickX) > 700  ) {
    Serial.print("RIGHT");
    Serial.print("\n");
    angle-=2;
    myservo1.write(angle);
    

  }
//  IN NEUTRAL POSITION
//  if (analogRead(stickY) < 700  & analogRead(stickY) > 300 & analogRead(stickX) < 700 & analogRead(stickX) > 300  ) {
//    Motor1->release();
//    Serial.print("NEUTRAL");
//    Serial.print("\n");
//  }
  
delay(75); 
}
