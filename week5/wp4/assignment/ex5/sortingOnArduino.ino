/*
- The program runs inside loop() and checks buttons using polling (digitalRead).

- If condition = 0 then we wait for the first red button to be pressed.
- If condition = 1 then we count the green button presses.
- If condition = 2 then we generate random numbers and sort them.
- If condition = 3 then we display the sorted numbers on the NeoPixel ring.

- Each green button press will increases the numberCount by 10.
- Red button (second press) starts number generation and sorting.
- Yellow button resets the whole system.

- Random numbers are generated between 1 and 96 (same as total number of LEDs in the 8x12 LED matrix).
- This is because each number is shown by lighting that many LEDs on the matrix.

- Array sorting is used where it compares two elements and swaps them if needed, so the array becomes sorted in ascending order.

- A wait symbol is shown on the LED matrix before sorting starts, it's a smiley face :)
- After sorting, the numbers are displayed one by one using LED count on the matrix.
- When all numbers are displayed, the same sorted numbers are shown again automatically.
- If the yellow button is pressed at any time, the system resets completely.

*/

#include <Arduino_LED_Matrix.h>


// This defines how many LEDs are in the ring
#define NUM_LEDS 96

// Button pins
#define RED_BUTTON 7
#define GREEN_BUTTON 4
#define YELLOW_BUTTON 2

typedef unsigned char byte; // byte type

// Here we create the NeoPixel ring object
ArduinoLEDMatrix matrix;

// Global Variables

// This stores how many numbers we will generate
int numberCount = 0;

// Maximum array size
#define MAX_SIZE 160
int numbers[MAX_SIZE];

// This keeps track of which stage the system is in
int condition = 0;
// condition 0 = waiting for first red
// condition 1 = counting green presses
// condition 2 = sorting
// condition 3 = displaying

void displayNumbers();
void clearDisplay();
void displayNumbers();
void showWatiAnimation();
void arraySorting();
void generateRandomNumbers();

// Setup

void setup() {

  // Here we set the buttons as input
  pinMode(RED_BUTTON, INPUT);
  pinMode(GREEN_BUTTON, INPUT);
  pinMode(YELLOW_BUTTON, INPUT);

  // Here we initialize the NeoPixel ring
  matrix.begin();

  Serial.begin(9600);
}


// Main Loop

void loop() {
  // Here we first check if the yellow button is pressed
  // This allows us to reset the system at any time
  byte curr_yellow = digitalRead(YELLOW_BUTTON);
  byte curr_red = digitalRead(RED_BUTTON);
  byte curr_green = digitalRead(GREEN_BUTTON);
  byte static prev_yellow = LOW;
  byte static prev_red = LOW;
  byte static prev_green = LOW;

  if (curr_yellow == HIGH && prev_yellow == LOW) {
    resetSystem();
  }
  
  // Condition 0
  // Here we are just waiting for the first red button press
  if (condition == 0) {
    if (curr_red == HIGH && prev_red == LOW) {
      // Here we move to counting mode
      condition = 1;
      delay(100); // small delay
    }
  }


  // Condition 1
  // Here we count how many numbers we want
  else if (condition == 1) {
    if (curr_green == HIGH && prev_green == LOW) {
      // Here we increase the number count by 10
      numberCount += 10;
      Serial.print("Numbers to sort: ");
      Serial.println(numberCount);
    }

    // Here we check for the second red press to start sorting
    if (digitalRead(RED_BUTTON) == HIGH && numberCount > 0) {
      // Here we move to sorting
      condition = 2;
      // Here we generate the random numbers before sorting
      generateRandomNumbers();
    }
  }

  // Condition 2
  // Here we perform the sorting process
  else if (condition == 2) {
    // Here we show a visual wait animation
    showWaitAnimation();
    // Here we sort the array
    arraySorting();
    // After sorting we move to display stage
    condition = 3;
  }

  // Condition 3
  // Here we display the sorted numbers continuously
  else if (condition == 3) {
    displayNumbers();
  }

  prev_green = curr_green;  // Set prev variable
  prev_red = curr_red;  // Set prev variable
  prev_yellow = curr_yellow;    // Set prev variable
}


// Functions


// This function resets everything
void resetSystem() {
  // Here we reset the number count back to zero
  numberCount = 0;
  // Here we move back to the initial stage
  condition = 0;
  clearDisplay(); // clear display
  Serial.println("System restarted");
  delay(500);
}

void clearDisplay() {
  byte frame[8][12] = {0};  // Set all lights to 0
  matrix.renderBitmap(frame, 8, 12);    // Put it on the matrix
}

// This generates random numbers between 1 and NUM_LEDS
void generateRandomNumbers() {
  for (int i = 0; i < numberCount; i++) {   // for each number
    numbers[i] = random(1, NUM_LEDS + 1);   // assign it a random number
    Serial.println(numbers[i]);
  }
}


// This is the array sorting function
void arraySorting() {
  // Here we loop through the whole array
  for (int i = 0; i < numberCount - 1; i++) {
    // Here we compare neighboring elements
    for (int j = 0; j < numberCount - i - 1; j++) {
      // If the current element is bigger than the next one
      if (numbers[j] > numbers[j + 1]) {
        // Here we swap the two values
        int temp = numbers[j];
        numbers[j] = numbers[j + 1];   
        numbers[j + 1] = temp;
      }
    }
  }

  // After this finishes the array is sorted in ascending order
}


// This shows a smiley face while sorting
void showWaitAnimation() {
  byte frame[8][12] = { // =]
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,0,0,1,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
  };
    matrix.renderBitmap(frame, 8, 12);  // Render to matrix
    delay(500);
}


// This displays numbers using LED count
void displayNumbers() {
  // Here we go through each sorted number

  int currentHighestLED = 0;    // FOr keeping track of what LED we have alrighty lit up
  byte frame[8][12] = {0};      // Initialize to 0 to clear smiley face
  for (int i = 0; i < numberCount; i++) {   // For every number
    for (int j = currentHighestLED; j < numbers[i]; j++) {  // FOr every unlit LED up until this number
      int row = j / 12; // Calculate row
      int col = j % 12; // Calculate column
      frame[row][col] = 1;  // turn light on
    }
    matrix.renderBitmap(frame, 8, 12);  // Render to matrix
    delay(500);
    currentHighestLED = numbers[i]; // Update variable
  }
}