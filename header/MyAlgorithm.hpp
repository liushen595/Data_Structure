#ifndef MY_ALGORITHM_H  // 防止重复包含
#define MY_ALGORITHM_H

#include <vector>
#include <string>
using namespace std;

namespace MyAlgorithm {
    namespace String {
        // vector<int> GetNext(const string &str_in);
        int KMP_Macth(const string &s, const string &t);
    }

    namespace Sort {
        // void BubbleSort(vector<int> &arr);
        template <typename T>
        void SelectSort(vector<T> &arr);

        template <typename T>
        void InsertSort(vector<T> &arr);

        template <typename T>
        void ShellSort(vector<T> &arr);

        template <typename T>
        void QuickSort(vector<T> &arr);

        template <typename T>
        void MergeSort(vector<T> &arr);

        template <typename T>
        void HeapSort(vector<T> &arr);
        // void CountSort(vector<int> &arr);
        // void RadixSort(vector<int> &arr);
    }

    namespace Search {
        template <typename T>
        int BinarySearch(vector<T> &arr, int target);
    }

}

#endif  // MY_ALGORITHM_H