#include <SoftwareSerial.h>
#include <Servo.h>
   // variable to store the servo position
Servo myservo;  // create servo object to control a servo
Servo shootservo; 
#define DEBUG true
#define TURN_MAX 60
#define TURN_MIN 0
//forward motors
// left connections
#define enA1  5
#define inA1  2
#define inA2  3
// right connections
#define enA2 6//we will join all wheels pwm
#define inA3 4
#define inA4 7

// back motors
//left
#define enB1 10
#define inB1  8
#define inB2  9
//right
#define enB2 11
#define inB3  12
#define inB4  13
static int pos = 0;    // variable to store the servo position
static int shootpos=0;

//Receiver Arduino Board Code
char mystring[20];               //Initialized variable to store receive
void setup() {
	// Set all the motor control pins to outputs
      Serial.begin(9600);
	pinMode(enA1, OUTPUT);
	pinMode(enA2, OUTPUT);
	pinMode(enB2, OUTPUT);
	pinMode(enB1, OUTPUT);
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
  myservo.attach(A0);
   shootservo.attach(A1);
 // attaches the servo on pin 9 to the servo object

        // Begin the Serial at 9600 Baud
}
String inputString="";
char junk;
void loop() {
  
       
  if(Serial.available())
  {
        inputString = "";

while(Serial.available())
    {

      char inChar = (char)Serial.read(); //read the input
      inputString += inChar; 
      // inputString=Serial.readStringUntil('p');
                 //make a string of the characters coming on serial
    }
    // Serial.println(inputString);
     while (Serial.available() > 0)  
    { 
      junk = Serial.read() ; 
      } 

      // delay(100);


}
inputString.trim();
Serial.println("message in slave:");
Serial.println(inputString);

int val1=100,val2=100;
       if (inputString[0]== 'A') 
                {
                  frontmotorsforward(val1,val2);
                 }
                 if (inputString[0] == 'B') 
                {
                  backmotorsforward(val1,val2);
                 }
                 if (inputString[0] == 'C') 
                {
                  backmotorsbackward(val1,val2);
                 }
                 if (inputString[0] == 'D') 
                {
                  frontmotorsbackward(val1,val2);
                 }
                 if (inputString[0] == 'E') 
                {
                  clockwise(val1,val2);
                 }
                 if (inputString[0] == 'F') 
                {
                  anticlockwise(val1,val2);
                 }
               
                 if (inputString[0] == 'S') 
                {
                  stopbot();
                 }

                      //  delay(100);

}

void frontmotorsforward(int value1,int value2)
{
  analogWrite(enA1,value1);
   analogWrite(enA2,value2);
  analogWrite(enB1,0);
   analogWrite(enB2,0);

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inA3, HIGH);
  digitalWrite(inA4, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
}
void frontmotorsbackward(int val1,int val2)
{
    analogWrite(enA1,val1);
   analogWrite(enA2,val2);
    analogWrite(enB1,0);
   analogWrite(enB2,0);

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
}
void backmotorsbackward(int val1,int val2)
{
    analogWrite(enA1,0);
   analogWrite(enA2,0);
    analogWrite(enB1,val1);
   analogWrite(enB2,val2);

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
}
void backmotorsforward(int val1,int val2)
{
    analogWrite(enA1,0);
   analogWrite(enA2,0);
    analogWrite(enB1,val1);
   analogWrite(enB2,val2);

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);
}
void clockwise(int val1,int val2)
{
 analogWrite(enA1,val1);
   analogWrite(enA2,val2);
 analogWrite(enB1,val1);
   analogWrite(enB2,val2);

  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inA3, HIGH);
  digitalWrite(inA4, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
}
void anticlockwise(int val1,int val2)
{
 analogWrite(enA1,val1);
  analogWrite(enA2,val2);
  

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
   analogWrite(enA1,255);
   analogWrite(enA2,255);
    analogWrite(enB1,255);
     analogWrite(enB2,255);
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
   analogWrite(enA1,255);
   analogWrite(enA2,255);
    analogWrite(enB1,255);
     analogWrite(enB2,255);
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
   analogWrite(enA1,255);
   analogWrite(enA2,255);
    analogWrite(enB1,255);
     analogWrite(enB2,255);
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
//  analogWrite(enA1,255);
   analogWrite(enA2,255);
    analogWrite(enB1,255);
    //  analogWrite(enB2,255);  
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
   analogWrite(enA1,255);
  //  analogWrite(enA2,255);
    // analogWrite(enB1,255);
     analogWrite(enB2,255);
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
  //  analogWrite(enA1,255);
   analogWrite(enA2,255);
    analogWrite(enB1,255);
    //  analogWrite(enB2,255);
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
   analogWrite(enA1,255);
  //  analogWrite(enA2,255);
    // analogWrite(enB1,255);
     analogWrite(enB2,255);
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
   analogWrite(enA1,255);
   analogWrite(enA2,255);
    analogWrite(enB1,255);
     analogWrite(enB2,255);
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
   analogWrite(enA1,255);
   analogWrite(enA2,255);
    analogWrite(enB1,255);
     analogWrite(enB2,255);
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
 analogWrite(enA1,0);
   analogWrite(enA2,0);
    analogWrite(enB1,0);
     analogWrite(enB2,0);
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
   shootpos=100;
   shootservo.write(shootpos);
   delay(200);
   shootpos=0;
   shootservo.write(shootpos);
   delay(200);
  //communicate the other arduino to shoot
}
void rotatebracketright()
{
  if(pos+15<TURN_MAX)
    pos=pos+15;
    myservo.write(pos); 
  
  delay(100);
  //communicate to rotate srvro to right
}
void rotatebracketleft()
{
  if(pos-15>TURN_MIN)
    pos=pos-15;
    myservo.write(pos);
  delay(100);
  //communicate to rotate srvro to left
}



   

