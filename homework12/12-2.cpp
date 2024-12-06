#include "BinaryTree.hpp"
#include <vector>
#include <string>
#include <sstream>

class bt122 :public AbstractBinaryTree<int> {
private:
    using typename AbstractBinaryTree<int>::TreeNode;

    TreeNode* deleteNodeHelper(TreeNode* node, const int &value)override { return nullptr; }// do nothing

public:
    bt122() :AbstractBinaryTree<int>() {};
    ~bt122() {};

    bool Find(const int &value) const override { return false; }// do nothing
    void insert(const int &value) override {}// do nothing

    //void preOrderCreat(const string &values);
    //void insertHelper(const string &values, size_t &index, TreeNode* &root_node);
};
// void bt122::insertHelper(const string &values, size_t &index, TreeNode* &root_node) {
//     if (index >= values.length() || values[index] == '#') {
//         return;
//     }
//     root_node = createNode(values[index] - '0');
//     insertHelper(values, ++index, root_node->left);
//     insertHelper(values, ++index, root_node->right);
// }

// void bt122::preOrderCreat(const string &values) {
//     size_t index = 0;
//     insertHelper(values, index, root);
// }

int main() {
    string s;
    getline(cin, s);
    bt122 tree;
    vector<int> v;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#') //记得要被忽略的字符，不能-'0'，尤其是在这里，因为这里是字符，不是数字
            v.push_back(s[i]);
        else
            v.push_back(s[i] - '0');
    }
    tree.preOrderCreat(v, '#');
    int res = tree.countNodes(2);
    cout << res;

    system("pause");
    return 0;
}