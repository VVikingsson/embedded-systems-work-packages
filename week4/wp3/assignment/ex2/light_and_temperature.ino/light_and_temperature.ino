// C++ code
//
// It is worth to note that the specification of the assignment handles temperature ranges in a logically flawed way, so this program is not flawless.
// But it follows the specification asked in the course.

#include <math.h> // For logarithm
#include <DHT.h>  // For temp sensor

#define LIGHT_SENSOR A2 // Light sensor pin
#define TEMP_SENSOR A1  // Temp sensor pin
#define GREEN_LED 5     // Green LED pin
#define BLUE_LED 7      // Blue LED pin
#define RED_LED 3       // Red LED pin
#define DELAY 1000      // Define delay constant

DHT dht(TEMP_SENSOR, DHT11);

// States for statemachine
enum State {
  IDLE, // Idle state
  MEASURE,  // Measure state
  LIGHTS    // Update lights state
};
// Variations
enum Variation {
  V_NORMAL, // Normal variation
  V_HIGH,   // High variation
  V_LOW     // Low variation
};

// Updates state and calls functions
void useStateMachine();
// Measures variation between "dependencies"
Variation measureVariation();
// Reads the light and gets percentage
int readLightPercent();
// Updates LEDs
void updateLights(Variation currentVariation);
// Reads temperature celcius
float readTemperature();


State currentState = IDLE;  // Initialize state to idle
Variation currentVariation = V_NORMAL;  // Initialize variation to normal
unsigned long lastTimeStamp = millis() -1000; // initialize last timestamp to one second ago

void setup()
{
  Serial.begin(9600);
  pinMode(BLUE_LED, OUTPUT);  // Set to output
  pinMode(RED_LED, OUTPUT);   // Set to output
  pinMode(GREEN_LED, OUTPUT); // Set to output
  pinMode(TEMP_SENSOR, INPUT);// Set to input
  pinMode(LIGHT_SENSOR, INPUT); // Set to input
} 

void loop()
{
  useStateMachine();  // Use state machine
}

// Updates state and calls functions
void useStateMachine() {
  switch(currentState) {  // Switch on state

    case IDLE:  // If idle
    	if (millis() - lastTimeStamp >= DELAY) {  // If one second passed
        	currentState = MEASURE; // update state
        }
      break;  // Break to not continue switch

    case MEASURE: // If measure
    	currentVariation = measureVariation(); // Measure variation
      lastTimeStamp = millis(); // Get current time
      currentState = LIGHTS;  // Update state
      break;  // Break to not continue switch

    case LIGHTS:  // If state is lights
      updateLights(currentVariation); // Update LEDs based on current variation
      currentState = IDLE;  // Update state
  }
}

// Finds variation between "dependencies"
Variation measureVariation() {
  int lightPercent = readLightPercent();  // get light percentage
  float currentTemp = readTemperature();  // get temperature
  Serial.print("Light: "); Serial.print(lightPercent); Serial.print(" Temp: "); Serial.println(currentTemp);
  Variation variation;  // declare

  if (lightPercent == 0) {  // if lightpercent == 0
    if (currentTemp < -12) variation = V_NORMAL;  // if temp < -12 set normal variation
    else variation = V_HIGH; // else set high variation
  } 
  else if (lightPercent >= 1 && lightPercent <= 20) { // if light between 1-20
    if (currentTemp >= -12 && currentTemp <= 0) variation = V_NORMAL; // if temp in -12-0 set normal variation
    else if (currentTemp > 0) variation = V_HIGH; // if temp > 0 set high variation
    else variation = V_LOW; // else set low variation
  } 
  else if (lightPercent >= 21 && lightPercent <= 60) {  // if light between 21-60
    if (currentTemp >= 0 && currentTemp <= 20) variation = V_NORMAL;  // conditional set normal variation
    else if (currentTemp > 20) variation = V_HIGH;  // if temp > 20, set high variation
    else variation = V_LOW; // else set low variation
  } 
  else if (lightPercent >= 61 && lightPercent <= 100) { // If light between 61-100
    if (currentTemp >= 21) variation = V_NORMAL;  // if temp >= 21, set normal variation
    else variation = V_LOW; // else set low variation
  }

  return variation;
}

// Turns LEDs on and off based on variation
void updateLights(Variation currentVariation) {
  switch (currentVariation) { // switch on variation
    case V_NORMAL:  // Normal variation
      digitalWrite(GREEN_LED, HIGH);  // Turn LED on
      digitalWrite(BLUE_LED, LOW); // Turn LED off
      digitalWrite(RED_LED, LOW); // Turn LED off
      break;
    case V_HIGH:  // High variation
      digitalWrite(BLUE_LED, LOW); // Turn LED off
      digitalWrite(RED_LED, HIGH); // Turn LED on
      digitalWrite(GREEN_LED, LOW); // Turn LED off
      break;
    case V_LOW: // Low variation
      digitalWrite(BLUE_LED, HIGH); // Turn LED on
      digitalWrite(RED_LED, LOW); // Turn LED off
      digitalWrite(GREEN_LED, LOW); // Turn LED off
  }
}

// reads ambient light percentage
int readLightPercent() {
  int raw = analogRead(LIGHT_SENSOR);   // Read raw value
  int lightPercent = map(raw, 1023, 0, 0, 100); // Convert to percentage 0-100. Our module has flipped values, wired in a "pull-up" configuration.
  return lightPercent;
}
// reads temperature
float readTemperature() {
  return dht.readTemperature(); // DHT Library does heavy lifting for us :thumbs_up:
}