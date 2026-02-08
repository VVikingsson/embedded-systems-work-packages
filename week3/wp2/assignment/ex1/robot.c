#include <stdio.h>  // std io library

// Enum for directions, defaulting to 0, 1, 2, 3
enum Directions {
    N,
    E,
    S,
    W
};

// Defining the robot type
typedef struct {
    int x;
    int y;
    enum Directions dir;
} Robot;

// Declare functions
void move(Robot* robot);
void turn(Robot* robot);
void clear_buffer();

// main function, entry point
int main(void) {
    Robot robot;    // Declare robot
    robot.dir = N;  // Set starting direction
    char* instructions; // Delare string
    int looping = 1;

    // Loop until exit process (ctrl+c)
    while (*instructions != 'x') { 
        printf("Enter starting x: ");
        scanf("%d", &robot.x);  // read x
        clear_buffer();     // clear buffer
        printf("Enter starting y: ");
        scanf("%d", &robot.y);  // read y
        clear_buffer();     // clear buffer
        printf("Enter m/t string or x to exit: ");
        fgets(instructions, 1024, stdin);   // read instructions, no need to clear buffer as fgets is safe

        // while instructions remain
        while(*instructions != '\0') {
            if (*instructions == 'm') { // if current instruction is m
                move(&robot);   // cal move function
            } else if(*instructions == 't') {   // elif current instruction is t
                turn(&robot);   // call turn function
            }
            instructions++;     // move pointer
        }

        printf("x: %d, y: %d\n", robot.x, robot.y);
    }
}

// Moves the robot one step in current direction
void move(Robot* robot) {
    switch (robot->dir) {   // Switch on robot direction
        // One case for each direction where we increment or decrement corresponding coordinate
        case N: robot->y++; break;
        case E: robot->x++; break;
        case S: robot->y--; break;
        case W: robot->x--; break;
    }
}

// TRotates the robot 90 degrees clockwise
void turn(Robot* robot) {
    robot->dir = (robot->dir + 1) % 4;  // increment in the wrapping range of 0-3
}

// Clears the stdin buffer
void clear_buffer() {
    int c;  // Declare int
    while (c = getchar() != '\n' && c != EOF);  // remove chars from stdin until a newline or EOF is found
}