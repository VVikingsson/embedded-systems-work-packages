#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START_LENGTH 10
#define RANDOM_LIMIT 100

// Define the Node type as a structure.
typedef struct n{   // n is a "tag". A replacement for the alias (Node) while the compiler hasn't reached that line yet.
    int value;     // node's data
    struct n* next; // next pointer
    struct n* prev; // prev pointer
} Node; // alias for the type

// Creates a new linked list with random values
Node* new_random_list();
void print_linked_list(Node* head);
Node* insert_new_head(Node* current_head, int value);

// Main function
int main(void) {
    srand(time(0)); // Initialize randomizer
    Node* head = new_random_list();
    print_linked_list(head);

    int value = 50;
    printf("Adding new head with value %d\n", value);
    head = insert_new_head(head, value);
    print_linked_list(head);
    return 0;
}


Node* new_random_list() {
    Node* head = malloc(sizeof(Node));
    Node* curr;
    Node* prev = head;

    head->value = rand() % RANDOM_LIMIT+1;
    head->prev = NULL;


    int count = 0;
    while (count < START_LENGTH) {
        curr = malloc(sizeof(Node));
        curr->value = rand() % RANDOM_LIMIT+1;
        curr->prev = prev;
        curr->next = NULL;
        prev->next = curr;
        prev = curr;


        count++;
    }

    return head;
}

Node* insert_new_head(Node* current_head, int value) {
    Node* new_head = malloc(sizeof(Node));
    new_head->value = value;
    new_head->next = current_head;
    current_head->prev = new_head;

    return new_head;
}

void print_linked_list(Node* head) {
    Node* curr = head;
    printf("%d", curr->value);
    curr = curr->next;
    while (curr->next != NULL) {
        printf(" -> %d", curr->value);
        curr = curr->next;
    }
    printf("\n");
}