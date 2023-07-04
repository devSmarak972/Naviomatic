 static int command2=4;
bool DEBUG=true;
// Motor A connections
int enA=9;
int inA1= 4;
int inA2=5;
// Motor B connections
// int enB 10;//we will join all wheels pwm
int inA3=6;
int inA4=7;

int inB1=10;
int inB2=11;
int inB3=12;
int inB4=13;

// String command2;
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

  Serial.begin(4800);
  Serial.println("Setup");
}
//  static int command2=4;
void loop()
{
  analogWrite(enA,255);

 if(Serial.available())  
 command2=Serial.read();
Serial.println(command2);
  if (command2 == 0) 
                {
                  forward();
                 }
                 if (command2 == 1) 
                {
                  reverse();
                 }
                 if (command2 == 2) 
                {
                  right();
                 }
                 if (command2 == 3) 
                {
                  left();
                 }
                  if (command2 == 4) 
                {
                  stopbot();
                 }
                
                 if (command2 == 5) 
                {
                  rotateclockwise();
                 }
                 if (command2 == 6) 
                {
                  rotateanticlockwise();
                 }
            delay(200);
                
               
                 
}

void forward()
{
    analogWrite(enA,255);

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
    analogWrite(enA,255);

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
{  analogWrite(enA,255);

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
    analogWrite(enA,255);

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
    analogWrite(enA,255);

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
  analogWrite(enA,0);

  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, LOW);

  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);  

}

   

 