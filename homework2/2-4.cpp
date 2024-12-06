#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}  // 构造函数，初始化数据和指针
};

Node* CreatLinklist(const vector<int>& values) {
    if (values.empty())
        return nullptr;

    Node* head = new Node(values[0]);
    Node* current = head;

    for (size_t i = 1; i < values.size(); i++) {
        current->next = new Node(values[i]);
        current = current->next;
    }

    return head;
}

Node* ReverseNode(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void DeleteLinklist(Node* head) {
    Node* current = head;
    Node* next_node = nullptr;

    while (current != nullptr) {
        next_node = current->next;
        delete current;
        current = next_node;
    }
}

int main() {
    vector<int> input;
    int n, num;
    cin >> n;
    if (n <= 0) {
        cout << "";
        system("pause");
        return 0;
    }
    else {
        for (int i = 0; i < n; i++) {
            cin >> num;
            input.push_back(num);
        }
    }

    Node* head = CreatLinklist(input);

    head = ReverseNode(head);
    Node* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr)
            cout << " ";
        current = current->next;
    }


    DeleteLinklist(head);
    system("pause");
    return 0;
}