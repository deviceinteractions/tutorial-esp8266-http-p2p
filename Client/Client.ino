/* HTTP Client that sends messages over HTTP

   Ranjit Bhinge,
   Device Interactions

   www.device-interactions.com
   www.github.com/deviceinteractions
   
   http://blog.device-interactions.com
   http://shop.device-interactions.com

   This example sets up an ESP8266 as an HTTP Server and opens a WiFi hotspot
   The Client is expected to connect to this hotspot and send messages using HTTP
   
   The Messages and responses will be visible in the Serial monitor

   To send a message, open the Serial Monitor and type it in the top bar and hit 'Send'

   To send long messages with spaces, please use '%20' instead of the space.
   eg: 'This%20is%20a%20space'  -> 'This is a space'
  
*/


#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

#define WIFI_SSID "ESP-SERVER"    // same as the Server AP WiFi name
#define WIFI_PASS "password"      // same as the Server AP WiFi password

String http_addr = "http://192.168.4.1";
String url = "";
String body = "";
void setup() {

    Serial.begin(9600);
   // Serial.setDebugOutput(true);

    Serial.println();
    Serial.println("Clearing Serial buffer...");
    Serial.flush();
     WiFi.begin(WIFI_SSID, WIFI_PASS);
      Serial.println("\nConnecting to the Server's Access Point");
    
      // Wait for connection
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(WIFI_SSID);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.println();
      Serial.println("Ready to send a message. Type into the Serial Monitor Bar and hit Send");

}

void loop() {
    if(WiFi.status() != WL_CONNECTED){
              Serial.println("");
              Serial.print("Connected to ");
              Serial.println(WIFI_SSID);
              Serial.print("IP address: ");
              Serial.println(WiFi.localIP());
              Serial.println();
              Serial.println("Ready to send a message. Type into the Serial Monitor Bar and hit Send");      
    }
     if(Serial.available()>0){
      // wait for WiFi connection
      body  = Serial.readString();
      if((body.length()>0)) {
  
          HTTPClient http;
          url = http_addr + "/message?body=" + body;
          Serial.print("[HTTP] starting...\n");
          // configure traged server and url
          Serial.println(url);
          http.begin(url); //HTTP
  
          Serial.print("Sending message - ");
          Serial.println(body);
          // start connection and send HTTP header
          int httpCode = http.GET();
  
          // httpCode will be negative on error
          if(httpCode > 0) {
              // file found at server
              if(httpCode == HTTP_CODE_OK) {
                  Serial.print("Received Response\n");
                  String payload = http.getString();
                  Serial.println(payload);
                  Serial.flush();
              }
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
  
          http.end();
      }
    } 
   
    delay(2000);
}

