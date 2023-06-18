String text;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available())
  {
    delay(10);
     char c=Serial.read();
     text += c;
         
  }
 if(text.length()>0)
 {
  if(text=="20 volt")
  {
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
  }
 text="";
 }
}
