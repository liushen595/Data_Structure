#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
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

// 前缀表达式求值函数
double prefix(string prefix_ex[], int n) {
    SeqStack<double> stack; // 用于存储操作数的栈

    // 从右向左遍历前缀表达式
    for (int i = n - 1; i >= 0; i--) {
        string token = prefix_ex[i];

        // 如果是运算符
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            // 从栈中弹出两个操作数
            if (stack.count() < 2) {
                cout << "illegal expression" << endl;
                exit(1);
            }

            double operand1 = stack.pop();
            double operand2 = stack.pop();
            double result;

            // 根据运算符进行相应的计算
            if (token == "+")
                result = operand1 + operand2;
            else if (token == "-")
                result = operand1 - operand2;
            else if (token == "*")
                result = operand1 * operand2;
            else if (token == "/") {
                if (operand2 == 0) // 处理除零情况
                {
                    cout << "illegal expression: division by zero" << endl;
                    exit(1);
                }
                result = operand1 / operand2;
            }

            // 将计算结果压入栈中
            stack.push(result);
        }
        else {
            // 如果是数字，则将其转换为 double 类型并压入栈中
            try {
                double num = stod(token); // 转换字符串为浮点数
                stack.push(num);
            }
            catch (const invalid_argument&) {
                cout << "illegal expression" << endl;
                exit(1);
            }
        }
    }

    // 最终栈中应该只剩下一个结果
    if (stack.count() == 1) {
        return stack.pop();
    }
    else {
        cout << "illegal expression" << endl;
        exit(1);
    }
}

int main() {

    string prefix_ex;

    getline(cin, prefix_ex);

    string prefix_array[20];

    stringstream ss(prefix_ex);

    int i = 0;

    while (ss >> prefix_array[i])

        i++;

    cout << prefix(prefix_array, i) << endl;

    system("pause");
    return 0;
}