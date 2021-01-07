#define LEFT_SENSOR A0
#define RIGHT_SENSOR A2

void setup() {
}

void loop() {
  //Sensor readings between 0 (brightest) and 1023 (darkest)
  int left_light = analogRead(LEFT_SENSOR);
  int right_light = analogRead(RIGHT_SENSOR);
  System.print("Left: ",left_light);
  System.print("Right: ",right_light);
}
