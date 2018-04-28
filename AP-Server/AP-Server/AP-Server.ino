/* HTTP Web Server + Access Point example 

   Ranjit Bhinge,
   Device Interactions

   www.device-interactions.com
   www.github.com/deviceinteractions
   
   http://blog.device-interactions.com
   http://shop.device-interactions.com

   This example sets up an ESP8266 as an HTTP Server and opens a WiFi hotspot
   The Client is expected to connect to this hotspot and send messages using HTTP

   The Messages will be visible in the Serial monitor
  
*/


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(192,168,4,1);  // Defining a static IP address for the Server

// This is what the clients will need to connect to:
const char *ssid = "ESP-SERVER";    // you can replace this with any other name
const char *password = "password";  // you can replace this with any other password
String msgBody = "";

ESP8266WebServer server(80);        // Use the default port 80 for HTTP comms

void handleRoot() {

  Serial.println("Root page accessed by a client!");

// Respond with a mini HTML page
  server.send ( 200, "text/html", "<h1><b>Hi</b> There!</h1>");
}

void handleMessage(){
  
  if(server.hasArg("body")){
    Serial.println("Message received from Client:");
    msgBody = server.arg("body");
    Serial.println(msgBody);
    msgBody = "Hi, this is the Server. I got your message saying : " + msgBody;
    server.send ( 200, "text/plain", msgBody);
  }
  else {
    Serial.println("Invalid message received");
    server.send ( 200, "text/plain", "Recevied a message without a body!");
  }

  Serial.println("-------------------------------------");
}

void handleNotFound() {
  server.send ( 404, "text/plain", "404, No resource found");
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.println("Configuring access point...");

  //setup the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  server.on ( "/", handleRoot );
  server.on ( "/message", handleMessage );
  server.onNotFound ( handleNotFound );
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
