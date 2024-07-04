#include <iostream>

struct Node {
    int value;
    Node* next;
};

void insertNode(Node*& head, int value, int position) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        for (int i = 0; i < position - 1 && current != nullptr; i++) {
            current = current->next;
        }
        if (current != nullptr) {
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

void deleteNode(Node*& head, int position) {
    if (head == nullptr) {
        return;
    }

    Node* temp = head;
    if (position == 0) {
        head = head->next;
        delete temp;
    } else {
        Node* current = head;
        for (int i = 0; i < position - 1 && current != nullptr; i++) {
            current = current->next;
        }
        if (current != nullptr && current->next != nullptr) {
            temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
}

void printReverse(Node* head) {
    if (head == nullptr) {
        return;
    }
    printReverse(head->next);
    std::cout << head->value << " ";
}

int main() {
    int n;
    std::cin >> n;

    Node* head = nullptr;

    for (int i = 0; i < n; i++) {
        int value, position;
        char operation;
        std::cin >> value >> position >> operation;

        if (operation == 'i') {
            insertNode(head, value, position);
        } else if (operation == 'd') {
            deleteNode(head, position);
        }
    }

    printReverse(head);
    std::cout << std::endl;

    return 0;
}