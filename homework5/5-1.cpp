#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
class SeqStack {
private:
    vector<T> stackArray;
    int topIndex;
public:
    SeqStack(int size = 0);
    void push(T value);
    bool isEmpty()const { return topIndex == -1; }
    // bool isFull()const { return topIndex == maxSize - 1; }
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

void primeFactorization(int n, SeqStack<int> &factorStack) {
    while (n % 2 == 0) {
        factorStack.push(2);
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factorStack.push(i);
            n /= i;
        }
    }

    if (n > 2)
        factorStack.push(n);

}

int main() {
    int n;
    cin >> n;

    if (n <= 1)
        return 1;

    SeqStack<int> factorStack;
    primeFactorization(n, factorStack);

    cout << n << "=";
    while (!factorStack.isEmpty()) {
        cout << factorStack.pop();
        if (!factorStack.isEmpty())
            cout << "*";
    }
    cout << endl;

    system("pause");
    return 0;
}