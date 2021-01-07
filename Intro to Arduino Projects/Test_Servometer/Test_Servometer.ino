#include<Servo.h>

Servo penMotor;
//Servo lightMotor;

int MOTORPIN = 3;
//int LIGHTMOTORPIN = 5;

void setup() {
  penMotor.attach(MOTORPIN);
  //lightMotor.attach(LIGHTMOTORPIN);
}

void loop() {
  penMotor.write(15); //any value between 0 and 180
  delay(500);
  penMotor.write(50);
  
}
