#include <Romi32U4.h>

Romi32U4Motors motors;
Romi32U4ButtonA buttonA;
Romi32U4LCD lcd;

// define variables for the sensor pins and sensor values
int sensor1_pin = A2;
int sensor2_pin = A0;
int sensor1, sensor2;

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
  // Read the value of the sensors
  sensor1 = analogRead(sensor1_pin); //0 to 1024
  sensor2 = analogRead(sensor2_pin);

  // Print the values of the sensors
  lcd.clear();
  lcd.print("1:");
  lcd.print(sensor1);
  lcd.gotoXY(0, 1);
  lcd.print("2:");
  lcd.print(sensor2);

  delay(100); // Pause for 100ms before updating values again
  //Reminder: Left motors is backwards
  sensor2 = sensor2+50;
  
  motors.setLeftSpeed(-map(sensor2, 1024, 0, 30, 300));
  motors.setRightSpeed(map(sensor1, 1024, 0, 30, 300));
  
  if (abs(sensor1 - sensor2)<50 || sensor1+sensor2 >= 1500)
  {
    motors.setLeftSpeed(100);
    motors.setRightSpeed(100);
  }
  if(sensor1+sensor2 <= 600)
  {
    int sensordif = map(sensor1 - sensor2, 300, 0, 0, 100); //positive if left is darker, so should rotate right
    motors.setLeftSpeed(sensordif); 
    motors.setRightSpeed(sensordif);
  }
  if(sensor1+sensor2 <= 300)
  {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
  }
}
