#include <iostream>
#include <vector>
using namespace std;

// 栈类
template <typename T>
class SeqStack {
private:
    vector<T> stackArray;
    int topIndex;
public:
    SeqStack(int size = 0);
    void push(T value);
    bool isEmpty()const { return topIndex == -1; }
    T pop();
    T peek()const;
    int count()const { return topIndex + 1; }
    ~SeqStack() {}
};

template <typename T>
SeqStack<T>::SeqStack(int size) :stackArray(vector<T>()), topIndex(-1) {}

template <typename T>
void SeqStack<T>::push(T value) {
    stackArray.push_back(value);
    topIndex++;
}

template <typename T>
T SeqStack<T>::pop() {
    if (isEmpty())
        exit(1);

    T value = stackArray.back();
    stackArray.pop_back();
    topIndex--;
    return value;
}

template <typename T>
T SeqStack<T>::peek()const {
    if (isEmpty())
        exit(1);

    return stackArray[topIndex];
}

// 循环队列类
template <typename T>
class CirQueue {
private:
    vector<T> queueArray;
    int frontIndex;
    int rearIndex;
    int maxSize;
public:
    CirQueue(int size);
    void EnQueue(T value);
    T DeQueue();
    bool isEmpty()const { return frontIndex == rearIndex; }
    bool isFull()const { return (rearIndex + 1) % maxSize == frontIndex; }
    void PrintOut() const;
    int count()const { return maxSize; }
};

template <typename T>
CirQueue<T>::CirQueue(int size) : maxSize(size + 1), frontIndex(0), rearIndex(0) {
    queueArray.resize(maxSize);
}

template <typename T>
void CirQueue<T>::EnQueue(T value) {
    if (isFull()) {
        throw overflow_error("Queue is full");
    }
    queueArray[rearIndex] = value;
    rearIndex = (rearIndex + 1) % maxSize;
}

template <typename T>
T CirQueue<T>::DeQueue() {
    if (isEmpty()) {
        throw underflow_error("Queue is empty");
    }
    T value = queueArray[frontIndex];
    frontIndex = (frontIndex + 1) % maxSize;
    return value;
}

template <typename T>
void CirQueue<T>::PrintOut() const {
    int index = frontIndex;
    while (index != rearIndex) {
        cout << queueArray[index] << " ";
        index = (index + 1) % maxSize;
    }
    cout << endl;
}

// reverseOdd 函数实现
void reverseOdd(CirQueue<int>& sq) {
    SeqStack<int> oddStack;
    CirQueue<int> tempQueue(sq.count());

    // 首次遍历队列，将奇数存入栈中，所有数存入临时队列
    while (!sq.isEmpty()) {
        int value = sq.DeQueue();
        if (value % 2 != 0) {
            oddStack.push(value);
        }
        tempQueue.EnQueue(value);
    }

    // 第二次遍历临时队列，奇数从栈中弹出替换原来的奇数，偶数保持原状
    while (!tempQueue.isEmpty()) {
        int value = tempQueue.DeQueue();
        if (value % 2 != 0) {
            sq.EnQueue(oddStack.pop());
        }
        else {
            sq.EnQueue(value);
        }
    }
}

int main() {
    int n, item;

    cin >> n;
    CirQueue<int> sq(n);

    if (n == 0) {
        cout << "";
        return 1;
    }

    for (int i = 0; i < n; i++) {
        cin >> item;
        sq.EnQueue(item);
    }

    reverseOdd(sq);

    sq.PrintOut();

    system("pause");
    return 0;
}
