#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <unordered_set>

using namespace std;
using namespace std::chrono;

// 全局变量用于统计比较次数
long long comparisonCount = 0;

// 顺序查找（无序表）
bool sequentialSearchUnordered(const vector<int>& data, int key, long long& comparisons) {
    comparisons = 0;
    for (auto it = data.begin(); it != data.end(); ++it) {
        comparisons++;
        if (*it == key)
            return true;
    }
    return false;
}

// 顺序查找（有序表）
bool sequentialSearchOrdered(const vector<int>& data, int key, long long& comparisons) {
    comparisons = 0;
    for (auto it = data.begin(); it != data.end(); ++it) {
        comparisons++;
        if (*it == key)
            return true;
        else if (*it > key) // 有序表可以提前终止
            break;
    }
    return false;
}

// 二分查找（非递归）
bool binarySearchIterative(const vector<int>& data, int key, long long& comparisons) {
    comparisons = 0;
    int left = 0;
    int right = data.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (data[mid] == key)
            return true;
        comparisons++;
        if (data[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

// 二分查找（递归）
bool binarySearchRecursiveHelper(const vector<int>& data, int key, int left, int right, long long& comparisons) {
    if (left > right)
        return false;
    int mid = left + (right - left) / 2;
    comparisons++;
    if (data[mid] == key)
        return true;
    comparisons++;
    if (data[mid] < key)
        return binarySearchRecursiveHelper(data, key, mid + 1, right, comparisons);
    else
        return binarySearchRecursiveHelper(data, key, left, mid - 1, comparisons);
}

bool binarySearchRecursive(const vector<int>& data, int key, long long& comparisons) {
    comparisons = 0;
    return binarySearchRecursiveHelper(data, key, 0, data.size() - 1, comparisons);
}

// 生成随机整数
int generateRandomInt(int min, int max) {
    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

int main() {
    int n, m;
    char tableType;
    cout << "请输入线性表中整数的数量n: " << flush;
    cin >> n;
    cout << "请选择线性表类型（o-有序表，u-无序表）: " << flush;
    cin >> tableType;

    // 生成线性表
    vector<int> data;
    data.reserve(n);
    unordered_set<int> uniqueCheck; // 确保无序表中的元素唯一
    while (data.size() < n) {
        int num = generateRandomInt(1, n * 10);
        if (tableType == 'u') {
            if (uniqueCheck.find(num) == uniqueCheck.end()) {
                data.push_back(num);
                uniqueCheck.insert(num);
            }
        }
        else {
            data.push_back(num);
        }
    }

    if (tableType == 'o') {
        sort(data.begin(), data.end());
    }

    cout << "请输入查找次数m: " << flush;
    cin >> m;

    // 生成m个查找关键字，其中一半存在，一半不存在
    int m_success = m / 2;
    int m_fail = m - m_success;
    vector<int> searchKeys;
    searchKeys.reserve(m);
    // 选择m_success个存在的关键字
    for (int i = 0; i < m_success; ++i) {
        int idx = generateRandomInt(0, n - 1);
        searchKeys.push_back(data[idx]);
    }
    // 选择m_fail个不存在的关键字
    for (int i = 0; i < m_fail; ++i) {
        int key;
        bool exists;
        do {
            key = generateRandomInt(n * 10 + 1, n * 20);
            if (tableType == 'o') {
                exists = binary_search(data.begin(), data.end(), key);
            }
            else { // tableType == 'u'
                exists = uniqueCheck.find(key) != uniqueCheck.end();
            }
        } while (exists);
        searchKeys.push_back(key);
    }

    // 打乱搜索关键字顺序
    shuffle(searchKeys.begin(), searchKeys.end(), mt19937(random_device{}()));

    // (1) 比较顺序查找在有序表和无序表中的性能
    if (tableType == 'o' || tableType == 'u') {
        // 顺序查找（无序表）
        if (tableType == 'u') {
            long long totalComparisons_success = 0, totalComparisons_fail = 0;
            auto start = high_resolution_clock::now();
            for (int i = 0; i < m; ++i) {
                long long comparisons = 0;
                bool found = sequentialSearchUnordered(data, searchKeys[i], comparisons);
                if (i < m_success) { // 前m_success个是成功查找
                    totalComparisons_success += comparisons;
                }
                else {
                    totalComparisons_fail += comparisons;
                }
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start).count();
            cout << "\n顺序查找（无序表）:" << endl;
            cout << "总时间: " << duration << " ms" << endl;
            cout << "平均比较次数（成功）: " << (double)totalComparisons_success / m_success << endl;
            cout << "平均比较次数（失败）: " << (double)totalComparisons_fail / m_fail << endl;
        }

        // 顺序查找（有序表）
        if (tableType == 'o') {
            long long totalComparisons_success = 0, totalComparisons_fail = 0;
            auto start = high_resolution_clock::now();
            for (int i = 0; i < m; ++i) {
                long long comparisons = 0;
                bool found = sequentialSearchOrdered(data, searchKeys[i], comparisons);
                if (i < m_success) { // 前m_success个是成功查找
                    totalComparisons_success += comparisons;
                }
                else {
                    totalComparisons_fail += comparisons;
                }
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start).count();
            cout << "\n顺序查找（有序表）:" << endl;
            cout << "总时间: " << duration << " ms" << endl;
            cout << "平均比较次数（成功）: " << (double)totalComparisons_success / m_success << endl;
            cout << "平均比较次数（失败）: " << (double)totalComparisons_fail / m_fail << endl;
        }
    }

    // (2) 比较顺序查找和二分查找在有序表中的性能
    if (tableType == 'o') {
        // 顺序查找
        long long totalComparisons_seq_success = 0, totalComparisons_seq_fail = 0;
        auto start_seq = high_resolution_clock::now();
        for (int i = 0; i < m; ++i) {
            long long comparisons = 0;
            bool found = sequentialSearchOrdered(data, searchKeys[i], comparisons);
            if (i < m_success) { // 前m_success个是成功查找
                totalComparisons_seq_success += comparisons;
            }
            else {
                totalComparisons_seq_fail += comparisons;
            }
        }
        auto end_seq = high_resolution_clock::now();
        auto duration_seq = duration_cast<milliseconds>(end_seq - start_seq).count();

        // 二分查找（非递归）
        long long totalComparisons_bin_iter_success = 0, totalComparisons_bin_iter_fail = 0;
        auto start_bin_iter = high_resolution_clock::now();
        for (int i = 0; i < m; ++i) {
            long long comparisons = 0;
            bool found = binarySearchIterative(data, searchKeys[i], comparisons);
            if (i < m_success) { // 前m_success个是成功查找
                totalComparisons_bin_iter_success += comparisons;
            }
            else {
                totalComparisons_bin_iter_fail += comparisons;
            }
        }
        auto end_bin_iter = high_resolution_clock::now();
        auto duration_bin_iter = duration_cast<milliseconds>(end_bin_iter - start_bin_iter).count();

        cout << "\n顺序查找 vs 二分查找（非递归）在有序表中的性能:" << endl;
        cout << "顺序查找总时间: " << duration_seq << " ms" << endl;
        cout << "二分查找（非递归）总时间: " << duration_bin_iter << " ms" << endl;
        cout << "顺序查找平均比较次数（成功）: " << (double)totalComparisons_seq_success / m_success << endl;
        cout << "顺序查找平均比较次数（失败）: " << (double)totalComparisons_seq_fail / m_fail << endl;
        cout << "二分查找（非递归）平均比较次数（成功）: " << (double)totalComparisons_bin_iter_success / m_success << endl;
        cout << "二分查找（非递归）平均比较次数（失败）: " << (double)totalComparisons_bin_iter_fail / m_fail << endl;
    }

    // (3) 比较递归和非递归二分查找在有序表中的性能
    if (tableType == 'o') {
        // 二分查找（非递归）
        long long totalComparisons_bin_iter_success = 0, totalComparisons_bin_iter_fail = 0;
        auto start_bin_iter = high_resolution_clock::now();
        for (int i = 0; i < m; ++i) {
            long long comparisons = 0;
            bool found = binarySearchIterative(data, searchKeys[i], comparisons);
            if (i < m_success) { // 前m_success个是成功查找
                totalComparisons_bin_iter_success += comparisons;
            }
            else {
                totalComparisons_bin_iter_fail += comparisons;
            }
        }
        auto end_bin_iter = high_resolution_clock::now();
        auto duration_bin_iter = duration_cast<milliseconds>(end_bin_iter - start_bin_iter).count();

        // 二分查找（递归）
        long long totalComparisons_bin_rec_success = 0, totalComparisons_bin_rec_fail = 0;
        auto start_bin_rec = high_resolution_clock::now();
        for (int i = 0; i < m; ++i) {
            long long comparisons = 0;
            bool found = binarySearchRecursive(data, searchKeys[i], comparisons);
            if (i < m_success) { // 前m_success个是成功查找
                totalComparisons_bin_rec_success += comparisons;
            }
            else {
                totalComparisons_bin_rec_fail += comparisons;
            }
        }
        auto end_bin_rec = high_resolution_clock::now();
        auto duration_bin_rec = duration_cast<milliseconds>(end_bin_rec - start_bin_rec).count();

        cout << "\n二分查找（非递归） vs 二分查找（递归）在有序表中的性能:" << endl;
        cout << "二分查找（非递归）总时间: " << duration_bin_iter << " ms" << endl;
        cout << "二分查找（递归）总时间: " << duration_bin_rec << " ms" << endl;
        cout << "二分查找（非递归）平均比较次数（成功）: " << (double)totalComparisons_bin_iter_success / m_success << endl;
        cout << "二分查找（非递归）平均比较次数（失败）: " << (double)totalComparisons_bin_iter_fail / m_fail << endl;
        cout << "二分查找（递归）平均比较次数（成功）: " << (double)totalComparisons_bin_rec_success / m_success << endl;
        cout << "二分查找（递归）平均比较次数（失败）: " << (double)totalComparisons_bin_rec_fail / m_fail << endl;
    }

    system("pause");
    return 0;
}
