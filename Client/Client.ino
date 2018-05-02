/* HTTP Client that sends messages over HTTP

   Ranjit Bhinge,
   Device Interactions

   www.device-interactions.com
   www.github.com/deviceinteractions
   
   http://blog.device-interactions.com
   http://shop.device-interactions.com

   This example sets up an ESP8266 as an HTTP Client and connects to the Server's WiFi hotspot
   This Client sends messages using HTTP GET requests and expects an acknowledgement response from the Server
   
   The Messages and responses will be visible in the Serial monitor

   To send a message, open the Serial Monitor and type it in the top bar and hit 'Send'

   To send long messages with spaces, please use '%20' instead of the space.
   eg: 'This%20is%20a%20space'  -> 'This is a space'
  
*/


#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

// This is the Server's WiFi network the client will try to connect to
#define WIFI_SSID "ESP-SERVER"    // same as the Server AP WiFi name
#define WIFI_PASS "password"      // same as the Server AP WiFi password

String http_addr = "http://192.168.4.1";  // Server's IP address on the AP network

// Global variables
String url = "";
String body = "";

void setup() {
    Serial.begin(9600); // Init Serial comms

    // Clear the Serial buffer
    Serial.println();
    Serial.println("Clearing Serial buffer...");
    Serial.flush();
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("\nConnecting to the Server's Access Point");
    
    // WiFi connection
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
    // Auto reconnect on loss of WiFi connection
    if(WiFi.status() != WL_CONNECTED){
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(WIFI_SSID);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.println();
      Serial.println("Ready to send a message. Type into the Serial Monitor Bar and hit Send");      
    }

    // wait for Serial input from the User
     if(Serial.available()>0){
      body  = Serial.readString();
      // Check if the received message is valid
      if((body.length()>0)) {
  
          // Initiate the HTTP call based on the received User Input
          HTTPClient http;
          url = http_addr + "/message?body=" + body;
          Serial.print("[HTTP] starting...\n");
          // configure traged server and url
          Serial.println(url);
          http.begin(url);
  
          Serial.print("Sending message - ");
          Serial.println(body);
          // start connection and send HTTP header
          int httpCode = http.GET();
            
          // httpCode will be negative on error
          if(httpCode > 0) {
              // Receive the Server response
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

