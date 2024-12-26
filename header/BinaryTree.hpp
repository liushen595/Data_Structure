#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <queue>
#include <iostream>
#include <vector>

using namespace std;

// 基类，定义了二叉树的基本操作接口
template <typename T>
class AbstractBinaryTree {
protected:
    struct TreeNode {
        T value;
        TreeNode *left, *right;
        TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    virtual TreeNode* copyTree(TreeNode* node);
    virtual void preOrderCreatHelper(const vector<T> &values, size_t &index, TreeNode* &root_node, const T ignore);
    virtual void inOrderCreatHelper(const vector<T> &values, size_t &index, TreeNode* &root_node, const T ignore);
    virtual void postOrderCreatHelper(const vector<T> &values, size_t &index, TreeNode* &root_node, const T ignore);
    virtual void deleteTree(TreeNode* node);

    virtual void preOrder(TreeNode* node) const;
    virtual void inOrder(TreeNode* node) const;
    virtual void postOrder(TreeNode* node) const;

    virtual void preOrderVector(TreeNode* node, vector<T> &res) const;
    virtual void inOrderVector(TreeNode* node, vector<T> &res) const;
    virtual void postOrderVector(TreeNode* node, vector<T> &res) const;

    virtual int height(TreeNode* node) const;

    virtual TreeNode* deleteNodeHelper(TreeNode* node, const T &value) = 0;

public:
    AbstractBinaryTree() : root(nullptr) {}
    AbstractBinaryTree(const AbstractBinaryTree &other);
    virtual ~AbstractBinaryTree() { deleteTree(root); }
    AbstractBinaryTree& operator=(const AbstractBinaryTree &other);

    virtual TreeNode* createNode(const T &value) { return new TreeNode(value); }
    virtual void preOrderCreat(const vector<T> &values, const T ignore);
    virtual void inOrderCreat(const vector<T> &values, const T ignore);
    virtual void postOrderCreat(const vector<T> &values, const T ignore);
    virtual void deleteNode(const T &value) { root = deleteNodeHelper(root, value); }

    virtual void preOrderTraversal() const { preOrder(root); }
    virtual void inOrderTraversal() const { inOrder(root); }
    virtual void postOrderTraversal() const { postOrder(root); }
    virtual void levelOrderTraversal() const;

    virtual vector<T> preOrderTraversalVector() const { vector<T> res; preOrderVector(root, res); return res; };
    virtual vector<T> inOrderTraversalVector() const { vector<T> res; inOrderVector(root, res); return res; };
    virtual vector<T> postOrderTraversalVector() const { vector<T> res; postOrderVector(root, res); return res; };
    virtual vector<T> levelOrderTraversalVector() const;

    virtual int getHeight() const { return height(root); }
    virtual int countNodes(const int degree) const;
    virtual int getWidth() const;

    virtual bool Find(const T &value) const = 0;
    virtual void insert(const T &value) = 0;
};

template <typename T>
class BinarySearchTree : public AbstractBinaryTree<T> {
protected:
    using typename AbstractBinaryTree<T>::TreeNode;

    TreeNode* find(TreeNode* node, const T &value) const;
    TreeNode* findMin(TreeNode* node) const;
    TreeNode* deleteNodeHelper(TreeNode* node, const T &value) override;

public:
    BinarySearchTree() : AbstractBinaryTree<T>() {}
    BinarySearchTree(const BinarySearchTree &other) : AbstractBinaryTree<T>(other) {}
    ~BinarySearchTree() override {}
    BinarySearchTree& operator=(const BinarySearchTree &other) { AbstractBinaryTree<T>::operator=(other); return *this; }

    void insert(const T &value) override;
    bool Find(const T &value) const override { return find(this->root, value); }

};

template <typename T>
class CompleteBinaryTree : public AbstractBinaryTree<T> {
protected:
    using typename AbstractBinaryTree<T>::TreeNode;

    TreeNode* BSPfind(TreeNode* node, const T& value)const;
    TreeNode* DSPfind(TreeNode* node, const T& value)const;
    TreeNode* deleteNodeHelper(TreeNode* node, const T &value) override;

public:
    CompleteBinaryTree() :AbstractBinaryTree<T>() {}
    CompleteBinaryTree(const CompleteBinaryTree &other) : AbstractBinaryTree<T>(other) {}
    ~CompleteBinaryTree() {}
    CompleteBinaryTree& operator=(const CompleteBinaryTree &other) { AbstractBinaryTree<T>::operator=(other); return *this; }

    bool cbtFind(const T &value, int mode) const;
    bool Find(const T &value) const override { return false; }
    void insert(const T &value) override;
};

#include "BinaryTree.tpp"
#endif // BINARY_TREE_HPP