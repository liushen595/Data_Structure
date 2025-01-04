#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

// Node structure
template <typename T>
struct Node {
    T data;
    Node* next;
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
    void Print();
    void MergeSort();

private:
    Node<T>* mergeSortRecursive(Node<T>* head);
    Node<T>* split(Node<T>* head);
    Node<T>* merge(Node<T>* left, Node<T>* right);
};

// 构造函数
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

// 创建链表
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

// 添加节点
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

// 打印链表
template <typename T>
void LinkedList<T>::Print() {
    Node<T>* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// 拆分链表
template <typename T>
Node<T>* LinkedList<T>::split(Node<T>* head) {
    if (!head || !head->next) return nullptr;

    Node<T>* slow = head;
    Node<T>* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node<T>* secondHalf = slow->next;
    slow->next = nullptr;
    return secondHalf;
}

// 合并两个有序链表
template <typename T>
Node<T>* LinkedList<T>::merge(Node<T>* left, Node<T>* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->data <= right->data) {
        left->next = merge(left->next, right);
        return left;
    }
    else {
        right->next = merge(left, right->next);
        return right;
    }
}

// 递归归并排序实现
template <typename T>
Node<T>* LinkedList<T>::mergeSortRecursive(Node<T>* head) {
    if (!head || !head->next) return head;

    Node<T>* secondHalf = split(head);
    Node<T>* left = mergeSortRecursive(head);
    Node<T>* right = mergeSortRecursive(secondHalf);

    return merge(left, right);
}

// 对链表进行归并排序
template <typename T>
void LinkedList<T>::MergeSort() {
    head = mergeSortRecursive(head);
}

// 测试代码
int main() {
    LinkedList<int> list;
    vector<int> values = {4, 2, 5, 1, 3};

    list.CreateLinklist(values);

    cout << "Original List: ";
    list.Print();

    list.MergeSort();

    cout << "Sorted List: ";
    list.Print();

    system("pause");
    return 0;
}
