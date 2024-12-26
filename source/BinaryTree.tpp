#include "BinaryTree.hpp"

// 拷贝构造函数
template <typename T>
AbstractBinaryTree<T>::AbstractBinaryTree(const AbstractBinaryTree &other) {
    this->root = copyTree(other.root);
}

// 赋值运算符重载
template <typename T>
AbstractBinaryTree<T>& AbstractBinaryTree<T>::operator=(const AbstractBinaryTree &other) {
    if (this != &other) {
        deleteTree(this->root);
        this->root = copyTree(other.root);
    }
    return *this;
}

// 拷贝辅助函数
template <typename T>
typename AbstractBinaryTree<T>::TreeNode* AbstractBinaryTree<T>::copyTree(TreeNode* node) {
    if (!node) return nullptr;

    TreeNode* newNode = createNode(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}

// 删除树
template <typename T>
void AbstractBinaryTree<T>::deleteTree(TreeNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// 前序遍历
template <typename T>
void AbstractBinaryTree<T>::preOrder(TreeNode* node) const {
    if (node) {
        cout << node->value << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

// 中序遍历
template <typename T>
void AbstractBinaryTree<T>::inOrder(TreeNode* node) const {
    if (node) {
        inOrder(node->left);
        cout << node->value << " ";
        inOrder(node->right);
    }
}

// 后序遍历
template <typename T>
void AbstractBinaryTree<T>::postOrder(TreeNode* node) const {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->value << " ";
    }
}

// 层序遍历
template <typename T>
void AbstractBinaryTree<T>::levelOrderTraversal() const {
    if (!root)
        return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        cout << node->value << " ";

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    // cout << endl; // 末尾不输出换行
}

// 前序遍历转vector
template <typename T>
void AbstractBinaryTree<T>::preOrderVector(TreeNode* node, vector<T> &res) const {
    if (node) {
        res.push_back(node->value);
        preOrderVector(node->left, res);
        preOrderVector(node->right, res);
    }
}

// 中序遍历转vector
template <typename T>
void AbstractBinaryTree<T>::inOrderVector(TreeNode* node, vector<T> &res) const {
    if (node) {
        inOrderVector(node->left, res);
        res.push_back(node->value);
        inOrderVector(node->right, res);
    }
}

// 后序遍历转vector
template <typename T>
void AbstractBinaryTree<T>::postOrderVector(TreeNode* node, vector<T> &res) const {
    if (node) {
        postOrderVector(node->left, res);
        postOrderVector(node->right, res);
        res.push_back(node->value);
    }
}

// 层序遍历转vector
template <typename T>
vector<T> AbstractBinaryTree<T>::levelOrderTraversalVector() const {
    vector<T> res;
    if (!root)
        return res;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        res.push_back(node->value);

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    return res;
}

// 计算树的高度
template <typename T>
int AbstractBinaryTree<T>::height(TreeNode* node) const {
    if (!node) return 0;

    int left_height = height(node->left);
    int right_height = height(node->right);

    return max(left_height, right_height) + 1;
}

// 获取树的宽度
template <typename T>
int AbstractBinaryTree<T>::getWidth() const {
    if (!root) return 0;

    int max_width = 0;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int count = q.size();
        max_width = max(max_width, count);

        while (count--) {
            TreeNode* node = q.front();
            q.pop();

            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }

    return max_width;
}

// 计算特定度数的节点数
template <typename T>
int AbstractBinaryTree<T>::countNodes(const int degree) const {
    if (!root) return 0;

    queue<TreeNode*> q;
    q.push(root);
    int count = 0;

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (degree == 0) {
            if (!node->left && !node->right) {
                count++;
            }
        }
        else if (degree == 1) {
            if ((node->right && !node->left) || (node->left && !node->right)) {
                count++;
            }
        }
        else if (degree == 2) {
            if (node->right && node->left) {
                count++;
            }
        }
        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    return count;
}

// 前序创建
template <typename T>
void AbstractBinaryTree<T>::preOrderCreat(const vector<T> &values, const T ignore) {
    size_t index = 0;
    preOrderCreatHelper(values, index, this->root, ignore);
}

// 中序创建
template <typename T>
void AbstractBinaryTree<T>::inOrderCreat(const vector<T> &values, const T ignore) {
    size_t index = 0;
    inOrderCreatHelper(values, index, this->root, ignore);
}

// 后序创建
template <typename T>
void AbstractBinaryTree<T>::postOrderCreat(const vector<T> &values, const T ignore) {
    size_t index = 0;
    postOrderCreatHelper(values, index, this->root, ignore);
}

// 前序创建辅助函数
template <typename T>
void AbstractBinaryTree<T>::preOrderCreatHelper(const vector<T> &values, size_t &index, TreeNode* &root_node, const T ignore) {
    if (index >= values.size() || values[index] == ignore) {
        return;
    }
    root_node = createNode(values[index]);
    preOrderCreatHelper(values, ++index, root_node->left, ignore);
    preOrderCreatHelper(values, ++index, root_node->right, ignore);
}

// 中序创建辅助函数
template <typename T>
void AbstractBinaryTree<T>::inOrderCreatHelper(const vector<T> &values, size_t &index, TreeNode* &root_node, const T ignore) {
    if (index >= values.size() || values[index] == ignore) {
        return;
    }
    inOrderCreatHelper(values, ++index, root_node->left, ignore);
    root_node = createNode(values[index]);
    inOrderCreatHelper(values, ++index, root_node->right, ignore);
}

// 后序创建辅助函数
template <typename T>
void AbstractBinaryTree<T>::postOrderCreatHelper(const vector<T> &values, size_t &index, TreeNode* &root_node, const T ignore) {
    if (index >= values.size() || values[index] == ignore) {
        return;
    }
    postOrderCreatHelper(values, ++index, root_node->left, ignore);
    postOrderCreatHelper(values, ++index, root_node->right, ignore);
    root_node = createNode(values[index]);
}

/*---------------------BinarySearchTree-----------------------------*/

// 插入节点
template <typename T>
void BinarySearchTree<T>::insert(const T &value) {
    if (!this->root) {
        this->root = this->createNode(value);
    }
    else {
        TreeNode* current = this->root;
        TreeNode* parent = nullptr;

        while (current) {
            parent = current;
            if (value < current->value) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        if (value < parent->value) {
            parent->left = this->createNode(value);
        }
        else {
            parent->right = this->createNode(value);
        }
    }
}

// 查找节点
template <typename T>
typename AbstractBinaryTree<T>::TreeNode* BinarySearchTree<T>::find(TreeNode* node, const T &value) const {
    if (!node) return nullptr;

    if (node->value == value) {
        return node;
    }
    else if (value < node->value) {
        return find(node->left, value);
    }
    else {
        return find(node->right, value);
    }
}

// 查找最小节点
template <typename T>
typename AbstractBinaryTree<T>::TreeNode* BinarySearchTree<T>::findMin(TreeNode* node) const {
    if (!node) return nullptr;

    while (node->left) {
        node = node->left;
    }
    return node;
}

// 删除节点的辅助函数
template <typename T>
typename AbstractBinaryTree<T>::TreeNode* BinarySearchTree<T>::deleteNodeHelper(TreeNode* node, const T &value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = deleteNodeHelper(node->left, value);
    }
    else if (value > node->value) {
        node->right = deleteNodeHelper(node->right, value);
    }
    else {
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        else if (!node->left) {
            TreeNode* rightChild = node->right;
            delete node;
            return rightChild;
        }
        else if (!node->right) {
            TreeNode* leftChild = node->left;
            delete node;
            return leftChild;
        }
        else {
            TreeNode* minNode = findMin(node->right);
            node->value = minNode->value;
            node->right = deleteNodeHelper(node->right, minNode->value);
        }
    }
    return node;
}

/*----------------------CompleteBinaryTree------------------------*/

// 插入节点
template <typename T>
void CompleteBinaryTree<T>::insert(const T &value) {
    if (!this->root) {
        this->root = this->createNode(value);
    }
    else {
        queue<TreeNode*> q;
        q.push(this->root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            if (!current->left) {
                current->left = this->createNode(value);
                break;
            }
            else {
                q.push(current->left);
            }

            if (!current->right) {
                current->right = this->createNode(value);
                break;
            }
            else {
                q.push(current->right);
            }
        }
    }
}

// 查找节点，支持两种模式
template <typename T>
bool CompleteBinaryTree<T>::cbtFind(const T &value, int mode) const {
    if (mode == 0) {
        return BSPfind(this->root, value);
    }
    else if (mode == 1) {
        return DSPfind(this->root, value);
    }
    else {
        return false; // 无效的模式
    }
}

// 广度优先搜索
template <typename T>
typename AbstractBinaryTree<T>::TreeNode* CompleteBinaryTree<T>::BSPfind(TreeNode* node, const T& value)const {
    if (!node) return nullptr;

    queue<TreeNode*> q;
    q.push(node);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current->value == value) {
            return current;
        }

        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
    return nullptr;
}

// 深度优先搜索
template <typename T>
typename AbstractBinaryTree<T>::TreeNode* CompleteBinaryTree<T>::DSPfind(TreeNode* node, const T& value)const {
    if (!node) return nullptr;

    if (node->value == value) return node;

    return DSPfind(node->left, value) || DSPfind(node->right, value);
}

// 删除节点的辅助函数
template <typename T>
typename AbstractBinaryTree<T>::TreeNode* CompleteBinaryTree<T>::deleteNodeHelper(TreeNode* node, const T &value) {
    if (!node) return nullptr;

    queue<TreeNode*> q;
    q.push(node);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current->value == value) {
            TreeNode* deepestNode = nullptr;         // 最深的节点
            TreeNode* parentOfDeepestNode = nullptr; // 最深节点的父节点

            queue<TreeNode*> q1;
            q1.push(node);

            while (!q1.empty()) // 找到最深的节点
            {
                parentOfDeepestNode = deepestNode;
                deepestNode = q1.front();
                q1.pop();

                if (deepestNode->left)
                    q1.push(deepestNode->left);
                if (deepestNode->right)
                    q1.push(deepestNode->right);
            }

            current->value = deepestNode->value; // 将最深节点的值赋给要删除的节点
            // 删除最深节点
            if (parentOfDeepestNode->left == deepestNode) {
                delete parentOfDeepestNode->left;
                parentOfDeepestNode->left = nullptr;
                return node;
            }
            else {
                delete parentOfDeepestNode->right;
                parentOfDeepestNode->right = nullptr;
                return node;
            }
            break;
        }

        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
    return node;
}