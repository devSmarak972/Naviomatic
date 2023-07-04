//Receiver Arduino Board Code
char mystring[20];               //Initialized variable to store receive
void setup() {
 Serial.begin(9600);  
           // set the baud rate to 9600, same should be of your Serial Monitor
 pinMode(13, OUTPUT);           // Begin the Serial at 9600 Baud
}
String inputString="";
char junk;
void loop() {
  if(Serial.available())
  {
while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
     while (Serial.available() > 0)  
    { 
      junk = Serial.read() ; 
      } 
 if(inputString == "a"){         //in case of 'a' turn the LED on
      digitalWrite(13, HIGH);  
    }else if(inputString == "b"){   //incase of 'b' turn the LED off
      digitalWrite(13, LOW);
    }
        inputString = "";
}
}

