// (C) Aisha Attar, Vijaykrishnan Gopalakrishnan, Ville Vikingsson, group: 25 (2026)
// Work package 4
// Exercise 1
// Submission code: sCnaU7

#include <Servo.h>  // servo library

#define SERVO_SECONDS 3 // macro for pin
#define SERVO_MINUTES 2 // macro for pin

Servo servo_seconds; // Initialize servo object
Servo servo_minutes; // Initialize servo object
volatile int seconds = 0; // declare seconds as volatile because it can "suddenly" have an "unexpected" value - interrupts
int last_second = -1;      // Will be used to check if something should be executed in loop()
volatile int minutes = 0;    // initialize minutes
volatile int interrupt_counter = 0; // This is necessary because timer2 can't reach a second by itself.

void setup() {
  cli(); // Clear interrupts, enter critical section

  Serial.begin(9600);

  servo_seconds.attach(SERVO_SECONDS);  // set pin
  servo_minutes.attach(SERVO_MINUTES);  // set pin
  // The arduino uno also has timer0 and timer1, they work with 8 bits and 16 bits respectively.
  // timer2 is an 8bit timer, meaning it can increment 255 times before needing to wrap around
  // The reason we use timer2 is to avoid a servo library conflict (servo also uses timer1)
  // The below sets timer2 to interrupt at 100Hz (which we then scale to 1Hz).

  // Timer Counter Control Registers are special memory locations (usually 8 or 16 bits) used for
  // telling the timer exactly how to behave.
  // Setting all the control registers back to 0 ensure we have a known state
  TCCR2A = 0; // Set first half of Timer 2 control registers to 0. 
  TCCR2B = 0; // Set second half of Timer 2 control registers to 0. 
  TCNT2 = 0;  // Timer CouNTer, the actual number of times the timer has incremented before overflowing. We set this back to 0 to start from... well, 0.

  // OCR = Output Compare Register. Hardware is constantly checking if TCNT == OCR, and if it is, a given event is triggered. (in this case an interrupt).
  // Arduino clock speed == 16 000 000 Hz, 16MHz.
  OCR2A =  155; // (16000000 / (1024 * 100)) - 1     Clock / (Prescaler * Target_Freq)] - 1
  // Set Waveform Generation Mode bit. This tells the timer we want it to reset when it reaches the OCR2A value instead of its natural max, 256
  TCCR2A |= (1 << WGM21); // Timer counter control register 2A set to CTC mode 
  // Set CS20, CS21, and CS22 bits to tell the timer we want to use a prescaler of 1024. 
  // This is configured for Timer 2 bit mapping.
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); 
  // enable timer compare interrupt by setting "Output Compare Interrupt Enable" bit for timer 2 to 1 in the Timer Interrupt Mask for timer 2.
  TIMSK2 |= (1 << OCIE2A); 

  sei(); // Set interrupts, exit critical section
}

  // Timer2's interrupt handler, will execute at 100Hz 
ISR(TIMER2_COMPA_vect){ 
  interrupt_counter++; // inc int counter
  if (interrupt_counter >= 100) { // if int counter is 100 or more
    interrupt_counter = 0; // set 0
    seconds++; // increment seconds
    if (seconds == 60) {  // if seconds == 60
      seconds = 0;  // set 0
      minutes++;  // inc min
    }
  }
}

void loop() {
  if (seconds != last_second) {  // Check for change
    last_second = seconds;  // Acknowledge update
    
    servo_seconds.write(seconds * 3); // 180 total degrees, we want 60 seconds.
    servo_minutes.write(minutes * 3); // Match step size with seconds  

    char buffer[10];  // string for formatted time
    sprintf(buffer, "%02d:%02d", minutes, seconds); // Formatted time
    Serial.println(buffer);
  }
}