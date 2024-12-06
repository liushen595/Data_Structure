#include <iostream>
using namespace std;

int MaxSum(size_t n, int* arry) {
    int max_sum = 0, this_sum = 0;
    for (size_t i = 0; i < n; i++) {
        this_sum = this_sum + arry[i];
        if (this_sum > max_sum)
            max_sum = this_sum;
        else if (this_sum < 0)
            this_sum = 0;
    }

    return max_sum;
}

int main() {
    int sum;
    size_t n;
    cin >> n;
    int arry[n];
    for (size_t i = 0; i < n; i++)
        cin >> arry[i];

    sum = MaxSum(n, arry);
    cout << sum;
    system("pause");
    return 0;
}