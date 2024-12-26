#include "BinaryTree.hpp"
#include <sstream>

int main() {
    int value;
    string str;
    vector<int> values;
    vector<int> res;
    getline(cin, str);
    stringstream ss(str);

    while (ss >> value) {
        if (value != 0)
            values.push_back(value);
    }

    BinarySearchTree<int> bst;
    for (int value : values) {
        bst.insert(value);
    }

    res = bst.preOrderTraversalVector();
    if (res == values) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }

    system("pause");
    return 0;
}