#include "BinaryTree.hpp"
#include <algorithm>
#include <vector>

class MaxTree :public BinarySearchTree<int> {
private:
    void preOrder(TreeNode* node) const override;
public:
    MaxTree() {}
    MaxTree(const MaxTree &other) :BinarySearchTree<int>(other) {}
    ~MaxTree() override {}

    void insert(const vector<int> &arry, int size);
    void insertHelper(const vector<int> &arry, int size, TreeNode* &root_node);
    void preOrderTraversal() const override { preOrder(this->root); }
};

void MaxTree::preOrder(TreeNode* node) const {
    if (node) {
        if (node->value != ' ') {
            cout << node->value << ' ';
        }

        preOrder(node->left);
        preOrder(node->right);
    }
}


void MaxTree::insert(const vector<int> &arry, int size) {
    this->insertHelper(arry, size, root);
}

void MaxTree::insertHelper(const vector<int> &arry, int size, TreeNode* &root_node) {
    if (size == 0) {
        return;
    }

    int max = arry[0], max_pos = 0;
    for (size_t i = 1; i < size; i++) {
        if (arry[i] > max) {
            max = arry[i];
            max_pos = i;
        }
    }
    vector<int> sub_arry_left(arry.begin(), arry.begin() + max_pos);
    vector<int> sub_arry_right(arry.begin() + max_pos + 1, arry.end());

    TreeNode* current = this->createNode(max);

    if (!root_node) {
        root_node = current;
    }

    this->insertHelper(sub_arry_left, max_pos, current->left);
    this->insertHelper(sub_arry_right, size - max_pos - 1, current->right);
}



int main() {
    int count, num;
    cin >> count;
    vector<int> arry;
    for (int i = 0; i < count; i++) {
        cin >> num;
        arry.push_back(num);
    }

    MaxTree tree_a;
    tree_a.insert(arry, count);
    tree_a.preOrderTraversal();

    system("pause");
    return 0;
}