// stepper starts out not stepping
// one stepVal amount of steps per button click
// red LED light up when done 1 rot

// include all the stuff
#include <Stepper.h> 

// define stepper stuff
#define STEPSPERREV 200
Stepper stepper(STEPSPERREV, 9, 10, 11, 12);
// 200 steps per 360 deg => 3 steps per 5.4 deg 
int stepVal = 3;
//int stepVal = 50; // higher num for testing
bool stepperState = false; // set to not moving initially
int currentStep = 0; // set to zero initially
int totalStep = STEPSPERREV;

// define complete rotation led output
int ledPin1 = 7;

// define one movement led output
int ledPin2 = 8;

// define button input
int buttonPin = 2;
// button state is HIGH when pressed, LOW when not pressed

// define wait time in ms
int wait = 1000;

void setup() {
  // set up motor
  Serial.begin(9600);
  stepper.setSpeed(50);

  // set up complete rotation led
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, HIGH);

  // set up pause rotation led
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);

  // set up button
  pinMode(buttonPin, INPUT);

  // button interupt
  attachInterrupt(digitalPinToInterrupt(buttonPin), moveStepper, RISING);
}

void loop() {
  if (stepperState) {
    stepperState = false;
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin2, LOW);
    stepper.step(stepVal);
    digitalWrite(ledPin2, HIGH);
    currentStep += stepVal;
  }
  
  if (currentStep >= totalStep) {
    currentStep = 0;
  }

  if (currentStep == 0) {
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
  }
}

void moveStepper() {
  stepperState = true;
}
