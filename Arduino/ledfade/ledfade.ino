int b;
void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT); 
}

void loop()
{
 while(!Serial.available());
 b=Serial.read();
//  Serial.println("in arduino");
//  Serial.println(b);  
Serial.println(b);
 analogWrite(13,b);
}
