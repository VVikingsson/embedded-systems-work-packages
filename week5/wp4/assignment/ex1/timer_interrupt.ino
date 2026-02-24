// (C) Aisha Attar, Vijaykrishnan Gopalakrishnan, Ville Vikingsson, group: 25 (2026)
// Work package 4
// Exercise 1
// Submission code: sCnaU7

#define RED_LED 6   // define macro
#define ORANGE_LED 5  // define macro
#define YELLOW_LED 4  // define macro
#define GREEN_LED 3 // define macro
#define BLUE_LED 2  // define macro
#define TMP36 A0  // define macro

void setup() {
  pinMode(RED_LED, OUTPUT);     // Set pin mode
  pinMode(ORANGE_LED, OUTPUT);  // Set pin mode
  pinMode(YELLOW_LED, OUTPUT);  // Set pin mode
  pinMode(GREEN_LED, OUTPUT);   // Set pin mode
  pinMode(BLUE_LED, OUTPUT);    // Set pin mode
  pinMode(TMP36, INPUT);        // Set pin mode

  cli(); // Clear interrupts, enter critical section

  // The arduino uno also has timer0 and timer2, but they work with 8 bits.
  // timer1 is a 16bit timer.
  // It is more appropriate to use for smaller frequencies (larger intervals) because
  // it can count more times before overflowing.
  // The below sets timer1 to interrupt at 1Hz.

  // Timer Counter Control Registers are special memory locations (usually 8 or 16 bits) used for
  // telling the timer exactly how to behave.
  // Setting all the control registers back to 0 ensure we have a known state and eliminate glitchy behavior
  TCCR1A = 0; // Set first half of Timer 1 control registers to 0.
  TCCR1B = 0; // Set second half of Timer 1 control registers to 0.
  TCNT1 = 0;  // Timer CouNTer, the actual number of times the timer has incremented before overflowing. We set this back to 0 to start from... well, 0.

  // OCR = Output Compare Register. Hardware is constantly checking if TCNT == OCR, and if it is, a given event is triggered. (in this case an interrupt).
  // Arduino clock speed == 16 000 000 Hz, 16MHz.
  // What are prescalers?
  OCR1A =  15624; // = (16*10^6) / (1*1024) - 1. Must be < 65536
  // Set Waveform Generation Mode bit. This tells the timer we want it to reset when it reaches the OCR1A value instead of its natural max, 65536
  TCCR1B |= (1 << WGM12); // Timer counter control register 1B
  // Set CS10 and CS12 bits to tell the timer we want to use a prescaler of 1024. This allows us to use the timer for intervals as long as aroudn 4 seconds, but with
  // a lower resolution than smaller prescalers.
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt by setting "Output Compare Interrupt Enable" bit for timer 1 to 1 in the Timer Interrupt Mask for timer 1.
  TIMSK1 |= (1 << OCIE1A);

  sei(); // Set interrupts, exit critical section
}

  // Timer1's interrupt handler
ISR(TIMER1_COMPA_vect){
  static int last_pin = 2;  // Static variable to keep track of the LED that's currently on (needs to be turned off)
  digitalWrite(last_pin, LOW);  // Turn off led
  float temp = get_temperature(); // read temperature
  if (temp <= -10) {  // if temp <= 10
    digitalWrite(BLUE_LED, HIGH); // set LED to high
    last_pin = BLUE_LED;  // remember what LED is on
  } else if (temp <= 0) { // if temp <= 0
    digitalWrite(GREEN_LED, HIGH); // set LED to high
    last_pin = GREEN_LED; // remember what LED is on
  } else if (temp <= 10) { // if temp <= 10
    digitalWrite(YELLOW_LED, HIGH); // set LED to high
    last_pin = YELLOW_LED; // remember what LED is on
  } else if (temp <= 20) {  // if temp <= 20
    digitalWrite(ORANGE_LED, HIGH); // set LED to high
    last_pin = ORANGE_LED; // remember what LED is on
  } else {  // if temp > 20
    digitalWrite(RED_LED, HIGH); // set LED to high
    last_pin = RED_LED; // remember what LED is on
  }
}

void loop() {
  // Do nothing, just wait for interrupt
}


// Reads the current temperature
float get_temperature() {
  int raw = analogRead(TMP36);  // Read raw analog value
  float temp = (raw * (5.0 / 1024) - 0.5) * 100;  // Convert value to temperature
  return temp;
}
