// Task: User should be able to
// 1 Create a new and delete the old file.
// 2 Add a new person to the file.
// 3 Search for a person in the file.
// 4 Print out all in the file.
// 5 Exit the program.

#include <stdbool.h>    // bool library
#include <stdio.h>      // std io library
#include <string.h>     // string library

#define FILE_NAME "database.bin"    // file name constant
#define NAME_SIZE 20    // Max size of names

// custom struct type for Person
typedef struct {
    char first_name[NAME_SIZE]; // All fields are arrays of characters of different sizes
    char last_name[NAME_SIZE];
    char personnummer[13];
} Person;   // Alias Person

bool file_exists(char* file_name);  // Self explanatory
int delete_file_if_exists(char* file_name); // Self explanatory
void create_new_file(char* file_name);   // Creates new file and adds dummy 
void print_person(Person* person);  // Prints person info in a certain format
void search_persons();              // Searches then prints persons on prompt
void clear_buffer();                // Clears stdin
void print_all_entries(char* file_name);    // Prints all person entries in the file
int new_person_entry(char* file_name);      // Gets a new entry from stdin
void get_input(char* buffer, int size);     // fgets but remove the trailing \n



int main(void) {
    FILE* file; // Declare file
    int choice; // Declare choice

    while (choice != 5) {   // Self explanatory
        choice = -1;        // Set value for while loop to trigger
        while (choice < 1 || choice > 5) {  // Self explanatory
            printf("1. Create a new file and delete the old one\n2. Add a new person to the file\n3. Search for a person in the file\n4. Print out the whole file\n5. Exit program\n\n");
            printf("Please enter your choice: ");
            scanf("%d", &choice);   // Read an integer
            clear_buffer(); // Clear stdin buffer
            printf("\n");
        }

        switch (choice) {   // Switch on choice
            case 1: // Self explanatory
                delete_file_if_exists(FILE_NAME);   // Self explanatory
                create_new_file(FILE_NAME);     // Self explanatory
                break;      // break to skip other case checks
            case 2: // Self explanatory
                new_person_entry(FILE_NAME);    // Get person from stdin and save it
                break;      // break to skip other case checks
            case 3: // Self explanatory
                search_persons(FILE_NAME);  // Search for person and print all matches out
                break;      // break to skip other case checks
            case 4: // Self explanatory
                print_all_entries(FILE_NAME);   // Print all persons in the file
                break;      // break to skip other case checks
            case 5: // Self explanatory
                printf("Bye.");
        }
    }

}

// Function is self explanatory
bool file_exists(char* file_name) {
    FILE* file; // Declare file
    if (file = fopen(file_name, "r")) { //If file is not NULL when opened
        fclose(file);   // Close it
        return true;   //Return true
    }
    return false;   // Return false
}

// Function is self explanatory
int delete_file_if_exists(char* file_name) {
    if (file_exists(file_name)) {   // Self explanatory
        remove(file_name);  // Delete file
        return 1;   // Return 1
    }
    return 0;   // Return 0
}

// Creates new file and adds dummy person
void create_new_file(char* file_name) {
    FILE* file = fopen(file_name, "wb");    // Open file in write binary
    Person person;  // Declare person
    strcpy(person.first_name, "Dummy"); // Copy "Dummy" to person first name
    strcpy(person.last_name, "Dumb-Dumb"); // Copy "Dumb-Dumb" to person last name
    strcpy(person.personnummer, "197702012757"); // Copy "197702012757" to person personnummer
    fwrite(&person, sizeof(person), 1, file);   // Write person to file
    fclose(file);   // Close file
    printf("Created new file and added Dummy to it.\n\n");
}

// this function gets a user inputted person struct and saves it to the bin file
int new_person_entry(char* file_name) {
    FILE* file = fopen(file_name, "ab");    // Open file in append binary mode
    if (file == NULL) { // If file pointer is null
        printf("No file found with name %s. Create it first.", file_name);
        return 0;   // Return 0/false
    }
    Person person;  // declare person
    printf("\n\n--- Making new Entry ---\n\n");
    printf("%14s", "First name: "); // left padded string
    get_input(person.first_name, NAME_SIZE);    // read first name
    printf("%14s", "Last name: ");  // left padded string
    get_input(person.last_name, NAME_SIZE); // read last name
    printf("%14s", "Personnummer: ");   // left padded string
    get_input(person.personnummer, 13);  // read personnummer

    // parameters: Start from this address, read this amount, this many times, save it to this file
    fwrite(&person, sizeof(person), 1, file);   // Write person to file
    fclose(file);   // Close file
    printf("\n--- Entry Made ---\n\n");

    return 1;   // Return 1/true
}

void search_persons(char* file_name) {
    FILE* file = fopen(file_name, "rb");    // Open file in read binary mode
    if (file == NULL) { // If file pointer is null
        printf("No file found with name %s. Create it first.", file_name);
        return;   // Return
    }

    int choice; // Declare int
    Person temp;    // Declare temp person
    char query[NAME_SIZE];  // Declare search query
    
    printf("I would like to search for...\n1. First name\n2. Last name\n");
    scanf("%d", &choice); clear_buffer();   // Get input and clear buffer
    // If chocie is invalid
    if (choice < 1 || choice > 2) {
        printf("Please make a valid choice.\n\n");

    } else if (choice == 1) {   //if choice is 1
        printf("Enter first name:");
        get_input(query, NAME_SIZE);    // Read first name
        printf("Results for '%s' as first name:\n", query);
        while (fread(&temp, sizeof(temp), 1, file) == 1) {    // Keep reading one person at a time from file
            if (strcmp(temp.first_name, query) == 0) {   // Compare current person first name to user search term
                print_person(&temp);    // print person info
            }
        }

    } else if (choice == 2) {   //if choice is 2
        printf("Enter last name:");
        get_input(query, NAME_SIZE);    // Read last name
        printf("Results for '%s' as last name:\n", query);
        while (fread(&temp, sizeof(temp), 1, file) == 1) {    // Keep reading one person at a time from file
            if (strcmp(temp.last_name, query) == 0) {   // Compare current person first name to user search term
                print_person(&temp);    // print person info
            }
        }
    }

    fclose(file);   // Close file
    printf("\n");
}

void print_all_entries(char* file_name) {
    FILE* file = fopen(file_name, "rb"); // Open file in read binary mode
    if (file == NULL) { // If file pointer is null
        printf("No file found with name %s. Create it first.", file_name);
        return;   // Return
    }

    Person temp; // Declare temp person
    while(fread(&temp, sizeof(temp), 1, file) == 1) {   // Keep reading one entry at a time
        print_person(&temp);    // Print person
    }

    fclose(file);   // Close file
    printf("\n");
}

// Prints person info with a newline
void print_person(Person* person) {
    printf("%s %s - %s\n", person->first_name, person->last_name, person->personnummer);
}

// This function clears the input buffer
void clear_buffer() {
    int c;  // declare int
    while (c = getchar() != '\n' && c != EOF);  // clear chars from stdin until newline or EOF is encountered
}

// This function reads input and removes trailing \n
void get_input(char* buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Get the index of the newline in the buffer string and replace it with a null terminator
}