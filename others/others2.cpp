#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

class SimpleHashTable {
private:
    vector<int> table;
    int size;

    int hash(int key) {
        return key % size;
    }

public:
    SimpleHashTable(int tableSize) : size(tableSize) {
        table.resize(size, -1); // 使用 -1 表示空位
    }

    void insert(int key) {
        int index = hash(key);
        while (table[index] != -1) {
            index = (index + 1) % size; // 线性探测解决冲突
        }
        table[index] = key;
    }

    bool find(int key) {
        int index = hash(key);
        int startIndex = index;
        while (table[index] != -1) {
            if (table[index] == key) return true;
            index = (index + 1) % size;
            if (index == startIndex) break; // 遍历一圈后停止
        }
        return false;
    }
};

pair<int, int> findPairWithSum(const vector<int>& sortedArray, int k) {
    int n = sortedArray.size();
    if (n < 2) return {0, 0};

    // 创建哈希表，大小为数组长度的两倍以减少冲突
    SimpleHashTable hashTable(n * 2);

    for (int num : sortedArray) {
        int complement = k - num;
        if (complement > 0 && hashTable.find(complement)) {
            return {complement, num};
        }
        hashTable.insert(num);
    }

    return {0, 0}; // 如果没有找到，返回 {0, 0}
}

int main() {
    vector<int> sortedArray = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 13;

    pair<int, int> result = findPairWithSum(sortedArray, k);

    if (result.first != 0 || result.second != 0) {
        cout << "Found pair: (" << result.first << ", " << result.second << ")" << endl;
    }
    else {
        cout << "No pair found." << endl;
    }

    system("pause");
    return 0;
}
