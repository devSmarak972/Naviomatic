#include <SoftwareSerial.h>
   // variable to store the servo position

#define DEBUG true

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
//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4

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
 // attaches the servo on pin 9 to the servo object
 //ir pins
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
        // Begin the Serial at 9600 Baud
}
String inputString="";
char junk;
int s1,s2,s3,s4,s5;
void loop() {
  
       
  
    s1 = digitalRead(ir1);  //Left Most Sensor
    s2 = digitalRead(ir2);  //Left Sensor
    s3 = digitalRead(ir3);  //Middle Sensor
    s4 = digitalRead(ir4);  //Right Sensor
    s5 = digitalRead(ir5);  //Right Most Sensor


  //if only middle sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 0) && (s5 == 0))
  {
    //go forward
   state=0;
   forward();
  }
  
  //if only left sensor detects black line
  if((s1 == 0) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //going right with less speed
state=1;
right(100);
  }
  
  //if only left most sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //going right with full speed 
state=2;
right(255);
  }

  //if only right sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 0))
  {
    //going left with less speed 
state=3;
left(100);
  }

  //if only right most sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    //going left with full speed 
state=4;
left(255);
  }

  //if middle and right sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    //going left with lesser speed
    state=5;
left(100);
  }

  //if middle and left sensor detects black line
  if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0))
  {
    //going right with lesser speed 
    state=6;
right(100);
  }

  //if middle, left and left most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0))
  {
    //going right with full speed 
    state=7;
    rotateanticlockwise(255);
  }

  //if middle, right and right most sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    
    rotateclockwise(255);

  }

  //if all sensors are on a black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    state=9;
stopbot();
  }
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    state=10;
    stopbot();
// junction detected
  }
  delay(100);
if(Serial.available())
  {
    inputString = "";

while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
     while (Serial.available() > 0)  
    { 
      junk = Serial.read(); 
      }

      delay(100);
}
if(state==10)
{
  if(inputString=="LFT")
  {
  rotateanticlockwise(60);
  s1 = digitalRead(ir1);  //Left Most Sensor
    s2 = digitalRead(ir2);  //Left Sensor
    s3 = digitalRead(ir3);  //Middle Sensor
    s4 = digitalRead(ir4);  //Right Sensor
    s5 = digitalRead(ir5);  //Right Most Sensor

    delay(1000);
while( s2!=1||s4!=1||s3!=1)
{
    rotateanticlockwise(60);
    s1 = digitalRead(ir1);  //Left Most Sensor
    s2 = digitalRead(ir2);  //Left Sensor
    s3 = digitalRead(ir3);  //Middle Sensor
    s4 = digitalRead(ir4);  //Right Sensor
    s5 = digitalRead(ir5);  //Right Most Sensor

    delay(1000);

}
  }
  else if(inputString=="RGT")
  {
    rotateclockwise(60);
  s1 = digitalRead(ir1);  //Left Most Sensor
    s2 = digitalRead(ir2);  //Left Sensor
    s3 = digitalRead(ir3);  //Middle Sensor
    s4 = digitalRead(ir4);  //Right Sensor
    s5 = digitalRead(ir5);  //Right Most Sensor

    delay(1000);
while( s2!=1||s4!=1||s3!=1)
{
    rotateclockwise(60);
    s1 = digitalRead(ir1);  //Left Most Sensor
    s2 = digitalRead(ir2);  //Left Sensor
    s3 = digitalRead(ir3);  //Middle Sensor
    s4 = digitalRead(ir4);  //Right Sensor
    s5 = digitalRead(ir5);  //Right Most Sensor

    delay(1000);

}
  }
  
}

  
  
   

