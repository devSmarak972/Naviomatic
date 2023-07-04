int blink=1000;
// String b;
void setup()
{
    Serial.begin(9600);
     pinMode(13, OUTPUT);
}

void loop()
{
   if ( Serial.available() ) {
    blink=Serial.read();

    blink=(int)(blink*20);
    Serial.println("blink in arduino :");
    Serial.println(blink);
    if(blink<0)blink=1000;
    return; // just runs loop() again immediately
  }
    Serial.println(blink);

  digitalWrite(13, HIGH);
  delay(blink);
  digitalWrite(13, LOW);
  delay(blink);
  

}