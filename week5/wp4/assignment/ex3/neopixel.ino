// (C) Aisha Attar, Vijaykrishnan Gopalakrishnan, Ville Vikingsson, group: 25 (2026)
// Work package 4
// Exercise 1
// Submission code: sCnaU7

#include <Adafruit_NeoPixel.h>  // Pixel ring library

// Define macros
#define TMP36 A0
#define PIXELRING_PIN A1
#define PIXELRING_PIXELS 12
#define LED 2

// gets temperature
float get_temperature();
// sets LEDs to orange relative to temp
void light_positive(float temp);
// Sets LEDs to blue relative to temp
void light_negative(float temp);

// Declare ring
Adafruit_NeoPixel ring(PIXELRING_PIXELS, PIXELRING_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(LED, OUTPUT);	// Set pin mode to output
  pinMode(TMP36, INPUT); // Set pin mode to input
  ring.begin(); // Initialize ring
}

void loop()
{
  float temp = get_temperature(); // Read temperature
  ring.clear(); // Turn all pixels off
  if (temp > 0) { // if temp > 0
    light_positive(temp); // Light up clockwise order with orange
  } else if (temp < 0) {  // if temp < 0
    light_negative(temp); // Light up counter clockwise with blue
  }

  if (temp >= 24) { // if temp >= 24
    digitalWrite(LED, HIGH);  // LED on
  } else {  // else
    digitalWrite(LED, LOW); // LED off
  }
  ring.show();  // Send updates to hardware
  delay(500); // Freeze process for 0.5s
}



// Reads the current temperature
float get_temperature() {
  int raw = analogRead(TMP36);  // Read raw analog value
  float temp = (raw * (5.0 / 1024) - 0.5) * 100;  // Convert value to temperature
  return temp;
}

// Lights orange relative to temp
void light_positive(float temp) {
  int to_light = (int) temp/2;  // two positive degrees = one pixel

  for (int i = 0; i<to_light; i++) {  // For every pixel to light
    ring.setPixelColor(i, 200, 100, 0); // Light it
  }
}
// Lights blue relative to temp
void light_negative(float temp) {
  int to_light = (int) (-temp)/2; // two negative degrees = one pixel

  for (int i = 11; i > 11-to_light; i--) {  // For every pixel to light
    ring.setPixelColor(i, 0, 100, 200); // Light it
  }
}