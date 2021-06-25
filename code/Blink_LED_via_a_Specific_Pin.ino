/*
  Sketch name: Blink_LED_via_a_Specific_Pin
  Suggested board: Arduino UNO
  Purpose: 
    1. Blink the LED via a specific pin.
    2. The output pin for the LED can be changed conveniently via the int variable "LED_pin."
  Suggested system setup: 
    The LED is in series with a 220 ohm resistor for avoiding the destruction of the LED.    
  Date: 25 June 2021
  Author: Dr. Hsien-Ching Chung
  ORCID: https://orcid.org/0000-0001-9364-8858
*/


int LED_pin = 3; // LED output pin

// The setup function runs once when you press reset or power the board.
void setup() {
  pinMode(LED_pin, OUTPUT); // Set the output pin for LED
}

// The loop function runs over and over again forever.
void loop() {
  digitalWrite(LED_pin, HIGH);   // Turn the LED on (HIGH is the voltage level)
  delay(1000);                   // wait for 1000 ms
  digitalWrite(LED_pin,  LOW);   // Turn the LED off by making the voltage LOW
  delay(2000);                   // Wait for 1000 ms
}
