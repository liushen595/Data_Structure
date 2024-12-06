#include <iostream>
using namespace std;

int main() {
    int arry[10] = {10,9,8,7,6,5,4,3,2,1};
    int i, k;
    int* last = arry + 9;
    cin >> i >> k;
    if (i < 1 || i>10 || k == 0 || k > (10 - i + 1)) {
        cout << "error";
        system("pause");
        return -1;
    }

    for (int j = i - 1; j < 10 - k; j++) {
        arry[j] = arry[j + k];
    }
    last = last - k;

    for (int* p = arry; p <= last; p++) {
        cout << *p;
        if (p != last)
            cout << " ";
    }


    system("pause");
    return 0;
}