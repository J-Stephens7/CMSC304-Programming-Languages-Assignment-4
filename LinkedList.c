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
    else if (!*head) {
        *head = newNode;
        return;

    }
    // Traverse to the end of the list and insert the new node
    else {
        struct Node* current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

}

struct Node* createList(FILE* inf) {
    // Check for NULL file pointer
    if (!inf) {
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

struct Node* removeNode(struct Node** head, int index) {

    // Check for NULL head or empty list
    if (!*head) {
        fprintf(stderr, "Head is NULL\n");
        return NULL;
    }

    // Check for NULL head pointer
    if (!head) {
        fprintf(stderr, "Head pointer is NULL\n");
        return NULL;
    }

    // Check for negative index
    if (index < 0) {
        fprintf(stderr, "Negative index\n");
        return NULL;
    }

    //Initialize current node and index
    struct Node* current = *head;
    int currentIndex = 0;

    // If the index is 0, remove the head node
    if (index == 0) {
        // Update head to the next node
        *head = current->next;
        // Disconnect the old head from the list
        current->next = NULL;
        // Return the removed node  
        return current;        
    }

    while (current->next && currentIndex < index) {
        if (currentIndex == index - 1) {
            // Disconnect the node from the list
            struct Node* nodeToRemove = current->next;
            current->next = nodeToRemove->next;
            nodeToRemove->next = NULL;

            return nodeToRemove;
        }

        current = current->next;
        currentIndex++;
    }

    // If the index is out of bounds, return NULL
    fprintf(stderr, "Index out of bounds\n");
    return NULL;
}