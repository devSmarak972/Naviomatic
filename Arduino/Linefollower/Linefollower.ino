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
//**********5 Channel IR Sensor Connection**********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A4
//*************************************************//

// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

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


void setup() {
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
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
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
  
}
static int prev_state=0;
static int state=0;
void loop() {
  //Reading Sensor Values
  int s1 = digitalRead(ir1);  //Left Most Sensor
  int s2 = digitalRead(ir2);  //Left Sensor
  int s3 = digitalRead(ir3);  //Middle Sensor
  int s4 = digitalRead(ir4);  //Right Sensor
  int s5 = digitalRead(ir5);  //Right Most Sensor


  //if only middle sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 0) && (s5 == 0))
  {
    //go forward
   state=0;
  }
  
  //if only left sensor detects black line
  if((s1 == 0) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //going right with less speed
state=1;
  }
  
  //if only left most sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //going right with full speed 
state=2;
  }

  //if only right sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 0))
  {
    //going left with less speed 
state=3;
  }

  //if only right most sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    //going left with full speed 
state=4;
  }

  //if middle and right sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    //going left with lesser speed
    state=5;
// left(100);
  }

  //if middle and left sensor detects black line
  if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0))
  {
    //going right with lesser speed 
    state=6;
// right(100);
  }

  //if middle, left and left most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0))
  {
    //going right with full speed 
    state=7;
    // rotateanticlockwise(255);
//  right(255);
  }

  //if middle, right and right most sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    state=8;
    // rotateclockwise(255);

  }

  //if all sensors are on a black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    state=9;
    //stop
stop();
  }
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    state=10;
// junction detected
  }
  if(state==0)
  forward();
  else if(state==1)
     right(127);
  else if(state==2)
     right(255);
  else if(state==3)
     left(127);
  else if(state==4)
     left(255);
  else if(state==5)
     left(100);
  else if(state==6)
     right(100);
  else if(state==7)
      rotateanticlockwise(255);
  else if(state==8)
      clockwise(255);
  else if(state=10)
{
  read_color();
  while()
  if(color==LEFT)
  {
    
    rotateclockwise();
  }
  else if(color==RIGHT)
  {
    rotateanticlockwise();
  }
}  
      
     
  prev_state=state;
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

}