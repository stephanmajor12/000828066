#include <Arduino.h> 
#include <ESP8266WiFi.h> 
#include <OneWire.h> 
#include <DallasTemperature.h> 
#include <iostream>
#include<string>  
 
 //I Stephan Major, 000828066 certify that this is all my own work. 

// access credentials for WiFi network. 
const char* ssid = "VelvetCourt"; 
const char* password = "0123a456b789c098d7654e321f"; 
 
// WiFI server.  Listen on port 80, which is the default TCP port for HTTP 
WiFiServer server(80); 
 
 // Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

int incomingByte =0;
long currentmillis=0;
 
void setup() 
{ 
  Serial.begin(115200); 

  DS18B20.begin(); 
  Serial.println("\nWeb Server Demo"); 
 
  Serial.printf("\nConnecting to %s ", ssid); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println(" connected"); 
 
  server.begin(); 
  Serial.printf("Web server started, open %s in a web browser\n", 
WiFi.localIP().toString().c_str()); 
} 
 
void loop() 
{ 
  float fTemp; 

  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 

  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 

  // print the temp to the USB serial monitor 
  String myString = "Current temperature is: " + String(fTemp) + " deg. Celsius"; 

  // wait 2s (2000ms) before doing this again 
  WiFiClient client = server.available(); 


  currentmillis=millis();
  long days=0;
  long hours=0;
  long mins=0;
  long secs=0;
  secs = currentmillis/1000; //convect milliseconds to seconds
  mins=secs/60; //convert seconds to minutes
  hours=mins/60; //convert minutes to hours
  secs=secs-(mins*60); //subtract the coverted seconds to minutes in order to display 59 secs max 
  mins=mins-(hours*60); //subtract the coverted minutes to hours in order to display 59 minutes max
  hours=hours-(days*24); //subtract the coverted hours to days in order to display 23 hours max
 
  // wait for a client (web browser) to connect 
  if (client) 
  { 
    Serial.println("\n>> Client connected"); 
    Serial.println(">> Client request:"); 
    while (client.connected()) 
    { 
      // read line by line what the client (web browser) is requesting 
      if (client.available()) 
      { 
        // print information about the request (browser, OS, etc) 
        String line = client.readStringUntil('\r'); 
        Serial.print(line); 
        // wait for end of client's request 
        if (line.length() == 1 && line[0] == '\n') 
        { 
          // send some data back to the browser.  Note:  this is not 
          // proper HTML! 
          client.println("<h1>Hello from the HTTP Server</h1>"); 
          client.println("<p>" + myString + "</p>");
          client.println("<p>Your IP is:");
          client.println(client.localIP());
          client.println("</p>");

          client.println("<p>It has been running for:");
          client.println(hours);
          client.println(":");
          client.println(mins);
          client.println(":");
          client.println(secs);
          client.println("</p>");
          Serial.println(">> Response sent to client"); 
          break; 
        } 
      } 
    } 
 
    // keep read client request data (if any).  After that, we can terminate 
    // our client connection 
    while (client.available()) { 
      client.read(); 
    } 
 
    // close the connection: 
    client.stop(); 
    Serial.println(">> Client disconnected"); 
  } 
  delay(2000); 
} 