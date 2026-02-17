// C++ code
//

#define LIGHT_SENSOR A0 // Light sensor pin
#define TEMP_SENSOR A1  // Temp sensor pin
#define GREEN_LED 5     // Green LED pin
#define BLUE_LED 7      // Blue LED pin
#define RED_LED 3       // Red LED pin
#define DELAY 1000      // Define delay constant
#define DELAY2 500      // Define delay constant for temperature meter V2.0

// States for statemachine
enum State {
  ST_IDLE, // Idle state
  ST_MEASURE,  // Measure state
  ST_LIGHTS    // Update lights state
};

enum State2 {
  ST2_IDLE,           // Idle state
  ST2_CALCULATE_TEMP  // Calculate temperature and print it to the console state
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


State currentState = ST_IDLE;  // Initialize state to idle
State2 currentState2 = ST2_IDLE;

Variation currentVariation = V_NORMAL;  // Initialize variation to normal
unsigned long lastTimeStamp = millis() -1000; // initialize last timestamp to one second ago
unsigned long lastTimeStamp2 = millis() -500; // Initialize last timestamp to half a second ago

void setup()
{
  pinMode(BLUE_LED, OUTPUT);  // Set to output
  pinMode(RED_LED, OUTPUT);   // Set to output
  pinMode(GREEN_LED, OUTPUT); // Set to output
  pinMode(TEMP_SENSOR, INPUT);// Set to input
  pinMode(LIGHT_SENSOR, INPUT); // Set to input
  Serial.begin(9600);
} 

void loop()
{
  useStateMachine();  // Use state machine
  useStateMachine2(); // Use second state machine
}

// Updates state and calls functions
void useStateMachine() {
  switch(currentState) {  // Switch on state

    case ST_IDLE:  // If idle
    	if (millis() - lastTimeStamp >= DELAY) {  // If one second passed
        	currentState = ST_MEASURE; // update state
        }
      break;  // Break to not continue switch

    case ST_MEASURE: // If measure
    	currentVariation = measureVariation(); // Measure variation
      lastTimeStamp = millis(); // Get current time
      currentState = ST_LIGHTS;  // Update state
      break;  // Break to not continue switch

    case ST_LIGHTS:  // If state is lights
      updateLights(currentVariation); // Update LEDs based on current variation
      currentState = ST_IDLE;  // Update state
  }
}

void useStateMachine2() {
  switch (currentState2) {  // Switch on second state machine's state
    case ST2_IDLE:    // If idle
      if (millis() - lastTimeStamp2 >= DELAY2) {  // Compare timestamps
        currentState2 = ST2_CALCULATE_TEMP;  // Update state
      }
      break;    // break to not continue switch
    case ST2_CALCULATE_TEMP:  // If calculating temp
      float temp = readTemperature(); // read temperature
      Serial.println(temp);       // Print temperature to serial out
      lastTimeStamp2 = millis();  // Update timestamp
      currentState2 = ST2_IDLE;   // Update state
  }
}

// Finds variation between "dependencies"
Variation measureVariation() {
  int lightPercent = readLightPercent();  // get light percentage
  float currentTemp = readTemperature();  // get temperature
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
  int lightPercent = map(raw, 0, 1023, 0, 100); // Convert to percentage 0-100
  return lightPercent;
}
// reads temperature
float readTemperature() {
  int raw = analogRead(TEMP_SENSOR);      // Read raw value
  float milliVolts = raw * (5000.0 / 1024.0); // Convert raw to millivolts: (Reading / 1024) * 5000mV
  float temperature = (milliVolts - 500.0) / 10.0;  // Apply the formula for TMP36
  return temperature;
}