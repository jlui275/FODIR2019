//Main Arduino Script
#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

String input;
bool normalSpeed = true;
int delayAmt = 100;


Servo panServo;
Servo tiltServo;
int panAngle = 90;
int tiltAngle = 180;


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *Motor1 = AFMS.getStepper(200, 1);

Adafruit_StepperMotor *Motor2 = AFMS.getStepper(200, 2);

void setup(){
  Serial.begin(9600);
    AFMS.begin();
    Motor1->setSpeed(30);
    Motor2->setSpeed(30);

  
  panServo.attach(9);
  tiltServo.attach(10);
  panServo.write(panAngle);//starts in middle
  tiltServo.write(tiltAngle);//starts fully upright so the camera is facing forward
}

void loop(){
  
  if(Serial.available()){         //From RPi to Arduino
    input = Serial.readString();  //reading string from serial
  }
  
  //toggle speed 
  if(input == "B" && normalSpeed == true){
    delayAmt = 250;//slowing down from normal speed
  }else if(input == "B" && normalSpeed == false){
    delayAmt = 100;//speeding up from slowspeed
  }
  
  //move robot commands
  if(input == "Left Joystick Forward"){//move 1 step FW
      Motor1->step(1, FORWARD, SINGLE); 
      Motor2->step(1, BACKWARD, SINGLE); 
      delay(delayAmt);
      
    }else if(input == "Left Joystick Backward"){//move 1 step BW
      Motor2->step(1, FORWARD, SINGLE); 
      Motor1->step(1, BACKWARD, SINGLE);
      delay(delayAmt);
    }else if(input == "Left Joystick Left"){//Turn 1 step L
      Motor1->step(1, FORWARD, SINGLE); 
      Motor2->step(1, FORWARD, SINGLE);
      delay(delayAmt);
     
    }else if(input == "Left Joystick Right"){//Turn 1 step R
      Motor1->step(1, BACKWARD, SINGLE); 
      Motor2->step(1, BACKWARD, SINGLE);
      delay(delayAmt);

    }else if(input == "Stop Move"){//Turn 1 step R
      Motor1->release();
      Motor2->release();
      delay(delayAmt);
      
     //pan or tilt camera mount
    }else if (input == "Right Joystick Left"){
      //servo camera mount commands 
        panAngle += 3;
        panServo.write(panAngle);
        Motor1->release();
        Motor2->release();  
        delay(delayAmt);
    }else if (input == "Right Joystick Right"){
      //servo camera mount commands
        panAngle -= 3;
        panServo.write(panAngle); 
        Motor1->release();
        Motor2->release();
        delay(delayAmt); 
    }else if (input == "Right Joystick Up"){
        tiltAngle -= 5;
        tiltServo.write(tiltAngle);
        Motor1->release();
        Motor2->release(); 
        delay(delayAmt);
    }else if (input == "Right Joystick Down"){
        tiltAngle += 5;
        tiltServo.write(tiltAngle);
        Motor1->release();
        Motor2->release(); 
        delay(delayAmt);
    } 

}
