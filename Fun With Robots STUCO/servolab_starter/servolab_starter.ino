#include <Romi32U4.h>
#include "FWR_Servo.h"

#define UP 0
#define DOWN 75 //90 worked well for dot

Romi32U4Motors motors;
Romi32U4ButtonA buttonA;
Romi32U4Encoders encoders;
Romi32U4LCD lcd;
Romi32U4Buzzer buzzer;

FWR_Servo myservo;

int left_count, right_count;

void setup() {

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
  
  myservo.attach(20);
}

//encoders is frustrating, so stick with delay()

void get_update()
{
  lcd.clear();
  lcd.print("L:");
  lcd.print(encoders.getCountsLeft());
  lcd.gotoXY(0,1);
  lcd.print("R:");
  lcd.print(encoders.getCountsRight());
}

void draw_arc(bool ccw, int arclen, int wspeed) //full circle = 3000 at 200
{
  get_update();
  myservo.write(DOWN);
  delay(100);
  int left_count = encoders.getCountsLeft() + arclen;
  int right_count = encoders.getCountsRight() + arclen;
  if (ccw) //getCountsLeft() decreases, getCountsRight() increases
  {
    while(encoders.getCountsRight() < right_count)
      motors.setSpeeds(wspeed,wspeed);
  }
  else //getCountsRight() decreases, getCountsLeft() increases
  {
    while(encoders.getCountsLeft() < left_count)
      motors.setSpeeds(-wspeed,-wspeed);
  }
  myservo.write(UP);
  get_update();
}

void draw_line(bool forw, int len, int wspeed)
{
  get_update();
  myservo.write(DOWN);
  delay(250);
  if (forw) //getCounts() increases
  {  
    int count = encoders.getCountsLeft() - len;
    while(encoders.getCountsLeft() > count)
      motors.setSpeeds(wspeed, -wspeed);
    if(encoders.getCountsLeft() % 1000 == 0) get_update();
  }
  else //getCounts() decreases
  {
    int count = encoders.getCountsLeft() + len;
    while(encoders.getCountsLeft() < count)
      motors.setSpeeds(-wspeed, wspeed);
  }
  myservo.write(UP);
  motors.setSpeeds(0,0);
//  int left_count = encoders.getCountsLeft() + len;
//  int right_count = encoders.getCountsRight() + len;
//  while(encoders.getCountsLeft() < left_count && encoders.getCountsRight() < right_count)
//  {
//    if (forw) motors.setSpeeds(wspeed, -wspeed);
//    else      motors.setSpeeds(-wspeed, wspeed);
//  }
//  myservo.write(UP);
//  get_update();
}

void move_line(bool forw, int len, int wspeed)
{
  get_update();
  if (forw) //getCounts() increases
  {  
    int count = encoders.getCountsLeft() - len;
    while(encoders.getCountsLeft() > count)
      motors.setSpeeds(wspeed, -wspeed);
  }
  else //getCounts() decreases
  {
    int count = encoders.getCountsLeft() + len;
    while(encoders.getCountsLeft() < count)
      motors.setSpeeds(-wspeed, wspeed);
  }
  motors.setSpeeds(0,0);
}

void draw_dot()
{
  get_update();
  myservo.write(DOWN);
  delay(230);
  myservo.write(UP);
}

//Note: encoders.getCountsLeft/Right counts the distance/number of steps, NOT time.
//So, we could make speed as fast as we want!
void loop() {
  Serial.print("Hello");
  myservo.write(UP);
  delay(100);
  
  //draw_arc(false, 3000, 200); //parameters: counter-clockwise, arc length, motor speed
  //draw_line(true, 100, 50); //parameters: forward, line length, motor speed
  
  draw_line(true, 500, 200);
  delay(10000);

  //F ••-•
  draw_dot(); //•
  delay(100);
  move_line(true, 100, 200);
  delay(100);
  draw_dot(); //•
  delay(100);
  move_line(true, 100, 200);
  delay(100);
  draw_line(true, 200, 200); //-
  delay(100);
  move_line(true, 100, 200);
  delay(100);
  draw_dot(); //•
  delay(100);
  move_line(true, 400, 200);
  delay(100);

  //W •--
  draw_dot(); //•
  delay(100);
  move_line(true, 100, 200);
  delay(100);
  draw_line(true, 200, 200); //-
  delay(100);
  move_line(true, 100, 200);
  delay(100);
  draw_line(true, 200, 200); //-
  delay(100);
  move_line(true, 400, 200);
  delay(100);

  //R •-•
  draw_dot(); //•
  delay(100);
  move_line(true, 100, 200);
  delay(100);
  draw_line(true, 200, 200); //-
  delay(100);
  move_line(true, 100, 200);
  delay(100);
  draw_dot(); //•
  delay(100);
  move_line(true, 1000, 200);
  delay(100);
}


/**
  goal = 1000 + goal;

  left_count = encoders.getCountsLeft();
  right_count = encoders.getCountsRight();
  
  while(left_count < goal && right_count < goal){
    motors.setSpeeds(-50, 50);
    delay(10);
    
    left_count = encoders.getCountsLeft();
    right_count = encoders.getCountsRight();
  }
*/
