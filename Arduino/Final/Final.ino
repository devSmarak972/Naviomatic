#include <SoftwareSerial.h>

/* Pins 8, 9, 10 and 11 of Arduino are connected to L298N Motor Driver Input pins i.e. 
IN1, IN2, In3 and IN4 respectively*/


#define DEBUG true
// Motor A connections
#define enA  9;
#define inA1  8;
#define inA2  7;
// Motor B connections
// #define enB 10;//we will join all wheels pwm
#define inA3 12;
#define inA4 13;

#define inB1  8;
#define inB2  7;
#define inB3  8;
#define inB4  7;

#define RXPIN 2
#define TXPIN 3

SoftwareSerial esp8266Serial(RXPIN,TXPIN); //Pin 2 & 3 of Arduino as RX and TX. Connect TX and RX of ESP8266 respectively.


void setup()
  {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	// pinMode(enB, OUTPUT);
	pinMode(inA1, OUTPUT);
	pinMode(inA2, OUTPUT);
	pinMode(inA3, OUTPUT);
	pinMode(inA4, OUTPUT);
	pinMode(inB1, OUTPUT);
	pinMode(inB2, OUTPUT);
	pinMode(inB3, OUTPUT);
	pinMode(inB4, OUTPUT);
	// Turn off motors - Initial state
	digitalWrite(inA1, LOW);
	digitalWrite(inA2, LOW);
	digitalWrite(inA3, LOW);
	digitalWrite(inA4, LOW);
	digitalWrite(inB1, LOW);
	digitalWrite(inB2, LOW);
	digitalWrite(inB3, LOW);
	digitalWrite(inB4, LOW);
    Serial.begin(9600);
    
    esp8266Serial.begin(115200); //Baud rate for communicating with ESP8266. Your's might be different.
    esp8266Data("AT+RST\r\n", 5000, DEBUG); // Reset the ESP8266
    esp8266Data("AT+CWMODE=1\r\n", 5000, DEBUG); //Set station mode Operation
  
    /*Change the following command as per your requirement i.e. enter the 
    SSID and Password of your WiFi Network in the command.*/
    
    esp8266Data("AT+CWJAP=\"myfi\",\"password972\"\r\n", 5000, DEBUG);//Enter your WiFi network's SSID and Password.
                                   
    /*while(!esp8266Serial.find("OK")) 
    {
      }*/
      
    esp8266Data("AT+CIFSR\r\n", 5000, DEBUG);//You will get the IP Address of the ESP8266 from this command. 
  
    /* The following statement is to assign Static IP Address to ESP8266. 
    The syntax is AT+CIPSTA=<ip>,<gateway>,<netmask>. 
    This will assign a Static IP Address of 192.168.1.254 (in my case)
    to the ESP8266 Module. Change this value as per your requirements i.e. this IP address 
    shouldn't conflict with any other device. 
    Also, the second and third parameters are Gateway and Net Mask values. 
    You can get these values from ipconfig command in command prompt*/
  
    esp8266Data("AT+CIPSTA=\"192.168.1.254\",\"192.168.1.1\",\"255.255.255.0\"\r\n", 3000, DEBUG); // Assign Static IP Address
    esp8266Data("AT+CIFSR\r\n", 5000, DEBUG);//You will get the IP Address of the ESP8266 from this command. 

    esp8266Data("AT+CIPMUX=1\r\n", 5000, DEBUG);
    esp8266Data("AT+CIPSERVER=1,80\r\n", 5000, DEBUG);
  }

void loop()
  {
    if (esp8266Serial.available())
      {
        if (esp8266Serial.find("+IPD,"))
          {
            String msg;
            esp8266Serial.find("?");
            msg = esp8266Serial.readStringUntil(' ');
            String command1 = msg.substring(0, 5);
            String command2 = msg.substring(6);
                        
           if (DEBUG) 
              {
                Serial.println(command1);//Must print "robot"
                Serial.println(command2);//Must print "FWD" or "REV" or "LFT" or "RGT" or "STP"
              }
            delay(100);

              if (command2 == "F") 
                {
                  forward();
                 }
                 if (command2 == "B") 
                {
                  reverse();
                 }
                 if (command2 == "R") 
                {
                  right();
                 }
                 if (command2 == "L") 
                {
                  left();
                 }
                 if (command2 == "FR") 
                {
                  forwardright();
                 }
                 if (command2 == "FL") 
                {
                  forwardleft();
                 }
                 if (command2 == "BR") 
                {
                  backwardright();
                 }
                 if (command2 == "BL") 
                {
                  backwardleft();
                 }
                 if (command2 == "RC") 
                {
                  rotateclockwise();
                 }
                 if (command2 == "RAC") 
                {
                  rotateanticlockwise();
                 }
                 if (command2 == "BRR") 
                {
                  rotatebracketright();
                 }
                 if (command2 == "BRL") 
                {
                  rotatebracketleft();
                 }
                 if (command2 == "stop") 
                {
                  stopbot();
                 }
                 if (command2 == "shoot") 
                {
                  shoot();
                 }
                 
          }
      }
  }

void forward()
{
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inA3, HIGH);
  digitalWrite(inA4, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
}

void reverse()
{
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);
}

void right()
{
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, HIGH);

  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  
  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
}

void left()
{
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  
  digitalWrite(inA3, HIGH);
  digitalWrite(inA4, LOW);

  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);
}
void forwardright()
{
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, LOW);

  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
}
void forwardleft()
{
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  
  digitalWrite(inA3, HIGH);
  digitalWrite(inA4, LOW);

  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
}
void backwardright()
{
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, HIGH);

  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
}
void backwardleft()
{
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, LOW);

  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);
}
void rotateclockwise()
{
 digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, HIGH);

  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);  
}
void rotateanticlockwise()
{
 digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  
  digitalWrite(inA3, HIGH);
  digitalWrite(inA4, LOW);

  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);

  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);  
}
void stopbot()
{

 digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, LOW);

  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);  

}
void shoot()
{
  //communicate the other arduino to shoot
}
void rotatebracketright()
{
  //communicate to rotate srvro to right
}
void rotatebracketright()
{
  //communicate to rotate srvro to left
}
   
String esp8266Data(String command, const int timeout, boolean debug)
  {
    String response = "";
    esp8266Serial.print(command);
    long int time = millis();
    while ( (time + timeout) > millis())
      {
        while (esp8266Serial.available())
          {
            char c = esp8266Serial.read();
            response += c;
          }
      }
    if (debug)
      {
        Serial.print(response);
      }
    return response;
  }
 