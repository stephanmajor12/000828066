// Mohawk College - COMP-10184
//
// Pulse Width Modulation - Test Program
// I Stephan Major, 000828066 certify that all the following work is my own.
#include <Arduino.h>

//global var
boolean onoffFlag;
float iVal;
int iButton = 1;
int ledflag=0; 

void setup() {
  // configure the USB serial monitor
  Serial.begin(115200);
  // configure pin D4 as a digital output - this is the LED
  pinMode(D4, OUTPUT);
  // set default PWM range
  analogWriteRange(1023);
  //button
  pinMode(D5, INPUT);

  digitalWrite(D4, LOW);
}
void loop() {
  iVal = analogRead(A0);
  // set the PWM pulse width
  analogWrite(D4, iVal);

  //iButton = digitalRead(D5);
  if(digitalRead(D5) == HIGH) {
    if(ledflag == 0) {
      ledflag = 1;
      digitalWrite(D4,HIGH);
    } else {
      ledflag = 0;
      digitalWrite(D4,LOW);
    }
    delay(1000);
  } 
}
