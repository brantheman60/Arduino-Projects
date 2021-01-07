//brink the two lights, LED and external LED, oppositely

void setup(){
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop(){
  
  //13 on, 10 off
  digitalWrite(13, HIGH);
  digitalWrite(10, LOW);
  delay(100);
  
  //13 off, 10 on
  digitalWrite(13, LOW);
  digitalWrite(10, HIGH);
  delay(500);
}
