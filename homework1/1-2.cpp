#include <iostream>
#include <string>
#include <vector>
using namespace std;

void SortString(string &s) {
    vector<string> flag;
    for (size_t i = 0; i <= s.length() - 1; i++) {
        if (s[i] == 'a')
            flag.push_back("a");
    }
    for (size_t i = 0; i <= s.length() - 1; i++) {
        if (s[i] == 'b')
            flag.insert(flag.begin(), "b");
        else if (s[i] == 'c')
            flag.insert(flag.end(), "c");
    }
    for (string element : flag) {
        cout << element;
    }

}

int main() {
    string s1;
    cin >> s1;
    SortString(s1);
    system("pause");
}