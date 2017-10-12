#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
unsigned long previousTime = 0;
unsigned long currentTime = 0;
const long interval = 500; // the time interval between each blink

// set up the two motor variables
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);
Adafruit_DCMotor *motor2 = AFMS.getMotor(1);
int athreshold = 850;
int bthreshold = 850;
int stop = 0;
int speed = 30;
int cat = 0;
int integerValue = 0;
int incomingByte = 0;

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
}

void loop(){

    if (Serial.available() > 0) {   // something came across serial
        integerValue = 0;         // throw away previous integerValue
        while(1) {            // force into a loop until 'n' is received
          incomingByte = Serial.read();
          if (incomingByte == '\n') break;   // exit the while(1), we're done receiving
          if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
          integerValue *= 10;  // shift left 1 decimal place
          // convert ASCII to integer, add, and shift left 1 decimal place
          integerValue = ((incomingByte - 48) + integerValue);
        }
      Serial.println(integerValue);   // Do something with the value
      speed = integerValue;
    }
    //Serial.println(speed);


    if(speed > 255){
      speed = 255;
    }
    else if(speed < 0){
      speed = 0;
    }

    
    delayMicroseconds(500);
    //Serial.println(speed);
    int a=analogRead(A0);
    int b=analogRead(A1);
    //Serial.print(a);
    //Serial.print("    ");
    //Serial.println(b);
    
    //Serial.println(a); 
    if (b<bthreshold && a>athreshold){
      moveForward(speed);
      //Serial.println("moving forward");
    }
    /*else if(b<bthreshold && a<athreshold){
      moveForward(speed);
      delayMicroseconds(1000);
      if(b>bthreshold && a>athreshold){
        turnRight(speed);
        Serial.println("turning right");
        delayMicroseconds(500);
        moveForward(speed);
       
      }
    }*/
    else if(b<bthreshold && a<athreshold){
      turnRight(speed);
      //Serial.println("turning right");
      //delayMicroseconds(500);
      //moveForward(speed);
    }
    else if(b>bthreshold && a>athreshold){
      turnLeft(speed);
      //Serial.println("turning left");
    }
    else if(b>bthreshold && a<athreshold){
      previousTime = millis();
      while(a < athreshold){
        turnLeft(speed);
        currentTime =millis();
        if (currentTime - previousTime >= interval) {
          previousTime = currentTime;
          break;
        }
        
      }
      //Serial.println("turning less left");
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
        if(mySpeed>20){
          motor2->setSpeed(mySpeed-20);
        }
        else{
          motor2->setSpeed(0);
        }
        motor1->run(FORWARD);
        motor2->run(FORWARD);
}

void turnLeft(int mySpeed){
        motor2->setSpeed(mySpeed);
        if(mySpeed>20){
          motor1->setSpeed(mySpeed-20);
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
        if(mySpeed>10){
          motor2->setSpeed(mySpeed-10);
        }
        else{
          motor2->setSpeed(0);
        }
        motor1->run(FORWARD);
        motor2->run(FORWARD);
}

void turnLessLeft(int mySpeed){
        motor2->setSpeed(mySpeed);
        if(mySpeed>10){
          motor1->setSpeed(mySpeed-10);
        }
        else{
          motor1->setSpeed(0);
        }
        motor1->run(FORWARD);
        motor2->run(FORWARD);
}

