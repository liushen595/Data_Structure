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

    Node* head = new Node(values[1]);
    Node* current = head;

    for (size_t i = 2; i < values.size(); i++) {
        current->next = new Node(values[i]);
        current = current->next;
    }

    current->next = new Node(-65535); //创建尾标志

    Node* y = new Node(values[0]); //创建头节点
    y->next = head;
    head = y;

    return head;
}

//获取链表长度(不含头节点和尾标志)
int GetLength(Node* head) {
    int count = 0;
    if (head == nullptr)
        return 0;
    else {
        Node* curr = head->next;
        while (curr->data != -65535) {
            count++;
            curr = curr->next;
        }
    }
    return count;
}

//打印链表(不含头节点和尾标志)
void OutLinklist(Node* head) {
    if (head == nullptr) {
        cout << "";
        return;
    }
    Node* curr = head;
    while (curr->data != -65535) {
        cout << curr->data;
        if (curr->next->data != -65535)
            cout << ",";
        else
            cout << endl;
        curr = curr->next;
    }
}

//删除节点,参数为要删除的节点的前一个节点
void DeleteNode(Node* pre_position) {
    if (pre_position != nullptr && pre_position->next->data != -65535) {
        Node* deleted_node = pre_position->next;
        pre_position->next = deleted_node->next;
        delete deleted_node;
    }
}

//插入节点
void InsertNode(Node* position, int data) {
    Node* x = new Node(data);
    if (position != nullptr) {
        x->next = position->next;
        position->next = x;
    }
}

//策略一
void Adjust1(Node* head, int keyword) {
    if (head == nullptr)
        return;
    int len = GetLength(head), count = 1;
    vector<int> num;
    Node* curr = head;

    for (int i = 1; i <= len; i++) {
        curr = curr->next;
        if (i >= len - keyword) {
            while (curr->next->data != -65535) {
                num.push_back(curr->next->data); //将后k个数据暂存到一个向量中
                DeleteNode(curr);
            }
            break;
        }
    }
    curr = head;
    for (int i = num.size() - 1; i >= 0; i--) //反向遍历向量
    {
        InsertNode(curr, num[i]); //插入节点
        if (curr->next != nullptr)
            curr = curr->next->next; //因为有插入，所以要跳两步
    }

    OutLinklist(head);
}

void Adjust2(Node* head, int keyword) {
    if (head == nullptr)
        return;
    int len = GetLength(head);
    Node* fast = head->next;
    Node* flag = head;
    int count = 1;
    while (count <= keyword) {
        fast = fast->next;
        flag = flag->next;
        count++;
    }

    Node* slow = head;
    for (int i = 0; i < keyword + 1; i++) {
        InsertNode(slow, fast->data);
        slow = slow->next->next;
        fast = fast->next;
    }

    for (int i = 0; i < keyword + 1; i++)
        DeleteNode(flag->next);

    OutLinklist(head);
}

void Adjust3(Node* head, int keyword) {
    if (head == nullptr)
        return;
    int len = GetLength(head), count = 1;
    Node* curr = head->next;
    Node* flag = head;
    Node* tail = head->next;

    while (tail->next->data != -65535)
        tail = tail->next;

    while (count < len) {
        if (curr->data == keyword) {
            InsertNode(tail, keyword);
            tail = tail->next;
            curr = curr->next;
            count++;
            DeleteNode(flag);
            continue;
        }
        else {
            curr = curr->next;
            flag = flag->next;
            count++;
        }
    }

    OutLinklist(head);
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

int GetInput(vector<int> &input) {
    string line, token;
    // cout << "输入链表数据: ";
    getline(cin, line);
    stringstream ss(line);

    while (getline(ss, token, ',')) {
        if (stoi(token) == -1)
            return -1;
        else
            input.push_back(stoi(token));
    }

    return 0;
}

void GetRequest(int &method, int &keyword) {
    string line, token;
    // cout << "输入策略及关键字: ";
    getline(cin, line);
    stringstream ss1(line);
    int count = 1;
    while (getline(ss1, token, ',')) {
        if (count == 1)
            method = stoi(token);
        else
            keyword = stoi(token);
        count++;
    }
}

int main() {
    vector<int> input;
    int method = 0, keyword = 0;

    int flag = GetInput(input);
    Node* head = CreatLinklist(input);
    GetRequest(method, keyword);

    if (method == 1)
        Adjust1(head, keyword);
    else if (method == 2)
        Adjust2(head, keyword);
    else if (method == 3)
        Adjust3(head, keyword);
    else
        return 0;

    for (int i = 0; i < 2; i++) {
        flag = GetInput(input);
        if (flag == 0)
            Node* head = CreatLinklist(input);

        GetRequest(method, keyword);
        if (method == 1)
            Adjust1(head, keyword);
        else if (method == 2)
            Adjust2(head, keyword);
        else if (method == 3)
            Adjust3(head, keyword);
        else
            break;
    }

    DeleteLinklist(head);
    system("pause");
    return 0;
}