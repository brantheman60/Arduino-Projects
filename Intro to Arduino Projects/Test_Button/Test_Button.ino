int BUTTONPIN = 5;
int LEDPIN = 13;
int POTPIN = A2;

//potentiometer controls the rate of the blinking on-board LED light
//if button is pressed, the rate of the blinking LED light doubles

void setup() {
  pinMode(BUTTONPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(POTPIN, INPUT);
}

void loop() {
  int buttonVal = digitalRead(BUTTONPIN);
  
  /**
  if(buttonVal == HIGH)
    //digitalWrite(LEDPIN, HIGH);
    digitalWrite(LEDPIN, LOW);
  else
    //digitalWrite(LEDPIN, LOW);
    digitalWrite(LEDPIN, HIGH);
  **/

  int potVal = analogRead(POTPIN);
  int blinkTime = potVal;
  
  if(buttonVal == LOW)
  {
    digitalWrite(LEDPIN, HIGH);
    delay(blinkTime);
    digitalWrite(LEDPIN, LOW);
    delay(blinkTime);
  }
  else
  {
    digitalWrite(LEDPIN, HIGH);
    delay(blinkTime / 2);
    digitalWrite(LEDPIN, LOW);
    delay(blinkTime / 2);
  }
}
