#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void printList(struct Node* n) {
    while (n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");
}
void insertAtHead(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void insertAtTail(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    return;
}

void insertAtPosition(struct Node** head_ref, int new_data, int position) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    struct Node* temp = *head_ref;
    if (position == 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    }
    new_node->next = temp->next;
    temp->next = new_node;
    return;
}
void swapNodes(struct Node** head_ref, int x, int y) {
    if (x == y) {
        return;
    }
    struct Node* prevX = NULL;
    struct Node* currX = *head_ref;
    while (currX != NULL && currX->data != x) {
        prevX = currX;
        currX = currX->next;
    }
    struct Node* prevY = NULL;
    struct Node* currY = *head_ref;
    while (currY != NULL && currY->data != y) {
        prevY = currY;
        currY = currY->next;
    }
    if (currX == NULL || currY == NULL) {
        return;
    }
    if (prevX != NULL) {
        prevX->next = currY;
    } else {
        *head_ref = currY;
    }
    if (prevY != NULL) {
        prevY->next = currX;
    } else {
        *head_ref = currX;
    }
    struct Node* temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    printList(head);

    insertAtHead(&head,0);

    printList(head);

    insertAtTail(&head,5);

    printList(head);

    insertAtPosition(&head,4,4);

    printList(head);

    swapNodes(&head,2,3);

    printList(head);

    return 0;
}
