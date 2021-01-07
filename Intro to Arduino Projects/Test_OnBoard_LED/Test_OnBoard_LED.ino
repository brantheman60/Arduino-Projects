//code to blink the on-board LED

void setup(){
  pinMode(13, OUTPUT);
}

void loop(){
  /* Say "SOS in Morse Code
   * S: * * *
   * O: - - -
   * S: * * *
   */

  for(int i=0; i<3; i++)
  {
    digitalWrite(13, HIGH); //ON, TRUE, HIGH, 5V, and 1 are all synonymous
    delay(100);
    digitalWrite(13, LOW); //OFF, FALSE, LOW, 0V, and 0 are all synonymous
    delay(100);
  }
  delay(400);
  
  for(int i=0; i<3; i++)
  {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
  
  for(int i=0; i<3; i++)
  {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
  delay(1000);

}
