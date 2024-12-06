#include "BinaryTree.hpp"
#include <vector>
#include <string>
#include <sstream>

class bt03 :public BinarySearchTree<int> {
private:
    bool hasPathSumHelper(TreeNode* node, int remainingSum);

public:
    bt03() {};
    ~bt03() override {};
    void preOrderCreat(const vector<int> &values);
    void insertHelper(const vector<int> &values, size_t &index, TreeNode* &root_node);
    bool recursive_path_sum(bt03 &tree, int num);
};

// 递归插入
void bt03::insertHelper(const vector<int> &values, size_t &index, TreeNode* &root_node) {
    if (index >= values.size() || values[index] == 0) {
        return;
    }
    root_node = createNode(values[index]);
    insertHelper(values, ++index, root_node->left);
    insertHelper(values, ++index, root_node->right);
}

// 前序创建
void bt03::preOrderCreat(const vector<int> &values) {
    size_t index = 0;
    insertHelper(values, index, root);
}

bool bt03::hasPathSumHelper(TreeNode* node, int remainingSum) {
    if (node == nullptr) {
        return false;
    }

    remainingSum -= node->value;
    // 检查剩余的和是否为0
    if (remainingSum == 0) {
        return true;
    }

    // 递归检查左右子树
    return hasPathSumHelper(node->left, remainingSum) ||
        hasPathSumHelper(node->right, remainingSum);
}

bool bt03::recursive_path_sum(bt03 &tree, int num) {
    return hasPathSumHelper(tree.root, num);
}

int main() {
    bt03 tree;
    vector<int> values;
    int num;
    string str;
    string s;
    getline(cin, str);
    istringstream ss(str);
    while (getline(ss, s, ' ')) {
        values.push_back(stoi(s));
    }
    cin >> num;

    tree.preOrderCreat(values);

    bool result = tree.recursive_path_sum(tree, num);
    cout << result << endl;

    system("pause");
    return 0;
}