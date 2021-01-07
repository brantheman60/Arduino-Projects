#include <Romi32U4.h>

Romi32U4Motors motors;
Romi32U4ButtonA buttonA;

void setup() {
  // Wait fot he user to press button A
  buttonA.waitForButton();
  delay(1000);

  uint16_t batteryLevel;
  //Loop the code within {} until A is pressed
  while(!ButtonA.isPressed()) //.......
}

void spin (int mSpeed, int mTime) { //-300 <= speed <= 300
  motors.setLeftSpeed(mSpeed);
  motors.setRightSpeed(-mSpeed);
  delay(mTime);
}

void walk (int speed, int time) { //-300 <= speed <= 300
  motors.setLeftSpeed(mSpeed);
  motors.setRightSpeed(mSpeed);
  delay(mTime);
}

void twist (String dir, int speed, int time) { //-300 <= speed <= 300; "cw" or "ccw"
  if(dir.equals("cw"))  {motors.setLeftSpeed(mSpeed); motors.setRightSpeed(0);}
  else if(dir.equals("ccw"))  {motors.setRightSpeed(mSpeed); motors.setLeftSpeed(0);}
  delay(mTime);
}

void loop() {
  ledYellow(1);
  delay(500);
  ledYellow(0);
  delay(500);
  
  motors.setLeftSpeed(100);  //ranges from -300 to 300 inclusive
  motors.setRightSpeed(100);
  delay(1000);

  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  delay(1000);

}
