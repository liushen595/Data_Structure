#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 统计变量（可以改为引用参数或成员变量等更灵活的方式）
static long long comparisons = 0;  // 比较次数
static long long moves = 0;        // 移动次数

// -------------------- 工具函数：读取文件中的数据 --------------------
bool readDataFromFile(const string &filename, vector<int> &data) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return false;
    }
    data.clear();
    int value;
    while (fin >> value) {
        data.push_back(value);
    }
    fin.close();
    return true;
}

// -------------------- 各种排序算法 --------------------
/*
 * 插入排序
 */
void insertionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // 比较一次
        comparisons++;
        while (j >= 0 && arr[j] > key) {
            // 再比较一次
            comparisons++;
            // 移动
            moves++;
            arr[j + 1] = arr[j];
            j--;
        }
        // 上面的 while 循环退出时，还会有一次比较
        // 插入
        moves++;
        arr[j + 1] = key;
    }
}

/*
 * 选择排序
 */
void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            moves += 3;
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

/*
 * 希尔排序
 */
void shellSort(vector<int> &arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            comparisons++;
            while (j - gap >= 0 && arr[j - gap] > temp) {
                comparisons++;
                moves++;
                arr[j] = arr[j - gap];
                j -= gap;
            }
            moves++;
            arr[j] = temp;
        }
    }
}

/*
 * 归并排序
 */
void mergeArray(vector<int> &arr, int left, int mid, int right) {
    int i = left, j = mid + 1;
    vector<int> temp;
    temp.reserve(right - left + 1);

    while (i <= mid && j <= right) {
        comparisons++;
        if (arr[i] <= arr[j]) {
            moves++;
            temp.push_back(arr[i++]);
        }
        else {
            moves++;
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) {
        moves++;
        temp.push_back(arr[i++]);
    }
    while (j <= right) {
        moves++;
        temp.push_back(arr[j++]);
    }
    // 回填
    for (int k = 0; k < (int)temp.size(); k++) {
        moves++;
        arr[left + k] = temp[k];
    }
}

void mergeSortHelper(vector<int> &arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    mergeArray(arr, left, mid, right);
}

void mergeSort(vector<int> &arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

/*
 * 快速排序
 */
int partitionArray(vector<int> &arr, int low, int high) {
    int pivot = arr[low];
    while (low < high) {
        // 每一次比较都要计数
        comparisons++;
        while (low < high && arr[high] >= pivot) {
            comparisons++;
            high--;
        }
        if (low < high) {
            moves++;
            arr[low] = arr[high];
            low++;
        }
        comparisons++;
        while (low < high && arr[low] <= pivot) {
            comparisons++;
            low++;
        }
        if (low < high) {
            moves++;
            arr[high] = arr[low];
            high--;
        }
    }
    moves++;
    arr[low] = pivot;
    return low;
}

void quickSortHelper(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivotPos = partitionArray(arr, low, high);
        quickSortHelper(arr, low, pivotPos - 1);
        quickSortHelper(arr, pivotPos + 1, high);
    }
}

void quickSort(vector<int> &arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

/*
 * 堆排序
 */
void heapify(vector<int> &arr, int n, int i) {
    int largest = i;     // 根节点
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 和左子节点比较
    if (left < n) {
        comparisons++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }
    // 和右子节点比较
    if (right < n) {
        comparisons++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }
    // 如果 largest 不为 i，说明子节点中有比父节点更大的，需要交换
    if (largest != i) {
        moves += 3; // 交换
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int> &arr) {
    int n = arr.size();
    // 建堆（从第一个非叶子结点开始）
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // 逐个取出堆顶元素
    for (int i = n - 1; i >= 1; i--) {
        moves += 3; // 交换
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// -------------------- 测试并输出排序结果 --------------------
void testSort(const string &sortName, void (*sortFunc)(vector<int> &), const vector<int> &original) {
    // 每次都要拷贝一份原始数据
    vector<int> arr = original;

    // 清零统计
    comparisons = 0;
    moves = 0;

    // 开始计时
    auto startTime = high_resolution_clock::now();
    // 调用排序函数
    sortFunc(arr);
    // 结束计时
    auto endTime = high_resolution_clock::now();

    // 计算时长（毫秒）
    auto duration = duration_cast<milliseconds>(endTime - startTime).count();

    // 输出结果
    cout << sortName << " 排序结果:" << endl;
    cout << "  - 运行时间: " << duration << " ms" << endl;
    cout << "  - 比较次数: " << comparisons << endl;
    cout << "  - 移动次数: " << moves << endl;
    cout << "-----------------------------------" << endl;
}

int main() {
    vector<int> data;
    if (!readDataFromFile("random_integers.txt", data)) {
        system("pause");
        return 1; // 如果无法读取文件，直接退出
    }

    // 在测试前，可以确认一下 data 的大小
    cout << "读取到 " << data.size() << " 个整数。" << endl;

    // 调用测试函数
    testSort("插入排序", insertionSort, data);
    testSort("选择排序", selectionSort, data);
    testSort("希尔排序", shellSort, data);
    testSort("归并排序", mergeSort, data);
    testSort("快速排序", quickSort, data);
    testSort("堆排序", heapSort, data);

    system("pause");
    return 0;
}
