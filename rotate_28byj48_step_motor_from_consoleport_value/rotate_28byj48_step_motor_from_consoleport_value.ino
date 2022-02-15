#include<stdio.h>
#include <stdlib.h>
#include "Arduino.h"
#include "StepperMotor.h"

#define MAX_BUFF_LEN  255

/* inspired by https://www.youtube.com/watch?v=I-3cRo7lId8 */

char c;
char str[MAX_BUFF_LEN];
uint8_t idx = 0;
const int STEP  = 2;
const int DIR   = 0;
const int DELAY = 1000;

StepperMotor stepper(STEP,DIR);

void setup(){
  Serial.begin(115200);
  stepper.enable();
  // set stepper motor speed by changing the delay value, the higher the delay the slower the motor will turn
  stepper.setStepDelay(DELAY);
}

int removeFirst(int x) {
  if (x < 10) return 0;
  return x%10 + 10 * removeFirst(x/10);
}

void rotate(int value){
  int direction = (int) (value / pow(10, value));
  value = removeFirst(value);
  
  Serial.print("rotate in: ");
  Serial.println(direction);
  
  Serial.print("how much: ");
  Serial.println(value);

  for(int idx=0; idx<value; idx++)
  {
    stepper.step(direction, value);
  }
}

void loop(){
  if(Serial.available()>0){
    c = Serial.read();
    if(c != '\n')
      str[idx++] = c;
    else{
      str[idx] =  '\0';
      idx = 0;

      Serial.print("Recieved: ");
      Serial.println(str);
      rotate(atoi(str));
    }
  }
}
