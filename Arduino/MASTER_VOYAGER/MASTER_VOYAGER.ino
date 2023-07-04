
#include <SoftwareSerial.h>
#include <Servo.h>

Servo servoLook;                                  //Create an object to control the servo
// twelve servo objects can be created on most boards

static int pos = 0;    // variable to store the servo position
// SoftwareSerial softSerial(2, 3);

int trigPin = 10;      // trig pin of HC-SR04

int echoPin = 11;     // Echo pin of HC-SR04
long duration, distance;
byte stopDist = 50;                               //Minimum distance from an object to stop in cm
float timeOut = 2*(maxDist+10)/100/340*1000000;   //Maximum time to wait for a return signal


// Define color sensor pins
#define S0 4
#define S1 6
#define S2 7
#define S3 8
#define sensorOut 9
#define LEFT 0;
#define RIGHT 1;
#define END 2;
// Calibration Values
// *Get these from Calibration Sketch
int redMin = 15; // Red minimum value
int redMax = 160; // Red maximum value
int greenMin = 17; // Green minimum value
int greenMax = 180; // Green maximum value
int blueMin = 15; // Blue minimum value
int blueMax = 140; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;
static int color;
char junk;
String inputString="";

void setup()                    // run once, when the sketch starts
{
  // softSerial.begin(9600);
 Serial.begin(9600);  
  myservo.attach(5);
  
//setup of color sensor
	// Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);
  	// Set Frequency scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

  //end setup of color sensor
  pinMode(trig,OUTPUT);                           //Assign ultrasonic sensor pin modes
  pinMode(echo,INPUT);
}

int checkDirection()                                            //Check the left and right directions and decide which way to turn
{
  int distances [2] = {0,0};                                    //Left and right distances
  int turnDir = 1;                                              //Direction to turn, 0 left, 1 reverse, 2 right
  servoLook.write(180);                                         //Turn servo to look left
  delay(500);
  distances [0] = getDistance();                                //Get the left object distance
  servoLook.write(0);                                           //Turn servo to look right
  delay(1000);
  distances [1] = getDistance();                                //Get the right object distance
  if (distances[0]>=200 && distances[1]>=200)                   //If both directions are clear, turn left
    turnDir = 0;
  else if (distances[0]<=stopDist && distances[1]<=stopDist)    //If both directions are blocked, turn around
    turnDir = 1;
  else if (distances[0]>=distances[1])                          //If left has more space, turn left
    turnDir = 0;
  else if (distances[0]<distances[1])                           //If right has more space, turn right
    turnDir = 2;
  return turnDir;
}
int getDistance()                                   //Measure the distance to an object
{
  unsigned long pulseTime;                          //Create a variable to store the pulse travel time
  int distance;                                     //Create a variable to store the calculated distance
  digitalWrite(trig, HIGH);                         //Generate a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pulseTime = pulseIn(echo, HIGH, timeOut);         //Measure the time for the pulse to return
  distance = (float)pulseTime * 340 / 2 / 10000;    //Calculate the object distance based on the pulse time
  return distance;
}
void look()
{
  servoLook.write(90);                            //Set the servo to look straight ahead
  delay(750);
  int distance = getDistance();                   //Check that there are no objects ahead
  if(distance >= stopDist)                        //If there are no objects within the stopping distance, move forward
  {
    moveForward();
  }
  while(distance >= stopDist)                     //Keep checking the object distance until it is within the minimum stopping distance
  {
    distance = getDistance();
    delay(250);
  }
  stopMove();                                     //Stop the motors
  int turnDir = checkDirection();                 //Check the left and right object distances and get the turning instruction
  Serial.print(turnDir);
  switch (turnDir)                                //Turn left, turn around or turn right depending on the instruction
  {
    case 0:                                       //Turn left
      turnLeft (400);
      break;
    case 1:                                       //Turn around
      turnLeft (700);
      break;
    case 2:                                       //Turn right
      turnRight (400);
      break;
  }
}
void loop()
{
read_color();


    // Serial.println(inputString);
        // clear the serial buffer
    
    char buf[]={inputString[0],inputString[1],inputString[2],inputString[3],inputString[4],'\0'};
     
    Serial.write(buf,5);
  
}
void read_color()
{
  // Read Red value
	redPW = getRedPW();
	// Map to value from 0-255
	redValue = map(redPW, redMin,redMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Read Green value
	greenPW = getGreenPW();
	// Map to value from 0-255
	greenValue = map(greenPW, greenMin,greenMax,255,0);
	// Delay to stabilize sensor
	delay(200);

	// Read Blue value
	bluePW = getBluePW();
	// Map to value from 0-255
	blueValue = map(bluePW, blueMin,blueMax,255,0);
	// Delay to stabilize sensor
	delay(200);
 
 if((redValue>greenValue && greenValue>blueValue) || (redValue>blueValue && blueValue>greenValue) )
 {
   color=0;
 } 
 else if(greenValue>redValue && redValue>blueValue || greenValue>blueValue && blueValue>redValue)
 {
   color=1;
 } 
 if(blueValue>greenValue && greenValue>redValue || blueValue>redValue && redValue>greenValue)
 {
   color=2;
 } 
 
 
  

}
// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

void rotatebracketleft()
{
  if(pos-15>TURN_MIN)
    pos=pos-15;
    myservo.write(pos);
  delay(100);
  //communicate to rotate srvro to left
}

