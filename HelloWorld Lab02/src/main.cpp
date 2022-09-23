#include <Arduino.h>

unsigned long myTime;

void setup() {
  // put your setup code here, to run once:
  //I Stephan Major, 000828066 certify that all the following work is my own.
  Serial.begin(115200);

  String myID = "000828066";
  String myName = "Stephan Major";
  Serial.println("\n\nHello, World!");
  Serial.println(myID);
  String myFlash = String (ESP.getFlashChipId());
  String myChip = String (ESP.getChipId());
  //snprintf(clientid,25,"WIFI-Display-%08X",chipID);
  //Serial.print("Client ID: ");
  Serial.println("My chip ID = " + myChip);
  Serial.println("My flash ID = " + myFlash);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  myTime = millis();
  Serial.println(myTime);
}