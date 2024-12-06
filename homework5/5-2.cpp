#include <iostream>
#include <vector>
#include <string>
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

string stringdeal(string &str) {
    SeqStack<char> stack;

    // 遍历字符串的每个字符
    for (char c : str) {
        // 如果栈不为空，并且栈顶元素等于当前字符，说明遇到相同的相邻字符
        if (!stack.isEmpty() && stack.peek() == c)
            stack.pop();  // 弹出栈顶元素，消除相邻的相同字符对
        else
            stack.push(c);  // 否则，将当前字符压入栈中
    }

    // 将栈中的字符拼接
    string result = "";
    while (!stack.isEmpty())
        result += stack.pop(); // 从栈顶元素开始逐个弹出

    //反向
    SeqStack<char> reverse;
    for (char c : result)
        reverse.push(c);

    result = "";
    while (!reverse.isEmpty())
        result += reverse.pop(); // 从栈顶元素开始逐个弹出

    return result;
}

int main() {
    string s;
    cin >> s;

    cout << stringdeal(s);

    system("pause");
    return 0;
}