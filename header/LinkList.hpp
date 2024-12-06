#ifndef LINK_LIST_HPP
#define LINK_LIST_HPP

#include <iostream>
#include <vector>

using namespace std;

// Node structure
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T x);
    Node(T x) : data(x), next(nullptr) {}
};

// Basic Singly Linked List
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList();
    void CreateLinklist(const vector<T>& values);
    void AddNode(const T& value);
    bool DeleteNode(const T& value);
    bool InsertNode(const T& value, size_t position);
    Node<T>* FindNode(const T& value);
    void Print();
    ~LinkedList();
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}


template <typename T>
void LinkedList<T>::CreateLinklist(const vector<T>& values) {
    if (values.empty()) {
        head = nullptr;
        return;
    }

    head = new Node<T>(values[0]);
    Node<T>* current = head;
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new Node<T>(values[i]);
        current = current->next;
    }
}

template <typename T>
void LinkedList<T>::AddNode(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!head) {
        head = newNode;
    }
    else {
        Node<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

template <typename T>
bool LinkedList<T>::DeleteNode(const T& value) {
    if (!head) return false;
    if (head->data == value) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node<T>* current = head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }

    if (current->next) {
        Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }

    return false;
}

template <typename T>
bool LinkedList<T>::InsertNode(const T& value, size_t position) {
    if (position == 0) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        return true;
    }

    Node<T>* current = head;
    size_t index = 0;
    while (current && index < position - 1) {
        current = current->next;
        ++index;
    }

    if (!current) return false;

    Node<T>* newNode = new Node<T>(value);
    newNode->next = current->next;
    current->next = newNode;
    return true;
}

template <typename T>
Node<T>* LinkedList<T>::FindNode(const T& value) {
    Node<T>* current = head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
void LinkedList<T>::Print() {
    Node<T>* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
}

// Singly Linked List with a Head Node (dummy head node)
template <typename T>
class LinkedListWithHead : public LinkedList<T> {
public:
    LinkedListWithHead();
    void AddNode(const T& value);
    void Print();
    ~LinkedListWithHead();
};

template <typename T>
LinkedListWithHead<T>::LinkedListWithHead() {
    this->head = new Node<T>(T());
}

template <typename T>
void LinkedListWithHead<T>::AddNode(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    Node<T>* current = this->head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

template <typename T>
void LinkedListWithHead<T>::Print() {
    Node<T>* current = this->head->next;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
LinkedListWithHead<T>::~LinkedListWithHead() {
    Node<T>* current = this->head;
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
}

// Doubly Linked List
template <typename T>
struct DNode {
    T data;
    DNode* prev;
    DNode* next;
    DNode(T x);
    DNode(T x) : data(x), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    DNode<T>* head;

public:
    DoublyLinkedList();
    void CreateDoublyLinklist(const vector<T>& values);
    void AddNode(const T& value);
    bool DeleteNode(const T& value);
    void Print();
    ~DoublyLinkedList();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr) {}

template <typename T>
void DoublyLinkedList<T>::CreateDoublyLinklist(const vector<T>& values) {
    if (values.empty()) {
        head = nullptr;
        return;
    }

    head = new DNode<T>(values[0]);
    DNode<T>* current = head;

    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new DNode<T>(values[i]);
        current->next->prev = current;
        current = current->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::AddNode(const T& value) {
    DNode<T>* newNode = new DNode<T>(value);
    if (!head) {
        head = newNode;
    }
    else {
        DNode<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

template <typename T>
bool DoublyLinkedList<T>::DeleteNode(const T& value) {
    DNode<T>* current = head;
    while (current) {
        if (current->data == value) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            if (current == head) {
                head = current->next;
            }
            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
void DoublyLinkedList<T>::Print() {
    DNode<T>* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    DNode<T>* current = head;
    while (current) {
        DNode<T>* temp = current;
        current = current->next;
        delete temp;
    }
}

#endif // LINK_LIST_HPP