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

Node* Creat(const vector<int>& values) {
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

void DeleteLinklist(Node* head) {
    Node* current = head;
    Node* next_node = nullptr;

    while (current != nullptr) {
        next_node = current->next;
        delete current;
        current = next_node;
    }
}

int Find(int k, Node* head) {
    Node* fast = head;
    Node* slow = head;

    if (k <= 0)
        return -1;

    for (int i = 1; i <= k; i++) {
        if (fast == nullptr)
            return -1;
        fast = fast->next;
    }

    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }

    if (slow == nullptr)
        return -1;
    else
        return slow->data;
}

int main() {
    vector<int> input;
    int n, k;
    string line;

    getline(cin, line);
    istringstream sti(line);
    while (sti >> n)
        input.push_back(n);

    vector<int> values(input.begin() + 1, input.end());

    k = input[0];
    Node* head = Creat(values);
    int result = Find(k, head);

    if (result == -1)
        cout << "Not Found";
    else
        cout << result;

    DeleteLinklist(head);
    system("pause");
    return 0;
}