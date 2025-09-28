#include "LinkedList.h"

//Create a new node with given data and return a pointer to it
struct Node* createNode(char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // Check for malloc failure
    if (!newNode) {
        fprintf(stderr, "Node memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the new node
    newNode->next = NULL;
    newNode->data = (char*)malloc(strlen(data) + 1);

    // Check for malloc failure
    if (!newNode->data) {
        fprintf(stderr, "Data memory allocation failed\n");
        free(newNode);
        exit(EXIT_FAILURE);
    }

    //Copy the data into the new node
    strcpy(newNode->data, data);

    return newNode;
};

void insertAtEnd(struct Node** head, struct Node* newNode) {
    
    // Check for NULL pointers
    if (!head){
        return;
    }
    // If the list is empty, set the new node as the head
    else if (*head == NULL) {
        *head = newNode;
        return;

    }
    // Traverse to the end of the list and insert the new node
    else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

}

struct Node* createList(FILE* inf) {
    // Check for NULL file pointer
    if (inf == NULL) {
        fprintf(stderr, "Input file is NULL\n");
        return NULL;
    }

    // Initialize the head of the list to NULL
    struct Node* head = NULL;

    // fileLine to hold each line read from the file
    char fileLine[MAX_LINE_SIZE];

    // Read lines from the file and create nodes
    //Note that fgets includes the newline/CR character, so we remove it, and fgets advances the file pointer read position
    while (fgets(fileLine, sizeof(fileLine), inf) != NULL) {
        // Remove newline character if present
        fileLine[strcspn(fileLine, "\r\n")] = '\0';

        // Create a new node and insert it at the end of the list
        struct Node* newNode = createNode(fileLine);
        insertAtEnd(&head, newNode);
    }

    return head;
}