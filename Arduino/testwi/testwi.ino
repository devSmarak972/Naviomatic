#include <ESP8266WiFi.h>         

const char *ssid = "myfi";     
const char *password = "password972";     

void setup() {
Serial.begin(9600);            

WiFi.softAP(ssid, password);     
Serial.print("Access Point: ");
Serial.print(ssid);
Serial.println(" started");

Serial.print("IP address: ");
Serial.println(WiFi.softAPIP()); 
}

void loop() {}