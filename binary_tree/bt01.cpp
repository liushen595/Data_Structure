#include "BinaryTree.hpp"
#include <vector>
#include <string>

int main() {
    CompleteBinaryTree<int> tree_a;
    string s;
    getline(cin, s);
    for (size_t i = 0; i < s.length(); i++) {
        tree_a.insert(s[i] - 48);
    }

    tree_a.postOrderTraversal();

    system("pause");
    return 0;
}