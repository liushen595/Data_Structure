#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}  // 构造函数，初始化数据和指针
};

Node* CreatLinklist(int n) {
    int data;
    Node* head = nullptr;
    Node* tail = nullptr;

    if (n <= 0) return nullptr;

    while (cin >> data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        // 如果希望以换行符结束输入，则取消注释以下代码
        if (cin.get() == '\n')
            break;
    }
    tail->next = head;

    return head;
}

void DeleteLinklist(Node* head) {
    Node* current = head;
    Node* next_node = nullptr;
    if (head == nullptr) return;

    while (current->next != head) {
        next_node = current->next;
        delete current;
        current = next_node;
    }
}

void print_with_ascending(int n, Node* head) {
    if (head == nullptr) return;

    Node* curr = head;
    Node* compare = head->next;
    int temp = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (curr->data > compare->data) {
                temp = curr->data;
                curr->data = compare->data;
                compare->data = temp;
            }
            if (compare->next != head) compare = compare->next;
        }
        if (curr->next != head) curr = curr->next;
        if (curr->next != head) compare = curr->next;
    }

    curr = head;

    for (int i = 1; i <= n; i++) {
        cout << curr->data;
        if (curr->next != head) cout << " ";
        if (curr->next == head) cout << endl;
        curr = curr->next;
    }

}

int main() {
    int n;
    cin >> n;
    Node* head = CreatLinklist(n);
    print_with_ascending(n, head);

    DeleteLinklist(head);
    system("pause");
    return 0;
}