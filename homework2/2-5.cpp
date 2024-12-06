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

Node* CreatLinklist(const vector<int> &values) {
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

vector<int> Difference(Node* head1, Node* head2) {
    Node* curr1 = head1;
    Node* curr2 = head2;
    vector<int> res;

    while (curr1 != nullptr) {
        int flag = 1;
        while (curr2 != nullptr) {
            if (curr1->data == curr2->data) {
                flag = 0;
                curr2 = curr2->next;
                break;
            }
            curr2 = curr2->next;
        }
        curr2 = head2;
        if (flag == 1)
            res.push_back(curr1->data);
        curr1 = curr1->next;
    }

    return res;
}

void DeleteNode(Node* head) {
    Node* current = head;
    Node* next_node = nullptr;

    while (current != nullptr) {
        next_node = current->next;
        delete current;
        current = next_node;
    }
}

int main() {
    vector<int> input1, input2;
    int n;
    string line;

    getline(cin, line);
    istringstream sti0(line);
    while (sti0 >> n)
        input1.push_back(n);

    getline(cin, line);
    istringstream sti1(line);
    while (sti1 >> n)
        input2.push_back(n);

    Node* head1 = CreatLinklist(input1);
    Node* head2 = CreatLinklist(input2);

    vector<int> res = Difference(head1, head2);
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i];
        if (i != res.size() - 1)
            cout << " ";
    }

    DeleteNode(head1);
    system("pause");
    return 0;
}