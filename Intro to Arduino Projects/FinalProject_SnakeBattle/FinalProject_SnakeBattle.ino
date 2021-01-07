#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

int snake1[8][2] =
  { {0,0}, {1,0}, {2,0}, {3,0},
    {4,0}, {5,0}, {6,0}, {7,0} };
int snake2[8][2] =
  { {7,7}, {6,7}, {5,7}, {4,7},
    {3,7}, {2,7}, {1,7}, {0,7} };

int head1X = 7, head1Y = 0;
int head2X = 0, head2Y = 7;
String head1Dir = "down";
String head2Dir = "up";

int gameState = 3; //3 is preparing, 2 is "321 GO", 1 is cont. playing, 0 is gameover
boolean player1Wins = false;
boolean player2Wins = false;
int player1Score = 0;
int player2Score = 0;

#define blue1 8
#define blue2 9
#define blue3 10

static const uint8_t PROGMEM
  countdown_3[] =
  { B11111111,
    B00111000,
    B00000100,
    B00111000,
    B00000100,
    B00000100,
    B00111000,
    B11111111 },
  countdown_2[] =
  { B11111111,
    B00111000,
    B00000100,
    B00011000,
    B00100000,
    B00100000,
    B00111100,
    B11111111 },
  countdown_1[] =
  { B11111111,
    B00011000,
    B00101000,
    B00001000,
    B00001000,
    B00001000,
    B00111110,
    B11111111 },
  countdown_GO[] =
  { B11111111,
    B01110111,
    B10000101,
    B10000101,
    B10110101,
    B10010101,
    B01110111,
    B11111111 };


void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(blue1, OUTPUT);
  pinMode(blue2, OUTPUT);
  pinMode(blue3, OUTPUT);

  
  Serial.begin(9600);
  Serial.println("Snake Battle Test");
  
  matrix.begin(0x70);  // pass in the address
}





void draw321GO()
{
  Serial.print("Getting ready...");
  matrix.clear();
  matrix.drawBitmap(0, 0, countdown_3, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  matrix.drawBitmap(0, 0, countdown_2, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  matrix.drawBitmap(0, 0, countdown_1, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  matrix.drawBitmap(0, 0, countdown_GO, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
}

boolean hitsSnake (int x, int y) //enter any point
{
  for(int i=0; i<8; i++)
  {
    if(x==snake1[i][0] && y==snake1[i][1]) return true;
    if(x==snake2[i][0] && y==snake2[i][1]) return true;
  }
  return false;
}

boolean validHeadMove (int headNum) //checks if the head (1 or 2) is permitted to move that direction
{
  if(headNum==1)
  { 
    //Snake 1
    if(head1Dir.equals("right"))
      {if(head1X!=7 && !hitsSnake(head1X + 1, head1Y)) return true; else return false;}
    else if(head1Dir.equals("left"))
      {if(head1X!=0 && !hitsSnake(head1X - 1, head1Y)) return true; else return false;}
    else if(head1Dir.equals("up"))
      {if(head1Y!=0 && !hitsSnake(head1X, head1Y - 1)) return true; else return false;}
    else if(head1Dir.equals("down"))
      {if(head1Y!=7 && !hitsSnake(head1X, head1Y + 1)) return true; else return false;}
  }
  else if(headNum==1)
  {
    //Snake 2
    Serial.println(head2Dir);
    if(head2Dir.equals("right"))
      {if(head2X!=7 && !hitsSnake(head2X + 1, head2Y)) return true; else return false;}
    else if(head2Dir.equals("left"))
      {if(head2X!=0 && !hitsSnake(head2X - 1, head2Y)) return true; else return false;}
    else if(head2Dir.equals("up"))
      {if(head2Y!=0 && !hitsSnake(head2X, head2Y - 1)) return true; else return false;}
    else if(head2Dir.equals("down"))
      {if(head2Y!=7 && !hitsSnake(head2X, head2Y + 1)) return true; else return false;}
  }
  
  //return true;
}

void setSnake(int headNum)
{
  if(headNum==1)
  {
    for(int i=0; i<7; i++)
    {
      snake1[i][0] = snake1[i+1][0]; Serial.print(snake1[i][0]); Serial.print(",  ");
      snake1[i][1] = snake1[i+1][1]; Serial.println(snake1[i][1]);
    }
    snake1[7][0] = head1X; Serial.print(snake1[7][0]); Serial.print(",  ");
    snake1[7][1] = head1Y; Serial.println(snake1[7][1]);
  }
  else if(headNum==2)
  {
    for(int i=0; i<7; i++)
    {
      snake2[i][0] = snake2[i+1][0];
      snake2[i][1] = snake2[i+1][1];
    }
    snake2[7][0] = head2X;
    snake2[7][1] = head2Y;
  }
}





void loop() {
  matrix.clear();
  if(gameState==3) //or activate when button is pressed
  {
    matrix.drawLine(0,0, 7,0, LED_ON);
    matrix.drawLine(0,7, 7,7, LED_ON);
    matrix.writeDisplay();
    delay(3000);
    gameState--;
    return;
  }
  else if (gameState==2)
  {
    draw321GO();
    gameState--;
    Serial.println("Game is starting!");
    return;
  }
  else if (gameState==1)
  {
    matrix.clear();
  }
  else if (gameState==0)
  {
    if(player1Wins)
    {
      Serial.println("Player 1 Wins!");
      player1Score++;
      if(player1Score>=1) digitalWrite(red1, HIGH);
    }
    else if(player2Wins)
    {
      Serial.println("Player 2 Wins!");
      player2Score++;
      if(player2Score>=1) digitalWrite(blue1, HIGH);
    }
    delay(3000);
    //reset
    matrix.clear();
    matrix.writeDisplay();
    delay(1000);
    gameState = 3;
    player1Wins = false;
    player2Wins = false;
    for(int i=0; i<8; i++)
    {
      snake1[i][0] = i; snake1[i][1] = 0;
      snake2[i][0] = 7-i; snake2[i][1] = 7;
    }
    
    head1X = 7, head1Y = 0;
    head2X = 0, head2Y = 7;
    head1Dir = "down";
    head2Dir = "up";
  }
  
  int joy1x = 511 - analogRead(A1);
  int joy1y = 511 - analogRead(A0);

  int joy2x = 511 - analogRead(A3);
  int joy2y = 511 - analogRead(A2);

  //Snake 1: read head
  if(joy1x>0 && abs(joy1x) > abs(joy1y) + 100)
    head1Dir = "right";
  else if(joy1x<0 && abs(joy1x) > abs(joy1y) + 100)
    head1Dir = "left";
  else if(joy1y>0 && abs(joy1y) > abs(joy1x) + 100)
    head1Dir = "up";
  else if(joy1y<0 && abs(joy1y) > abs(joy1x) + 100)
    head1Dir = "down";

  //Snake 1: move head, or end game
  if(validHeadMove(1))
  {
    if(head1Dir.equals("right")) head1X++;
    else if(head1Dir.equals("left")) head1X--;
    else if(head1Dir.equals("up")) head1Y--;
    else if(head1Dir.equals("down")) head1Y++;
  }
  else
  {
    player2Wins=true;
    gameState = 0;
    return;
  }
  //Snake 1: update snake
  setSnake(1);

  //Snake 2: read head
  if(joy2x>0 && abs(joy2x) > abs(joy2y) + 100)
    head2Dir = "right";
  else if(joy2x<0 && abs(joy2x) > abs(joy2y) + 100)
    head2Dir = "left";
  else if(joy2y>0 && abs(joy2y) > abs(joy2x) + 100)
    head2Dir = "up";
  else if(joy2y<0 && abs(joy2y) > abs(joy2x) + 100)
    head2Dir = "down";

  //Snake 2: move head, or end game
  if(validHeadMove(2))
  {
    if(head2Dir.equals("right")) head2X++;
    else if(head2Dir.equals("left")) head2X--;
    else if(head2Dir.equals("up")) head2Y--;
    else if(head2Dir.equals("down")) head2Y++;
  }
  else
  {
    player1Wins=true;
    gameState = 0;
    return;
  }
  
  //Snake 2: update snake
  setSnake(2);

  
  //draw first snake
  for(int i=0; i<8; i++)
  {
    matrix.drawPixel(snake1[i][0], snake1[i][1], LED_ON);
    matrix.writeDisplay();
    Serial.print("Pixel Drawn");
  }
  //draw second snake
  for(int i=0; i<8; i++)
  {
    matrix.drawPixel(snake2[i][0], snake2[i][1], LED_ON);
    matrix.writeDisplay();
  }
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(300);
  
  
}
