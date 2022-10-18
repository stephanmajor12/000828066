// COMP-10184 – Mohawk College
// PIR Sensor Test Application
// Turn on the blue LED with motion is detected.

 //I Stephan Major, 000828066 certify that all the following work is my own.
#include <Arduino.h>
#include <iostream>  
#include<string>  
// digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6
// *************************************************************
static int hasRun;
static int buttonPress;
void setup() {
 // configure the USB serial monitor
 Serial.begin(115200);
 // configure the LED output
 pinMode(LED_BUILTIN, OUTPUT);
 // PIR sensor is an INPUT
 pinMode(PIN_PIR, INPUT);
 // Button is an INPUT
 pinMode(PIN_BUTTON, INPUT_PULLUP);

}
// *************************************************************
void loop() {
 bool bPIR;
 // read PIR sensor (true = Motion detected!). As long as there
 // is motion, this signal will be true. About 2.5 seconds after
 // motion stops, the PIR signal will become false.
 bPIR = digitalRead(PIN_PIR);

 // send the PIR signal directly to the LED
 // but invert it because true = LED off!
 //digitalWrite(LED_BUILTIN, !bPIR);



 Serial.println(bPIR);
 //Serial.println("has run: " + hasRun);

  if(hasRun == 0) {
    if(bPIR == true) {
      for(int i = 0; i < 40; i++) {
        if(digitalRead(PIN_BUTTON) == LOW) {
          if(buttonPress == 0) {
            buttonPress = 1;
          } else {
            buttonPress = 0;
          }
          digitalWrite(LED_BUILTIN, HIGH);
        } else {
          if(buttonPress == 0) {
            digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(125);              // wait for a second
            digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
            delay(125);  
          } else {
            //do nothing
          }
        }
      }
      //hasRun = 1;
    }
  } else if(hasRun == 1) {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(125);              // wait for a second
  }
}