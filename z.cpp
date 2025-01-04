#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include "MyAlgorithm.cpp"
using namespace std;

// auto test(auto a) {
//     cout << a << endl;
// }

int main() {
    // int arry[5] = {1,2,3,4,5};
    // cout << *(arry + 3);
    // string s = "fskhfkafkjnk";
    // int p = MyAlgorithm::String::KMP_Macth(s, "fkafkj");
    // cout << p << endl;
    //test(1);

    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 7, 8};
    vector<int> arr1;
    // MyAlgorithm::Sort::QuickSort(arr);
    // for (auto i : arr) {
    //     cout << i << " ";
    // }

    ifstream fin("random_integers.txt");
    ofstream fout("sorted_integers.txt");

    if (fin) {
        while (!fin.eof()) {
            int a;
            fin >> a;
            arr1.push_back(a);
        }
    }
    else {
        cout << "File cannot open!" << endl;
    }

    auto start = chrono::high_resolution_clock::now();
    MyAlgorithm::Sort::QuickSort(arr1);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Self Sort time: " << duration << " ms" << endl;

    if (fout) {
        for (auto i : arr1) {
            fout << i << endl;
        }
    }
    else {
        cout << "File cannot open!" << endl;
    }

    auto start1 = chrono::high_resolution_clock::now();
    sort(arr1.begin(), arr1.end());
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1).count();
    cout << "STL sort time: " << duration1 << " ms" << endl;

    system("pause");
    return 0;
}
