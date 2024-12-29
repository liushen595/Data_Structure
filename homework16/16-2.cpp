#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

// Node structure
template <typename T>
struct Node {
    T data;
    Node* next;
    //Node(T x);
    Node(T x) : data(x), next(nullptr) {}
};

// Basic Singly Linked List
template <typename T>
class LinkedList {
protected:
    Node<T>* head;

public:
    LinkedList();
    void CreateLinklist(const vector<T>& values);
    void AddNode(const T& value);
    bool DeleteNode(const T& value);
    void InsertNode(const T& value, size_t position);
    Node<T>* FindNode(const T& value);
    void insertion_sort();
    void Print();
    ~LinkedList();
};

//构造函数
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

//创建链表
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

//添加节点
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

//删除节点
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

//插入节点
template <typename T>
void LinkedList<T>::InsertNode(const T& value, size_t position) {
    if (position == 0) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        return;
    }

    Node<T>* current = head;
    size_t index = 0;
    while (current && index < position - 1) {
        current = current->next;
        ++index;
    }

    if (!current) return;

    Node<T>* newNode = new Node<T>(value);
    newNode->next = current->next;
    current->next = newNode;
    return;
}

//查找节点
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

//打印链表
template <typename T>
void LinkedList<T>::Print() {
    Node<T>* current = head->next;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

//插入排序
template <typename T>
void LinkedList<T>::insertion_sort() {
    if (!head || !head->next) return;
    Node<T>* first_unsorted, *last_sorted, *p;
    InsertNode(INT16_MIN, 0);
    first_unsorted = head->next;
    last_sorted = head;

    while (first_unsorted) {
        if (first_unsorted->data >= last_sorted->data) {
            last_sorted = last_sorted->next;
            first_unsorted = first_unsorted->next;
        }
        else {
            p = head;
            while (p->next->data <= first_unsorted->data) {
                p = p->next;
            }
            last_sorted->next = first_unsorted->next;
            first_unsorted->next = p->next;
            p->next = first_unsorted;
            first_unsorted = last_sorted->next;
        }
    }
}

//析构函数
template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
}



int main() {
    int n, value;
    LinkedList<int> list;
    vector<int> values;
    cin >> n;
    for (size_t i = 0; i < n; i++) {
        cin >> value;
        values.push_back(value);
    }
    list.CreateLinklist(values);

    list.insertion_sort();
    list.Print();

    system("pause");
    return 0;
}