//Main Arduino Script
#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

char input;
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
<<<<<<< HEAD
    input = Serial.readStringUntil('\n');  //reading string from serial
    Serial.println(input);
=======
    input = Serial.read();  //reading string from serial
>>>>>>> 601cac1f9a53ba232fb11fdcdc9a64b81923f018
  }
  
  //toggle speed 
  if(input == 0 && normalSpeed == true){//B button press
    delayAmt = 250;//slowing down from normal speed
  }else if(input == 0 && normalSpeed == false){
    delayAmt = 100;//speeding up from slowspeed
  }
  
  //move robot commands
  if(input == 2){//move 1 step FW
      Motor1->step(1, FORWARD, SINGLE); 
      Motor2->step(1, BACKWARD, SINGLE); 
      delay(delayAmt);
      
    }else if(input == 3){//move 1 step BW
      Motor2->step(1, FORWARD, SINGLE); 
      Motor1->step(1, BACKWARD, SINGLE);
      delay(delayAmt);
    }else if(input == 4){//Turn 1 step L
      Motor1->step(1, FORWARD, SINGLE); 
      Motor2->step(1, FORWARD, SINGLE);
      delay(delayAmt);
     
    }else if(input == 1){//Turn 1 step R
      Motor1->step(1, BACKWARD, SINGLE); 
      Motor2->step(1, BACKWARD, SINGLE);
      delay(delayAmt);

    }else if(input == 9){//stop moving FW or BW
      Motor1->release();
      Motor2->release();
      delay(delayAmt);
      
     //pan or tilt camera mount
    }else if (input == 5){//pan left
      //servo camera mount commands 
        panAngle += 3;
        panServo.write(panAngle);
        Motor1->release();
        Motor2->release();  
        delay(delayAmt);
    }else if (input == 6){//pan right
      //servo camera mount commands
        panAngle -= 3;
        panServo.write(panAngle); 
        Motor1->release();
        Motor2->release();
        delay(delayAmt); 
    }else if (input == 7){//tilt up
        tiltAngle -= 5;
        tiltServo.write(tiltAngle);
        Motor1->release();
        Motor2->release(); 
        delay(delayAmt);
    }else if (input == 8){//tilt down
        tiltAngle += 5;
        tiltServo.write(tiltAngle);
        Motor1->release();
        Motor2->release(); 
        delay(delayAmt);
    }

}
