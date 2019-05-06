// stepper starts out not stepping
// will start or pause when button press
// will indefinite pause when complete rotation
// complete rot LED high when complete rot
// pause rot LED high when pause rot

// include all the stuff
#include <Stepper.h> 
#include <Servo.h>

// define stepper stuff
#define STEPS 32
Stepper stepper(STEPS, 8, 10, 9, 11);
// 2048 steps per 360 deg => 32 steps per 5.625 deg 
//int stepVal = 32;
int stepVal = 512; // higher num for testing
bool stepperState = false; // set to not moving initially
int currentStep = 0; // set to zero initially
int totalStep = 2048;

// define complete rotation led output
int ledPin1 = 12;
int LEDstate1 = HIGH; // high = light = not stepping, low = no light = stepping

// define pause rotation led output
int ledPin2 = 13;
int LEDstate2 = HIGH; // high = light = paused, low = no light = not paused

// define button input
int buttonPin = 2;
// button state is HIGH when pressed, LOW when not pressed

// define servo stuff
int servoPin = 7;
Servo servo;

// define wait time in ms
int wait = 1000;

void setup() {
  // set up motor
  Serial.begin(9600);
  stepper.setSpeed(200);

  // set up complete rotation led
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LEDstate1);

  // set up pause rotation led
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LEDstate2);

  // set up button
  pinMode(buttonPin, INPUT);

  // button interupt
  attachInterrupt(digitalPinToInterrupt(buttonPin), pauseStepper, RISING);

  // set up servo
  servo.attach(servoPin);
}

void loop() {
  // if it has completed a rotation, shut off stepper
  if (currentStep >= totalStep && stepperState == true) {
    currentStep = 0;
    stepperState = false;
    LEDstate1 = HIGH;
  }

  // make stepper turn depending on state
  if (stepperState) {
    LEDstate1 = LOW;
    LEDstate2 = LOW;
    servoClick();
    delay(wait);
    stepper.step(stepVal);
    delay(wait);
    currentStep += stepVal;
  }

   // turn LED on/off depending on state
  digitalWrite(ledPin1, LEDstate1);
  digitalWrite(ledPin2, LEDstate2);
}

void pauseStepper() {
  stepperState = !stepperState;
  LEDstate2 = !LEDstate2;
}

void servoClick() { 
  servo.write(0);
  servo.write(100);
  delay(wait);
  servo.write(0);
}
