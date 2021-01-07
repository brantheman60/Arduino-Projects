// blink the two lights oppositely
// and change the delay between blinks based on
// a potentiometer's position

void setup(){
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A0, INPUT);

  Serial.begin(9600); //prepare to read data at rate of 9600 bits per second (9600 baud)
}

void loop(){
  int potVal = analogRead(A0); //can store numbers between 0 and 1023

  Serial.println(potVal);
  
  digitalWrite(13, HIGH);
  digitalWrite(10, LOW);
  delay(potVal);
  
  digitalWrite(13, LOW);
  digitalWrite(10, HIGH);
  delay(potVal);
}
