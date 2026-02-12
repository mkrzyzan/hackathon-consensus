/*
 * ESP32 LED Blinking Program
 * 
 * This program controls an LED connected to GPIO 2 (built-in LED on most ESP32 Dev Modules)
 * The LED will blink with 1 second ON and 1 second OFF intervals.
 * 
 * Hardware Setup:
 * - ESP32 Dev Module C Kit
 * - LED connected to GPIO 2 (or use built-in LED)
 * - If using external LED: connect LED cathode to GND through 220Ω resistor
 * 
 * Pin Assignment:
 * GPIO 2 - This is the built-in LED pin on most ESP32 Dev Modules
 * Alternative pins: GPIO 5, GPIO 18, GPIO 19, GPIO 21, GPIO 22, GPIO 23
 */

#include <Arduino.h>

// Define LED pin - GPIO 2 is the built-in LED on most ESP32 boards
#define LED_PIN 2

// Blink interval in milliseconds
#define BLINK_INTERVAL 1000

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("ESP32 LED Blinking Program Started");
  Serial.printf("LED connected to GPIO %d\n", LED_PIN);
  
  // Configure LED pin as output
  pinMode(LED_PIN, OUTPUT);
  
  // Start with LED off
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Turn LED on
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(BLINK_INTERVAL);
  
  // Turn LED off
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(BLINK_INTERVAL);
}
