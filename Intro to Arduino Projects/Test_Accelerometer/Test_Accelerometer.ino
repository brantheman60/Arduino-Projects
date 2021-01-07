int XPIN = A0;
int YPIN = A1;
int ZPIN = A2;

int LEDPIN = A3;

void setup() {
  pinMode(XPIN, INPUT);
  pinMode(YPIN, INPUT);
  pinMode(ZPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //serial feedback like: x,y,z newline
  Serial.print(analogRead(XPIN));
  Serial.print(",");
  Serial.print(analogRead(YPIN));
  Serial.print(",");
  Serial.println(analogRead(ZPIN));

  int ledLight = map(analogRead(XPIN), 0, 1023, 0, 255);
  analogWrite(LEDPIN, ledLight);
  delay(100);

}
