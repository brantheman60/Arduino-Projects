#include <Romi32U4.h>

Romi32U4Motors motors;
Romi32U4ButtonA buttonA;
Romi32U4LCD lcd;

// Run once, when the sketch starts
void setup()
{
  uint16_t batteryLevel;

  // Loop the code within { } until A is pressed
  while (!buttonA.isPressed()) {
    // read the battery level and store it in a variable
    batteryLevel = readBatteryMillivolts();
    
    lcd.clear();  // clear the LCD
    lcd.print("B=");
    lcd.print(batteryLevel); // print the battery voltage 
    lcd.print("mV");
    lcd.gotoXY(0, 1);
    lcd.print("Press A");

    delay(100); // Pause for 100ms
  }
  lcd.clear();
  
  delay(500);
}

// Run over and over again
void loop()
{
  ledYellow(1);
  delay(500);
  ledYellow(0);
  delay(500);

  motors.setLeftSpeed(100);
  motors.setRightSpeed(100);
  delay(1000);

  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  delay(1000);
}
