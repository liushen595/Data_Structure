#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> dailyTemperatures(const vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> s; // 用于存储索引

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
            int prevIndex = s.top();
            s.pop();
            result[prevIndex] = i - prevIndex;
        }
        s.push(i);
    }

    return result;
}

int main() {
    vector<int> temperatures;
    int temp;
    while (cin >> temp) {
        temperatures.push_back(temp);
    }

    vector<int> result = dailyTemperatures(temperatures);
    for (int days : result) {
        cout << days << " ";
    }
    cout << endl;

    return 0;
}
