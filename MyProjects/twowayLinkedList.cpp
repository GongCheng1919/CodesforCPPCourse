#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;

void insertAtBeginning(int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->prev = NULL;
    new_node->next = head;
    if (head != NULL) {
        head->prev = new_node;
    }
    head = new_node;
}

void insertAtEnd(int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = head;
    new_node->data = new_data;
    new_node->next = NULL;
    if (head == NULL) {
        new_node->prev = NULL;
        head = new_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    new_node->prev = last;
    return;
}

void insertAfter(struct Node* prev_node, int new_data) {
    if (prev_node == NULL) {
        printf("The given previous node cannot be NULL");
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }
}

void swapNodes(int x, int y) {
    if (x == y) {
        return;
    }
    struct Node* nodeX = NULL;
    struct Node* nodeY = NULL;
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == x) {
            nodeX = temp;
        }
        if (temp->data == y) {
            nodeY = temp;
        }
        temp = temp->next;
    }
    if (nodeX == NULL || nodeY == NULL) {
        return;
    }
    if (nodeX->prev != NULL) {
        nodeX->prev->next = nodeY;
    } else {
        head = nodeY;
    }
    if (nodeY->prev != NULL) {
        nodeY->prev->next = nodeX;
    } else {
        head = nodeX;
    }
    struct Node* tempPrev = nodeX->prev;
    nodeX->prev = nodeY->prev;
    nodeY->prev = tempPrev;
    struct Node* tempNext = nodeX->next;
    nodeX->next = nodeY->next;
    nodeY->next = tempNext;
    if (nodeX->next != NULL) {
        nodeX->next->prev = nodeX;
    }
    if (nodeY->next != NULL) {
        nodeY->next->prev = nodeY;
    }
}

void traverse() {
    struct Node* temp = head;
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void inverseTraverse() {
    struct Node* temp = head;
    if (temp == NULL) {
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("Reverse: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}
struct Node* findElement(int element) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == element) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
int main() {
    insertAtBeginning(5);
    insertAtBeginning(4);
    insertAtEnd(6);
    insertAfter(head->next, 7);
    traverse();
    inverseTraverse();
    swapNodes(4, 6);
    traverse();
    inverseTraverse();
    struct Node* found = findElement(7);
    if (found != NULL) {
        printf("Element found: %d\n", found->data);
    } else {
        printf("Element not found\n");
    }
    return 0;
}
