// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College
// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>
// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
void setup() {
 // configure the USB serial monitor
 Serial.begin(115200);
 // Start the DS18B20 sensor
 //DS18B20.begin();
 DeviceAddress myAddress;

 //String[2] myData;

  DS18B20.begin();

  DS18B20.getAddress(myAddress,0);

  Serial.println("");
  Serial.println("---Device Address: ---");

  for(uint8_t i=0; i<8;i++) {
    Serial.print(myAddress[i],HEX);
  }
  Serial.println("");

  Serial.println("-----------");


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
 float fTemp;

 DeviceAddress myAddress;

 //String[2] myData;

  DS18B20.begin();

  DS18B20.getAddress(myAddress,0);

 if(!DS18B20.getAddress(myAddress,0)) {
  Serial.println("Disconnected");
 } else {
  // ask DS18B20 for the current temperature
  DS18B20.requestTemperatures();
  // fetch the temperature. We only have 1 sensor, so the index is 0.
  fTemp = DS18B20.getTempCByIndex(0);
  // print the temp to the USB serial monitor
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + tempCheck(fTemp));
 }

 // wait 2s (2000ms) before doing this again
 delay(2000);
}