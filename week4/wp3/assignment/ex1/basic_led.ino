#define LED_PIN 6
#define DELAY 500

enum State {
  IDLE,
  LIGHT_ON,
  LIGHT_OFF
};

State currentState = IDLE;
int lastTimeStamp = millis() - 500;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  useStateMachine();  // Use state machine
}

void useStateMachine() {
  switch (currentState) { // Switch on current state
    case IDLE:  // If IDLE
      if (millis() - lastTimeStamp >= DELAY) {  // Check timestamp
        currentState = LIGHT_ON;  // Update state
        lastTimeStamp = millis();
      }
      break;  // Break to avoid next case instantly
    case LIGHT_ON:  // If light_on state
      digitalWrite(LED_PIN, HIGH);  // TUrn light on
      Serial.println("Light on");
      if (millis() - lastTimeStamp >= DELAY / 2) {  // wait half a half second
        currentState = LIGHT_OFF; // update state
      }
      break;  // break to avoid next case instantly
    case LIGHT_OFF: // If light_off state
      digitalWrite(LED_PIN, LOW); // Turn light off
      Serial.println("Light off");
      currentState = IDLE;  // Update state
  }
}
