
#include <SoftwareSerial.h>
SoftwareSerial softSerial(2, 3);

char junk;
String inputString="";

void setup()                    // run once, when the sketch starts
{
  softSerial.begin(9600);
 Serial.begin(9600);            // set the baud rate to 9600, same should be of your Serial Monitor
}

void loop()
{
  if(softSerial.available()){
  while(softSerial.available())
    {
      char inChar = (char)softSerial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (softSerial.available() > 0)  
    { 
      junk = softSerial.read() ; 
      }      // clear the serial buffer
    char buf[]={inputString[0],'\0'};
    Serial.write(buf,1);
    inputString = "";
  }
}
