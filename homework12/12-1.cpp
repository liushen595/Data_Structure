#include "BinaryTree.hpp"
#include <vector>
#include <string>
#include <sstream>

class bt121 :public AbstractBinaryTree<char> {
private:
    using typename AbstractBinaryTree<char>::TreeNode;

    TreeNode* deleteNodeHelper(TreeNode* node, const char &value)override { return nullptr; }// do nothing
    TreeNode* ReplaceHelper(TreeNode* node);

public:
    bt121() :AbstractBinaryTree<char>() {};
    ~bt121() {};

    bool Find(const char &value) const override { return false; }// do nothing
    void insert(const char &value) override {}// do nothing

    //void preOrderCreat(const vector<char> &values, const char ignore = '#')override;
    //void insertHelper(const vector<char> &values, size_t &index, TreeNode* &root_node);
    void ReplaceWithMaxChild(bt121 &tree) { if (root) root = ReplaceHelper(tree.root); }
};
// void bt121::insertHelper(const vector<char> &values, size_t &index, TreeNode* &root_node) {
//     if (index >= values.size() || values[index] == '#') {
//         return;
//     }
//     root_node = createNode(values[index]);
//     insertHelper(values, ++index, root_node->left);
//     insertHelper(values, ++index, root_node->right);
// }

// void bt121::preOrderCreat(const vector<char> &values, const char ignore) {
//     size_t index = 0;
//     insertHelper(values, index, this->root);
// }

typename AbstractBinaryTree<char>::TreeNode* bt121::ReplaceHelper(TreeNode* node) {
    TreeNode* max_node = nullptr;

    queue<TreeNode*> q1;
    q1.push(node);

    while (!q1.empty()) { // 遍历树的每个节点，找到每个节点的子树的最大值

        TreeNode* max_node = q1.front();
        q1.pop();

        queue<TreeNode*> q2;
        q2.push(max_node);

        while (!q2.empty()) { // 找当前节点的子树的最大值

            TreeNode* current = q2.front();
            q2.pop();

            if (current->left) {
                q2.push(current->left);
            }
            if (current->right) {
                q2.push(current->right);
            }

            if (current->value > max_node->value) {
                max_node->value = current->value;
            }
        }
        if (max_node->left) {
            q1.push(max_node->left);
        }
        if (max_node->right) {
            q1.push(max_node->right);
        }

    }
    return node;
}


int main() {
    vector<char> values;
    string s;
    getline(cin, s);
    stringstream ss(s);
    char temp;

    while (ss >> temp) {
        values.push_back(temp);
    }
    bt121 tree;
    tree.preOrderCreat(values, '#');
    tree.ReplaceWithMaxChild(tree);
    tree.preOrderTraversal();

    system("pause");
    return 0;
}