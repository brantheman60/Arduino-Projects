#include <QTRSensors.h>
#include <Romi32U4.h>

Romi32U4Motors motors;
Romi32U4LCD lcd;
Romi32U4ButtonA buttonA;

#define NUM_SENSORS 6     // Number of sensors used
#define TIMEOUT     2500  // waits 2500us for sensor outputs to go low
#define EMITTER_PIN QTR_NO_EMITTER_PIN

QTRSensorsRC qtrrc((unsigned char[]) {1, 0, 5, 12, 22, 21},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensors[NUM_SENSORS];

// Use this function to print a variable that 
// has type float to the lcd screen
void lcd_print_float(float num)
{
  // Print digits before decimal
  lcd.print((int)num);

  int decimal_digits = (num - (int)num) * 100;

  lcd.print('.');
  lcd.print(abs(decimal_digits));
}

float get_pid_turning_factor(int error, float Kp, float Kd) 
{
  // The keyword static indicates that this variable should only 
  // be initialized once, the first time the function is called,
  // NOT each time the function is run.
  static int old_error = 0;

  float proportional = error * Kp; //Higher Kp is faster, more unstable

  float derivative = (error - old_error) * Kd; //Higher Kd is slower, more stable
  old_error = error;
  
  return proportional + derivative;
}

// Initializes the Romi, displays a welcome message and calibrates
void setup()
{
  unsigned int counter;

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

  // Always wait for the button to be released so that Romi doesn't
  // start moving until your hand is away from it.
  delay(1000);

  // Auto-calibration: turn right and left while calibrating the
  // sensors.
  for (counter=0; counter<160; counter++)
  {
    if (counter < 40 || counter >= 120)
      motors.setSpeeds(60, 60);
    else
      motors.setSpeeds(-60, -60);

    // This function records a set of sensor readings and keeps
    // track of the minimum and maximum values encountered.  The
    // IR_EMITTERS_ON argument means that the IR LEDs will be
    // turned on during the reading, which is usually what you
    // want.
    qtrrc.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0, 0);
  lcd.clear();
  lcd.print("Press A");
  
  buttonA.waitForButton();
  lcd.clear();
  lcd.print("Go!");
}

// The main function.  This function is repeatedly called by
// the Arduino framework.
void loop()
{
  // Get the position of the line.  Note that we *must* provide
  // the "sensors" argument to read_line() here, even though we
  // are not interested in the individual sensor readings.
  int pos = qtrrc.readLine(sensors, QTR_EMITTERS_ON);

  int error = (2500 - pos) / 100;

  // Pass your Kp and Kd to this function to calculate the turning factor
  float turn_factor = get_pid_turning_factor(error, 14, 2); //error, kP, kD
  
  lcd.clear();
  lcd.print(pos);
  lcd.gotoXY(0, 1);
  lcd_print_float(turn_factor);

  /* TODO add code to set motor speeds based on the value of turn_factor
   *  The larger the absolute value of turn factor, the sharper the turn. 
   *  The sign of turn factor indicates the direction of turn 
   *  (you can test it to figure out which is left and which is right)
   *  
   *  Hint: Have a base speed that the turn factor is added and/or subtracted
   *        from in order to make the robot turn
   */
  motors.setSpeeds(-(125-turn_factor), 125+turn_factor);

  // Make sure to make this delay shorter when writing your algorithm
  delay(5);
}
