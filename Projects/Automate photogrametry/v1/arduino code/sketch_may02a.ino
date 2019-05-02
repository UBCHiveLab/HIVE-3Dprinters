#include <Stepper.h> 

// define motor stuff
#define STEPS 32
Stepper stepper(STEPS, 8, 10, 9, 11);
// 2048 steps per 360 deg => 32 steps per 5.625 deg 
int val = 32;

// define led output
int ledPin = 12;

// define wait time in ms
int wait = 1000;

void setup() {
  // set up motor
  Serial.begin(9600);
  stepper.setSpeed(200);

  // set up led
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (Serial.available()>0) {
    if (Serial.parseInt() == 1)
      {
        stepper.step(val);
        digitalWrite(ledPin, HIGH);
        delay(wait);
        digitalWrite(ledPin, LOW);
      }  
  }
}
