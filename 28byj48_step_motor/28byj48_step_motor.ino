/* Project Ardu_Serie # 48
  EASYDRIVER: 4-Wire-Stepper Motor Driver - Brian Schmalz Design on A3967 IC 
              Bi-Polar Motors — .75A@30v peak — Making Using This a Breeze!
   Code I
   From: Brian Schmalz - Easy Driver Examples - Sample code and projects to get your stepper running!
   http://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html
   Objective: Hi,This is the most basic example you can have with an Arduino,
              an Easy Driver, and a stepper motor;)

   https://medium.com/jungletronics/easydriver-4-wire-stepper-motor-driver-9f32b233efe6
 
 */
#include "Arduino.h"
#include "StepperMotor.h"

const int STEP  = 2;
const int DIR   = 0;
const int DELAY = 1000;

StepperMotor stepper(STEP,DIR);

void setup() {
    
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    // enable the stepper motor, use .disable() to disable the motor
    stepper.enable();
    // set stepper motor speed by changing the delay value, the higher the delay the slower the motor will turn
    stepper.setStepDelay(DELAY);
  
//     pinMode(DIR, OUTPUT);
//     pinMode(STEP, OUTPUT);
//     digitalWrite(DIR, LOW);
//     digitalWrite(STEP, LOW);
}

void loop() {
//     digitalWrite(STEP, HIGH);
//     delay(DELAY);
//     digitalWrite(STEP, LOW);
//     delay(DELAY);
    stepper.step(1, 1000);  // move motor 1000 steps in one direction
    delay(1000);            // short stop
    stepper.step(0, 1000);  // move motor 1000 steps in the other dirction
    delay(1000);            //short stop
}
