String voice;
void setup() {
  Serial.begin(9600);
}

void loop() {                    // put your main code here, to run repeatedly:
  while (Serial.available()){  //Check if there is an available byte to read
  voice = Serial.readString(); //Conduct a serial read
  } 
  if (voice.length() > 0) {
    Serial.println(voice);
voice=""; //Reset the variable after initiating
}
}