#include <Arduino.h>
void setup() {
 // configure the USB serial monitor
 Serial.begin(115200);
}

float iVal;
double iVal2;
String tempOut;

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

String tempCheck(float temp) {
  String tempOut;
  if(temp < 10) {
    tempOut = "Cold!";
  }
  else if(temp < 15) {
    tempOut = "Cool";
  } 
  else if (temp < 25)
  {
    tempOut = "Perfect";
  } 
  else if (temp < 30)
  {
    tempOut = "Warn";
  }
  else if (temp < 35)
  {
    tempOut = "Hot";
  } 
  else if (temp > 35)
  {
    tempOut = "Too Hot!";
  } else {
    tempOut = "Error...";
  }
  return tempOut;
}

void loop() {
 // read digitized value from the D1 Mini's A/D convertor
 iVal = analogRead(A0);

 float myVal = map(iVal,0,1023,0,1000) / 50;
 Serial.println("Digitized output of " + String(iVal) + "is equivalent to a temperature input of " + String(myVal) + " deg. C, which is " + tempCheck(myVal));
 // print value to the USB port
 //Serial.println("Digitized Value = " + String(iVal));
 // wait 0.5 seconds (500 ms)
 delay(500);
}