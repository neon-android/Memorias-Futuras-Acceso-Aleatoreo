#include <Arduino.h>
#include "DYPlayerArduino.h"
#include <Servo.h>

#define CUELLO 2
#define HOMBROI 4
#define HOMBROD 8
#define PECHOI 5
#define PECHOD 7
#define ESTOMAI 6
#define ESTOMAD 9
#define CARA 3
#define SENS 10
#define PinNum 7
#define SERVO 11

DY::Player player(&Serial1);
Servo myservo;

byte RobotPins[] = { CUELLO, HOMBROI, HOMBROD, PECHOI, PECHOD, ESTOMAI, ESTOMAD };
long randomNumber;
bool oldState = false;
bool newState = false;
int index = 0;
int pos = 90

  ;
void setup() {
  for (int i = 0; i < PinNum; i++) {
    pinMode(RobotPins[i], OUTPUT);
  }
  pinMode(CARA, OUTPUT);
  pinMode(SENS, INPUT_PULLUP);
  digitalWrite(CARA, LOW);
  player.begin();
  player.setVolume(30);  // 50% Volume
  myservo.attach(SERVO);

  myservo.write(pos);  // tell servo to go to position in variable 'pos'
  delay(15);           // waits 15 ms for the servo to reach the position
}

void loop() {
  randomNumber = random(1, 11);
  sensor();
  switch (index) {

    case 0:
      for (int j = 0; j < 255; j++) {
        for (int i = 0; i < PinNum; i++) {
          analogWrite(RobotPins[i], j);
          delayMicroseconds(500);
        }
      }
      for (int j = 255; j > 0; j--) {
        for (int i = 0; i < PinNum; i++) {
          analogWrite(RobotPins[i], j);
          delayMicroseconds(500);
          //umicroDelay(1);
        }
      }
      break;


    case 1:
      for (int i = 0; i < PinNum; i++) {
        digitalWrite(RobotPins[i], HIGH);
        delay(50);
        digitalWrite(RobotPins[i], LOW);
        delay(50);
        //usensor();
      }
      for (int i = PinNum; i > -1; i--) {
        digitalWrite(RobotPins[i], HIGH);
        delay(50);
        digitalWrite(RobotPins[i], LOW);
        delay(50);
        //sensor();
      }

      index = 2;
      break;

    case 2:
      for (int j = 0; j < 255; j++) {
        for (int i = 0; i < PinNum; i++) {
          analogWrite(RobotPins[i], j);
          delayMicroseconds(50);
        }
      }
      for (int j = 255; j > 0; j--) {
        for (int i = 0; i < PinNum; i++) {
          analogWrite(RobotPins[i], j);
          delayMicroseconds(50);
          //umicroDelay(1);
        }
      }

      // if (newState) {
      //   index = 0;
      // }

      break;
  }
}

void sensor(void) {
  newState = digitalRead(SENS);
  if (newState != oldState) {
    if (!newState) {
      player.playSpecified(randomNumber);
      //delay(10000);
      digitalWrite(CARA, HIGH);

      for (pos = 90; pos >= 0; pos--) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(5);           // waits 15 ms for the servo to reach the position
        index = 1;
      }
    } if(newState){
      digitalWrite(CARA, LOW);
      for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(5);           // waits 15 ms for the servo to reach the position
        index = 0;
      }
    }

    oldState = newState;
  }
}
