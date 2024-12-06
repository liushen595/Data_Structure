#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class SeqStack {
private:
    vector<T> stackArray;
    int topIndex;
    //int init_size;
public:
    SeqStack();
    void push(T value);
    bool isEmpty()const { return topIndex == -1; }
    T pop();
    T peek()const;
    int count()const { return topIndex + 1; }
    ~SeqStack() {}
};

template <typename T>
SeqStack<T>::SeqStack() :
    stackArray(vector<T>()), topIndex(-1) {}

template <typename T>
void SeqStack<T>::push(T value) {
    stackArray.push_back(value);
    topIndex++;
}

template <typename T>
T SeqStack<T>::pop() {
    if (isEmpty())
        throw out_of_range("exit");

    T value = stackArray.back();
    stackArray.pop_back();
    topIndex--;
    return value;
}

template <typename T>
T SeqStack<T>::peek()const {
    if (isEmpty())
        throw out_of_range("exit");

    return stackArray[topIndex];
}

template <typename T>
void exChange_Reverse(SeqStack<T> &source, SeqStack<T> &target) {
    while (!source.isEmpty()) {
        target.push(source.pop());
    }
}


int main() {
    int n, m, num;
    cin >> n;
    SeqStack<int> right;
    SeqStack<int> left;

    for (int i = 0; i < n; i++) {
        cin >> num;
        right.push(num);
    }
    for (int i = 0; i < n; i++) {
        exChange_Reverse(right, left);
    }

    cin >> m;
    char in_m;
    for (int i = 0; i < m; i++) {
        cin >> in_m;
        if (in_m == 'D') {
            if (left.isEmpty()) {
                // 如果左侧栈为空，将右侧栈中的元素转移过来
                exChange_Reverse(right, left);
            }
            if (!left.isEmpty()) {
                cout << left.pop() << endl;
            }
        }
        else {
            right.push((int)(in_m - '0'));
        }
    }

    return 0;
    system("pause");
}