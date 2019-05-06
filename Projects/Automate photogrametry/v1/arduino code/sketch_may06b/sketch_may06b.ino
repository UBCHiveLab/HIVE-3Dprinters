// stepper starts out not stepping
// one stepVal amount of steps per button click
// red LED light up when done 1 rot

// include all the stuff
#include <Stepper.h> 

// define stepper stuff
#define STEPS 32
Stepper stepper(STEPS, 8, 10, 9, 11);
// 2048 steps per 360 deg => 32 steps per 5.625 deg 
int stepVal = 32;
//int stepVal = 512; // higher num for testing
bool stepperState = false; // set to not moving initially
int currentStep = 0; // set to zero initially
int totalStep = 2048;

// define complete rotation led output
int ledPin1 = 12;

// define one movement led output
int ledPin2 = 13;

// define button input
int buttonPin = 2;
// button state is HIGH when pressed, LOW when not pressed

// define wait time in ms
int wait = 1000;

void setup() {
  // set up motor
  Serial.begin(9600);
  stepper.setSpeed(200);

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
/*
void moveStepperBuffer() {
  stepper.step(stepVal);
  currentStep += stepVal;
  blinkLED2();
  checkCompleteRot();
}
/*
void blinkLED2() {
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin2, HIGH);
  //delay(blinker);
  digitalWrite(ledPin2, LOW);
}

void checkCompleteRot() {
  if (currentStep >= totalStep) {
    digitalWrite(ledPin1, HIGH);
    currentStep = 0;
  } else {
    digitalWrite(ledPin1, LOW);
  }
}
*/
