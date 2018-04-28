# Tutorial for Peer-to-Peer HTTP Communication using ESP8266 modules

## Overview
The Communication setup is a Master-Slave configuration where one module is a Server and the other is a Client.
The Server Module generates a WiFi hotspot and allows clients to connect to it.
The Client Module connects to this hotspot and sends messages, based on the User's Serial commands

To get started, click the Clone/Download button in the top right corner and get a copy of this repository on your PC.
Open the downloaded directory.

## The Server Module
To set up the Server, follow these steps:
1. Open the AP-Server.ino file with Arduino IDE
2. Plug on your first ESP8266 Module
3. Select the right port and board (ESP8266 Module)
4. Open your Serial Monitor, and select 9600 baud rate
5. Click on 'Upload Sketch' (Ctrl+U)
6. Once the Sketch is uploaded, wait for the Serial message confirming that the Access Point and HTTP Server have started
7. Now leave this powered up

## The Client Module
To set up the Client Module, follow these steps:
1. Open the Client.ino file with the Arduino IDE
2. Plug in the second ESP8266 Module
3. Select the right board and port (remember that the first ESP8266 module is connected too)
4. Open the Serial Monitor and select 9600 baud rate
5. Click on 'Upload Sketch' (Ctrl+U)
6. Once the sketch is uploaded, wait for the Serial message to confirm that the Client has connected to the Server's Access Point.
7. Once the connection takes place, it will prompt you for a Serial Command that can be provided from the top bar in the Serial Monitor
8. Now you can type in any message that you like in the Serial monitor bar, and that message will be sent to the Server over the Hotspot
9. You will also receive an acknowledgement message back from the Server regarding your message

### Try connecting the two modules on two separate PCs, with the two Serial Monitors open. You will see all the magic happening!
