#include <stdio.h>  // std io library
#include <stdbool.h>


#define HEIGHT 100  // Constant for height of 2d plane
#define WIDTH 100   // Constant for width of 2d plane

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
// Moves robot in current direction
void move(Robot* robot);
// Turns robot clockwise
void turn(Robot* robot);
// Clears stdin
void clear_buffer();
// Draws the 2d plane with walls and robot to terminal
void draw_plane(Robot robot);
// Checks robot is within limits of HEIGHT and WIDTH
bool robot_is_within_bounds(Robot robot);

// main function, entry point
int main(void) {
    Robot robot;    // Declare robot
    robot.dir = N;  // Set starting direction
    robot.x = 0;    // Set starting x for while loop
    robot.y = 0;    // Set starting y for while loop
    char* instructions; // Delare string

    // Loop until exit process (ctrl+c)
    while (robot_is_within_bounds(robot)) { 
        printf("Enter starting x: ");
        scanf("%d", &robot.x);  // read x
        clear_buffer();     // clear buffer
        printf("Enter starting y: ");
        scanf("%d", &robot.y);  // read y
        clear_buffer();     // clear buffer
        printf("Enter m/t string or x to exit: ");
        fgets(instructions, 1024, stdin);   // read instructions, no need to clear buffer as fgets is safe

        puts("State before moving robot:");
        printf("x: %d, y: %d\n", robot.x, robot.y);
        draw_plane(robot);  // Draw 2d plane to terminal

        // while instructions remain
        while(*instructions != '\0') {
            if (*instructions == 'm') { // if current instruction is m
                move(&robot);   // cal move function
            } else if(*instructions == 't') {   // elif current instruction is t
                turn(&robot);   // call turn function
            }
            instructions++;     // move pointer
        }

        puts("State after moving robot:");
        printf("x: %d, y: %d\n", robot.x, robot.y);
        draw_plane(robot);  // Draw 2d plane to terminal
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

// Draws 2d environment to terminal with robot and walls visible
void draw_plane(Robot robot) {
    if (robot_is_within_bounds(robot)) {    // If robot is within bounds
        for (int i = -1; i < HEIGHT + 1; i++) { // For every i 0-100
            for (int j = -1; j < WIDTH + 1; j++) {  // For every j 0-100
                if (i == -1 || i == HEIGHT || j == -1 || j == WIDTH) {  // If at the edge
                    printf("#");    // Print wall token
                    if (j == WIDTH) {   // If j == WIDTH
                        printf("\n");   // Print new line
                    }
                } else if (i == robot.x && j == robot.y) {  // If we are at robot location
                    printf("R");    // Print R
                } else {    // If we are not at robot location and we are not at the edge
                    printf(".");    // Print "nothing" token
                }
            }
        }
    } else {    // If robot is out of bounds
        puts("Robot out of bounds, not drawing plane.");
    }
}

bool robot_is_within_bounds(Robot robot) {
    return (robot.x < HEIGHT && robot.x >= 0 && robot.y < WIDTH && robot.y >= 0);   // If robot is within bounds
}