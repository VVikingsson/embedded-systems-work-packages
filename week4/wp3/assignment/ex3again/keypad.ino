#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define COL1 9
#define COL2 8
#define COL3 7
#define COL4 6

// Matrix for keys, to model the keyboard
const char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Arrays to help transition physical layout into code
int rowPins[4] = {ROW1, ROW2, ROW3, ROW4};
int colPins[4] = {COL1, COL2, COL3, COL4};

// Reads pressed key from the keyboard.
void readKeyboard();

void setup() {
  Serial.begin(9600);     // Initialize serial communication with 9600 bps data rate
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);      // Set all row pins to output mode
    digitalWrite(rowPins[i], HIGH);   // Set all rows to 5v as default. This keeps the "drain" closed
    pinMode(colPins[i], INPUT);       // Set all column pins to input mode
  }
}

void loop() {
  readKeyboard();   // Reads the keyboard and prints any keys pressed
  delay(500);       // Wait half a second
}

// This function checks every button by going row for row and setting the row pin to LOW, allowing the 5v from the columns to move if the button was pressed
void readKeyboard() {
  for (int i = 0; i < 4; i++) {     // For each row
    digitalWrite(rowPins[i], LOW);  // Set row to 0v (GND). This opens the "drain" and lets the "high pressure water" run through.
    for (int j = 0; j < 4; j++) {   // For each column
      if (digitalRead(colPins[j]) == LOW) { // This means the button was pressed, the gap between the "high pressure" col and "low pressure" row was bridged with the press of a button
        Serial.print(keys[i][j]); // Print corresponding character
      }
    }
    digitalWrite(rowPins[i], HIGH); // Set row back to 5v to close the "drain" and "lock" the high pressure 5v back in place, even if the button is pressed.
  }
}