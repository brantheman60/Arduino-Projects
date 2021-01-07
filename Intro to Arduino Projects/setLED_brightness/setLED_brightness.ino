/*
 * LED
 * This program sets the brightness of a single LED
 */

int setLED = 180; //represent the output brightness for the LED (0-255)
const int ledPIN = 9; //name output pin to LED


void setup() {
  pinMode(ledPIN, OUTPUT); //initialize pin for output

}

void loop() {
  analogWrite(ledPIN, setLED); //output PWM signal to ledPin with duty cycle of setLED/255

}
