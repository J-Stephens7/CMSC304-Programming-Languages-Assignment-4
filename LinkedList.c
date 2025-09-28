#include "LinkedList.h"

struct Node* createNode(char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        fprintf(stderr, "Node memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->next = NULL;
    newNode->data = (char*)malloc(strlen(data) + 1);

    if (!newNode->data) {
        fprintf(stderr, "Data memory allocation failed\n");
        free(newNode);
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->data, data);

    return newNode;
};

void insertAtEnd(struct Node** head, struct Node* newNode) {
    
    if (!head){
        return;
    }
    else if (*head == NULL) {
        *head = newNode;
        return;

    }
    else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

}