#include "MyAlgorithm.hpp"
#include <random>

namespace {

    // KMP算法中的next数组
    vector<int> GetNext(const string &str_in) {
        int m = str_in.length();
        vector<int> next(m, 0);
        next[0] = -1;
        int j = -1;

        for (size_t i = 1; i < m; i++) {
            while (j >= 0 && str_in[i] != str_in[j + 1]) {
                j = next[j];
            }
            if (str_in[i] == str_in[j + 1]) {
                j++;
            }
            next[i] = j;
        }
        return next;
    }

    // 合并两个有序数组
    template <typename T>
    void merge(vector<T> &arr, vector<T> &temp, int left, int mid, int right) {
        int l_pos = left;       //左边数组的起始位置
        int r_pos = mid + 1;    //右边数组的起始位置
        int temp_pos = left;    //临时数组的起始位置

        //合并两个数组
        while (l_pos <= mid && r_pos <= right) {
            if (arr[l_pos] < arr[r_pos]) {  // 左边数组的剩余的首个元素更小
                temp[temp_pos++] = arr[l_pos++];
            }
            else {                          // 右边数组的剩余的首个元素更小
                temp[temp_pos++] = arr[r_pos++];
            }

        }

        // 将左边数组剩余的元素放入临时数组
        while (l_pos <= mid) {
            temp[temp_pos++] = arr[l_pos++];
        }

        // 将右边数组剩余的元素放入临时数组
        while (r_pos <= right) {
            temp[temp_pos++] = arr[r_pos++];
        }

        // 将临时数组的元素复制回原数组
        for (int i = left; i <= right; i++) {
            arr[i] = temp[i];
        }
    }

    // 归并排序辅助函数
    template <typename T>
    void MgSort(vector<T> &arr, vector<T> &temp, int left, int right) {
        //如果只有一个元素，就不用再分了
        if (left >= right) {
            return;
        }
        else {
            int mid = (left + right) / 2;       //分成两半
            MgSort(arr, temp, left, mid);        //递归划分左半边
            MgSort(arr, temp, mid + 1, right);   //递归划分右半边
            merge(arr, temp, left, mid, right); //合并
        }

    }

    // 快速排序辅助函数
    template <typename T>
    void QkSort(vector<T> &arr, int low, int high) {
        if (low >= high) {
            return;
        }

        int left = low;
        int right = high;
        std::uniform_int_distribution<int> u(low, high);
        std::default_random_engine e;
        int index = u(e);
        swap(arr[low], arr[index]); //随机选择一个数作为基准数，放到最左边
        T pivot = arr[low]; // 把基准数挖出来，留下一个坑

        while (left < right) {
            // 从右往左找比基准数小的数，要先从右往左找，因为基准数在左边，如果先从左往右找，会把基准数覆盖掉
            while (left < right && arr[right] >= pivot) {
                right--;
            }
            arr[left] = arr[right]; // 填左边的坑，右边就"空"了

            // 从左往右找比基准数大的数
            while (left < right && arr[left] <= pivot) {
                left++;
            }
            arr[right] = arr[left]; // 填右边的坑,左边就"空"了
        }
        arr[left] = pivot; //此时left=right，把基准数放到这个坑里
        QkSort(arr, low, left - 1);
        QkSort(arr, left + 1, high);
    }
}

namespace MyAlgorithm {
    /*----------------------------------------------String----------------------------------------------------------*/
    namespace String {

        // KMP算法
        int KMP_Macth(const string &s, const string &t) {
            vector<int> next;
            int n = t.length();
            int m = s.length();
            int valid_p = -1;

            if (n >= m) {
                next = GetNext(t);
                int j = 0;  // 模式串位置
                for (int i = 0; i < s.size(); i++) // 主串位置
                {
                    while (j > 0 && s[i] != t[j]) {
                        j = next[j];
                    }
                    if (s[i] == t[j]) {
                        j++;
                    }
                    if (j == t.size()) {
                        return i - j + 1;  // 匹配成功，返回起始位置
                    }
                }
                return -1;  // 匹配失败
            }
            else
                return -1;
        }
    }

    /*----------------------------------------------Sort------------------------------------------------------------*/
    namespace Sort {

        // 选择排序
        template <typename T>
        void SelectSort(vector<T> &arr) {
            int n = arr.size();
            for (int i = 0; i < n - 1; i++) {
                int min = i;
                for (int j = i + 1; j < n; j++) {
                    if (arr[j] < arr[min]) {
                        min = j;
                    }
                }
                if (min != i) {
                    swap(arr[i], arr[min]);
                }
            }
        }

        // 插入排序
        template <typename T>
        void InsertSort(vector<T> &arr) {
            int n = arr.size();
            for (int i = 1; i < n; i++) {
                T temp = arr[i];
                int j = i - 1;
                while (j >= 0 && arr[j] > temp) {
                    arr[j + 1] = arr[j]; // 后移
                    j--; // 从后往前找到比temp小的元素
                }
                arr[j + 1] = temp; // 插入
            }
        }

        // 希尔排序
        template <typename T>
        void ShellSort(vector<T> &arr) {
            int n = arr.size();
            for (int gap = n / 2; gap > 0; gap /= 2) {
                for (int i = gap; i < n; i++) {
                    T temp = arr[i];
                    int j = i - gap;
                    while (j >= 0 && arr[j] > temp) {
                        arr[j + gap] = arr[j];
                        j -= gap;
                    }
                    arr[j + gap] = temp;
                }
            }
        }

        // 快速排序
        template <typename T>
        void QuickSort(vector<T> &arr) {
            int n = arr.size();
            if (n <= 1) {
                return;
            }
            QkSort(arr, 0, n - 1);
        }

        // 归并排序
        template <typename T>
        void MergeSort(vector<T> &arr) {
            vector<T> temp(arr.size());
            MgSort(arr, temp, 0, arr.size() - 1);
        }
    }
}