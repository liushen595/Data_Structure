#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void QuickSort(vector<int> &arry) {
    if (arry.size() <= 1) {
        return;
    }
    int pivot = arry[0];
    vector<int> left;
    vector<int> right;
    for (int i = 1; i < arry.size(); i++) {
        if (arry[i] < pivot) {
            left.push_back(arry[i]);
        }
        else {
            right.push_back(arry[i]);
        }
    }
    QuickSort(left);
    QuickSort(right);
    arry.clear();
    arry.insert(arry.end(), left.begin(), left.end());
    arry.push_back(pivot);
    arry.insert(arry.end(), right.begin(), right.end());
}

int main() {
    vector<int> arry;
    int n, k, num;
    cin >> n >> k;

    for (size_t i = 0; i < n; i++) {
        cin >> num;
        arry.push_back(num);
    }

    QuickSort(arry);
    cout << arry[k - 1] << endl;

    system("pause");
    return 0;
}