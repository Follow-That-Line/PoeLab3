#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// set up the two motor variables
Adafruit_DCMotor *motor1 = AFMS.getMotor(3);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);
int athreshold = 3;
int bthreshold = 950;
int stop = 0;


void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps

  AFMS.begin();  // create with the default frequency 1.6KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  // make sure the motor is stopped to start
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  // set up the LEDs for the sensors
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);


}

void loop(){

    if(Serial.available() >= 0) {
      stop = Serial.read();
    }
    else{
      stop = 0;
    }
    
    delayMicroseconds(500);
    
    int a=analogRead(A0);
    int b=analogRead(A1);
    int speed = 100;
    
    //Serial.println(a); 
    if (stop == 1){
      stopAllMotors();
    }
    else if (b<bthreshold && a>athreshold){
      moveForward(speed);
    }
    else if(b<bthreshold && a<athreshold){
      moveForward(speed);
      delayMicroseconds(1000);
      if(b>bthreshold && a>athreshold){
        turnRight(speed);
        delayMicroseconds(500);
        moveForward(speed);
      }
    }
    else if(b<bthreshold && a<athreshold){
      turnLeft(speed);
      delayMicroseconds(500);
      moveForward(speed);
    }
    else if(b>bthreshold && a>athreshold){
      turnLessRight(speed);
    }
 
}

void stopAllMotors(){
      motor1->setSpeed(0);
      motor2->setSpeed(0);
      motor1->run(RELEASE);
      motor2->run(RELEASE);
}

void moveForward(int mySpeed){
      motor1->setSpeed(mySpeed);
      motor2->setSpeed(mySpeed);
      motor1->run(FORWARD);
      motor2->run(FORWARD);
}

void turnRight(int mySpeed){
        motor1->setSpeed(mySpeed);
        if(mySpeed>50){
          motor2->setSpeed(mySpeed-50);
        }
        else{
          motor2->setSpeed(0);
        }
        motor1->run(FORWARD);
        motor2->run(FORWARD);
}

void turnLeft(int mySpeed){
        motor2->setSpeed(mySpeed);
        if(mySpeed>50){
          motor1->setSpeed(mySpeed-50);
        }
        else{
          motor1->setSpeed(0);
        }
        motor1->run(FORWARD);
        motor2->run(FORWARD);
}

//function to turn right less sharply
void turnLessRight(int mySpeed){
        motor1->setSpeed(mySpeed);
        if(mySpeed>30){
          motor2->setSpeed(mySpeed-30);
        }
        else{
          motor2->setSpeed(0);
        }
        motor1->run(FORWARD);
        motor2->run(FORWARD);
}

