#include <iostream>
using namespace std;

bool isDecrease(int n) {
    if (n == 0 || n < 0)
        return false;
    while (n >= 10) {
        if (((n / 10) % 10) >= (n % 10))
            n = n / 10;
        else
            return false;
    }

    return true;
}

int main() {
    int n;
    cin >> n;
    if (isDecrease(n))
        cout << 1;
    else
        cout << 0;

    system("pause");
    return 0;
}