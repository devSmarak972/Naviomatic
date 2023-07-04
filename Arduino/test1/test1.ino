#include <SoftwareSerial.h>
#include <Servo.h>
// variable to store the servo position
Servo myservo;  // create servo object to control a servo
Servo shootservo;
#define DEBUG true
#define TURN_MAX 60
#define TURN_MIN 0
#define BUFFER_SIZE 1
//forward motors
// left connections
#define enA1 5
#define inA1 2
#define inA2 3
// right connections
#define enA2 6  //we will join all wheels pwm
#define inA3 4
#define inA4 7

// back motors
//left
#define enB1 10
#define inB1 8
#define inB2 9
//right
#define enB2 11
#define inB3 12
#define inB4 13
static int pos = 0;  // variable to store the servo position
static int shootpos = 0;

//Receiver Arduino Board Code
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
  Serial.write("b");

}
char inputString[1] ;
char cmd = '_';
char junk;
void loop() {

int rxlen = Serial.available(); // number of bytes available in Serial buffer
  if (rxlen > 0) {
    int rlen; // number of bytes to read
    if (rxlen > BUFFER_SIZE) // check if the data exceeds the buffer size
      rlen = BUFFER_SIZE;    // if yes, read BUFFER_SIZE bytes. The remaining will be read in the next time
    else
      rlen = rxlen;

    // read the incoming bytes:
    rlen = Serial.readBytes(inputString, rlen);

    // TODO: PROCESS THE INCOMING DATA HERE
  if(rlen>0)
    if (inputString[0] == 'F' || inputString[0] == 'B' || inputString[0] == 'R' || inputString[0] == 'L' || inputString[0] == 'E' || inputString[0] == 'Q' || inputString[0] == 'C' || inputString[0] == 'Z' || inputString[0] == 'P' || inputString[0] == 'O' || inputString[0] == 'L' || inputString[0] == 'K' || inputString[0] == 'N' || inputString[0] == 'M')
      cmd = inputString[0];
  
  }


  // Serial.write(cmd);
  if (cmd == 'F') {
    // Serial.println("inf fwd");
    forward();
  }
  if (cmd == 'B') {
    reverse();
  }
  if (cmd == 'R') {
    right();
  }
  if (cmd == 'L') {
    left();
  }
  if (cmd == 'E') {
    forwardright();
  }
  if (cmd == 'Q') {
    forwardleft();
  }
  if (cmd == 'C') {
    backwardright();
  }
  if (cmd == 'Z') {
    backwardleft();
  }
  if (cmd == 'P') {
    rotateclockwise();
  }
  if (cmd == 'O') {
    rotateanticlockwise();
  }
  if (cmd == 'L') {
    rotatebracketright();
  }
  if (cmd == 'K') {
    rotatebracketleft();
  }
  if (cmd == 'N') {
    stopbot();
  }
  if (cmd == 'M') {
    shoot();
  }
   delay(200);
}
void BLFORWARD() {
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
}
void BLBACKWARD() {
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
}
void BRFORWARD() {
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, HIGH);
}
void BRBACKWARD() {
  digitalWrite(inB3, HIGH);
  digitalWrite(inB4, LOW);
}
void FLFORWARD() {
  digitalWrite(inA3, HIGH);
  digitalWrite(inA4, LOW);
}
void FLBACKWARD() {
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, HIGH);
}
void FRFORWARD() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
}
void FRBACKWARD() {
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
}
void FLSTOP() {
  digitalWrite(inA3, LOW);
  digitalWrite(inA4, LOW);
}
void FRSTOP() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
}
void BRSTOP() {
  digitalWrite(inB3, LOW);
  digitalWrite(inB4, LOW);
}
void BLSTOP() {
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);
}
void forward() {
  FLFORWARD();
  FRFORWARD();
  BLFORWARD();
  BRFORWARD();
  analogWrite(enA1, 50);
  analogWrite(enA2, 50);
  analogWrite(enB1, 50);
  analogWrite(enB2, 50);
}

void reverse() {
  FLBACKWARD();
  FRBACKWARD();
  BLBACKWARD();
  BRBACKWARD();
  analogWrite(enA1, 50);
  analogWrite(enA2, 50);
  analogWrite(enB1, 50);
  analogWrite(enB2, 50);
}

void right() {
  FLFORWARD();
  FRBACKWARD();
  BRFORWARD();
  BLBACKWARD();
  analogWrite(enA1, 50);
  analogWrite(enA2, 50);
  analogWrite(enB1, 50);
  analogWrite(enB2, 50);
}

void left() {
  FLBACKWARD();
  FRFORWARD();
  BLBACKWARD();
  BRFORWARD();
  analogWrite(enA1, 50);
  analogWrite(enA2, 50);
  analogWrite(enB1, 50);
  analogWrite(enB2, 50);
}
void forwardright() {
  FLFORWARD();
  BRFORWARD();
  FRSTOP();
  BLSTOP();
  analogWrite(enA1, 50);
  analogWrite(enA2, 50);
  analogWrite(enB1, 50);
  analogWrite(enB2, 50);

  // digitalWrite(inA3, LOW);
  // digitalWrite(inA4, LOW);

  // digitalWrite(inB1, LOW);
  // digitalWrite(inB2, LOW);
}
void forwardleft() {
  FRFORWARD();
  BLFORWARD();
  FLSTOP();
  BRSTOP();
  analogWrite(enA1, 50);
  analogWrite(enA2, 50);
  analogWrite(enB1, 50);
  analogWrite(enB2, 50);

  // digitalWrite(inA1, LOW);
  // digitalWrite(inA2, LOW);

  // digitalWrite(inB3, LOW);
  // digitalWrite(inB4, LOW);
}
void backwardright() {

  FRBACKWARD();
  BLBACKWARD();
  BRSTOP();
  FLSTOP();
  analogWrite(enA1, 50);
  analogWrite(enA2, 50);
  analogWrite(enB1, 50);
  analogWrite(enB2, 50);

  // digitalWrite(inA1, LOW);
  // digitalWrite(inA2, LOW);

  // digitalWrite(inB3, LOW);
  // digitalWrite(inB4, LOW);
}
void backwardleft() {
  FLBACKWARD();
  BRBACKWARD();
  FRSTOP();
  BLSTOP();
  analogWrite(enA1, 50);
  analogWrite(enA2, 50);
  analogWrite(enB1, 50);
  analogWrite(enB2, 50);

  // digitalWrite(inA3, LOW);
  // digitalWrite(inA4, LOW);

  // digitalWrite(inB1, LOW);
  // digitalWrite(inB2, LOW);
}
void rotateclockwise() {
  FLFORWARD();
  FRBACKWARD();
  BRBACKWARD();
  BLFORWARD();
  analogWrite(enA1, 1);
  analogWrite(enA2, 1);
  analogWrite(enB1, 1);
  analogWrite(enB2, 1);
}
void rotateanticlockwise() {
  FLBACKWARD();
  FRFORWARD();
  BRFORWARD();
  BLBACKWARD();
  analogWrite(enA1, 1);
  analogWrite(enA2, 1);
  analogWrite(enB1, 1);
  analogWrite(enB2, 1);
}
void stopbot() {

  FRSTOP();
  FLSTOP();
  BRSTOP();
  BLSTOP();
  analogWrite(enA1, 0);
  analogWrite(enA2, 0);
  analogWrite(enB1, 0);
  analogWrite(enB2, 0);

  // digitalWrite(inA1, LOW);
  // digitalWrite(inA2, LOW);

  // digitalWrite(inA3, LOW);
  // digitalWrite(inA4, LOW);

  // digitalWrite(inB1, LOW);
  // digitalWrite(inB2, LOW);

  // digitalWrite(inB3, LOW);
  // digitalWrite(inB4, LOW);
}

void shoot() {
  shootpos = 50;
  shootservo.write(shootpos);
  delay(200);
  shootpos = 0;
  shootservo.write(shootpos);
  delay(200);
  //communicate the other arduino to shoot
}
void rotatebracketright() {

  FRSTOP();
  FLSTOP();
  BRSTOP();
  BLSTOP();

  if (pos + 15 < TURN_MAX)
    pos = pos + 15;
  myservo.write(pos);

  delay(50);
  //communicate to rotate srvro to right
}
void rotatebracketleft() {
  FRSTOP();
  FLSTOP();
  BRSTOP();
  BLSTOP();
  
  if (pos - 15 > TURN_MIN)
    pos = pos - 15;
  myservo.write(pos);
  delay(50);
  //communicate to rotate srvro to left
}
