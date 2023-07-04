
#include <SoftwareSerial.h>
#include <Servo.h>

// Servo myservo;  // create servo object to control a servo
// Servo shootservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// static int pos = 0;    // variable to store the servo position
// static int shootpos=0;
SoftwareSerial softSerial(2, 3);

char junk;
String inputString="";

void setup()                    // run once, when the sketch starts
{
  softSerial.begin(9600);
 Serial.begin(9600);
   
  //  myservo.attach(5);
  //  shootservo.attach(A1);
     // attaches the servo on pin5 to the servo object
          // set the baud rate to 9600, same should be of your Serial Monitor
}

void loop()
{
  if(softSerial.available()){
    inputString = "";

  while(softSerial.available())
    {
      char inChar = (char)softSerial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial

    }
    while (softSerial.available() > 0)  
    { 
      junk = softSerial.read() ; 
      }      // clear the serial buffer
    // Serial.println(inputString);

    char buf[]={inputString[0],'\0'};
    // if(inputString=="BRR" ||inputString=="BRL"||inputString=="SHT" )
    //   //do nothing
    // else    
    Serial.write(buf,1);
    // Serial.print(Serial.read());
  }

    // if (inputString == "BRR") 
    // {
    //   rotatebracketright();
    // }
    // if (inputString == "BRL") 
    // {
    //   rotatebracketleft();
    // }
    // if (inputString == "SHT") 
    // {
    //   shoot();
    // }
}

// void shoot()
// {
//    shootpos=100;
//    shootservo.write(shootpos);
//    delay(200);
//    shootpos=0;
//    shootservo.write(shootpos);
//    delay(200);
//   //communicate the other arduino to shoot
// }
// void rotatebracketright()
// {
//   if(pos+15<TURN_MAX)
//     pos=pos+15;
//     myservo.write(pos); 
  
//   delay(100);
//   //communicate to rotate srvro to right
// }
// void rotatebracketleft()
// {
//   if(pos-15>TURN_MIN)
//     pos=pos-15;
//     myservo.write(pos);
//   delay(100);
//   //communicate to rotate srvro to left
// }

