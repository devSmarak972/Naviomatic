void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT); 
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(8, OUTPUT); 
}

void loop()
{
 while(!Serial.available()); 
  String data;
  data=Serial.readString();
  Serial.println(data);
  // Serial.println(typeof(data));
 if(data[0]=='1')
 {
 digitalWrite(8,HIGH );
//  Serial.println('1');
 Serial.write("brakeapplied");
 }
 else if(data[0]=='0')
 {
//  Serial.println('0');
 digitalWrite(8,LOW );
 Serial.write("brakestopped");
 }
 else{
    Serial.println("else");

    digitalWrite(LED_BUILTIN,HIGH );
delay(1000);
    digitalWrite(LED_BUILTIN,LOW );

 }
// delay(1000);
 
}
