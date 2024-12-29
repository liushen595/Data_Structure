#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

// 辅助函数：判断是否是后序遍历的结果
bool verifyPostorder(vector<int>& sequence, int start, int end) {
    if (start >= end) {
        return true; // 空树或只有一个节点，直接返回true
    }

    int root = sequence[end]; // 后序遍历的最后一个元素是根节点

    // 找到第一个大于根节点的元素，分界点
    int split = start;
    while (split < end && sequence[split] < root) {
        split++;
    }

    // 检查右子树是否所有元素都大于根节点
    for (int i = split; i < end; i++) {
        if (sequence[i] <= root) {
            return false; // 如果右子树中存在小于等于根节点的值，返回false
        }
    }

    // 递归检查左子树和右子树
    return verifyPostorder(sequence, start, split - 1) &&
        verifyPostorder(sequence, split, end - 1);
}

// 主函数：判断数组是否为二元查找树的后序遍历结果
bool isPostorderBST(vector<int>& sequence) {
    if (sequence.empty()) {
        return true; // 空数组是合法的后序遍历
    }
    return verifyPostorder(sequence, 0, sequence.size() - 1);
}

int main() {
    // 输入
    string input;
    getline(cin, input); // 读取整行输入
    vector<int> sequence;

    // 将输入的字符串解析为整数数组
    stringstream ss(input);
    string token;
    while (getline(ss, token, ' ')) {
        sequence.push_back(stoi(token));
    }

    // 判断并输出结果
    cout << (isPostorderBST(sequence) ? "true" : "false") << endl;

    system("pause");
    return 0;
}
