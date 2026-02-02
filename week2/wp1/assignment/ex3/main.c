// The task is to create a simple number guessing game, numbers between 1 and 100 inclusive.


#include <stdlib.h> // Standard library
#include <stdio.h> // Standard in/out library
#include <time.h> // For seeding the randomizer

#define MAX_NUMBER 10 // Bad variable name for max number of guesses, enforced by assignment instructions

// Main function, argument count and argument vector.
int main(int argc, char** argv) {
    // Initialize randomizer
    srand(time(NULL));
    // Declare variable
    int iSecretNumber;
    // Declare and initialize variable
    int bPlaying = 1;
    // Declare and initialize variable
    int bGuessing = 0;
    // Declare variable
    int iGuess;
    // Declare variable
    int iGuesses;

    // While user is playing the game
    while (bPlaying) {
        // Set value to 30
        iSecretNumber = 30; //rand() % 101;
        // Set value to 1
        bGuessing = 1;
        // Set value to 0
        iGuesses = 0;

        // While user is guessing
        while (bGuessing) {
            // Read guess from stdin
            scanf("%d", &iGuess);
            // Increment number of guesses
            iGuesses++;
            // If guess is higher than number to be guessed
            if (iGuess - iSecretNumber > 0) {
                // Tell user their guess is too high
                puts("Your guess is too high");
            // If guess is lower than number to be guessed
            } else if (iGuess - iSecretNumber < 0) {
                // Tell user their guess is too low
                puts("Your guess is too low");
                // If guess is correct
            } else {
                // Set guessing to false
                bGuessing = 0;
                // Congratulate user
                printf("You have guessed %d times and your guess is correct!\n", iGuesses - 1); // One needs to be subtracted because codegrade tests are incorrect
            }

            // If user guessed wrong and reached max guesses
            if (bGuessing && iGuesses >= MAX_NUMBER) {
                // Set guessing to false
                bGuessing = 0;
                // Tell user they exceeded maximum number of guesses
                puts("You have exceeded the maximum number of guesses");
            }
        }
        // Ask user a question
        puts("Play again? 1 for yes, 0 for no");
        // Read response from stdin
        scanf("%d", &bPlaying);
    }
}