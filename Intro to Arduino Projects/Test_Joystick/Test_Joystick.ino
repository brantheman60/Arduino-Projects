/**
 *  All joysticks have the following configure:
 *  
 *                  |  |  |  |
 *     x=0,y=1023______________ x=0, y=0
 *               |             |
 *               |             |
 *               |             |
 *               |             |
 *               |             |
 *               |             |
 *  x=1023,y=1023|_____________|x=1023, y=0
 *                      *
 */
void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  int xVal1 = analogRead(A0);
  int yVal1 = analogRead(A1);
  int xVal2 = analogRead(A2);
  int yVal2 = analogRead(A3);
  
  Serial.print("xVal1: "); Serial.print(xVal1);    Serial.print("        xVal2: "); Serial.println(xVal2);
  Serial.print("yVal1: "); Serial.print(yVal1);    Serial.print("        yVal2: "); Serial.println(yVal2);

  /**
  short x = 1023 - analogRead(A1) - 511; //values from -511 to 512
  short y = 1023 - analogRead(A0) - 511; //values from -511 to 512
  Serial.print("x: "); Serial.println(x);
  Serial.print("y: "); Serial.println(y);
  */
  
  delay(500);
}
