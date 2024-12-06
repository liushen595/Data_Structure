#include "BinaryTree.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <limits>

template <typename Type>
void BinarySearchTreeFeature() {
    BinarySearchTree<Type> bst;
    string values; // 用于存储输入的元素
    Type temp;     // 用于存储输入的临时元素

    cout << "请输入二叉搜索树的元素,以空格分开,不输入任何元素直接回车将返回:" << endl;
    getline(cin, values);
    if (values.empty()) {
        return;
    }

    stringstream ss(values);
    while (ss >> temp) {
        bst.insert(temp);
    }

    cout << endl;
    while (true) {
        int choose_feature;
        cout << "构建完成,选择接下来的操作:" << endl;
        cout << "【1】查找元素" << endl;
        cout << "【2】删除元素" << endl;
        cout << "【3】前序遍历" << endl;
        cout << "【4】中序遍历" << endl;
        cout << "【5】后序遍历" << endl;
        cout << "【6】层序遍历" << endl;
        cout << "【7】获取树的深度" << endl;
        cout << "【8】获取树的宽度" << endl;
        cout << "【9】获取度为0的节点数" << endl;
        cout << "【10】获取度为1的节点数" << endl;
        cout << "【11】获取度为2的节点数" << endl;
        cout << "【0】返回上一层" << endl;

        cout << "请输入: ";
        cin >> choose_feature;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区
        cout << endl;

        if (choose_feature == 1) {
            // 查找元素
            Type search_val;
            cout << "请输入要查找的元素(直接回车将返回): ";
            string input;
            getline(cin, input);

            if (input.empty()) {
                continue;
            }

            // 将输入字符串转换为对应类型
            stringstream ss(input);

            if (!(ss >> search_val)) {
                cout << "输入格式错误" << endl;
                cout << endl;
                continue;
            }
            if (bst.Find(search_val)) {
                cout << "元素存在于二叉搜索树中。" << endl;
                cout << endl;
            }
            else {
                cout << "元素不存在于二叉搜索树中。" << endl;
                cout << endl;
            }
        }
        else if (choose_feature == 2) {
            // 删除元素
            Type delete_val;
            string input;
            cout << "请输入要删除的元素(直接回车将返回): ";
            getline(cin, input);

            if (input.empty()) {
                continue;
            }

            // 将输入字符串转换为对应类型
            stringstream ss(input);
            if (!(ss >> delete_val)) {
                cout << "输入格式错误" << endl;
                cout << endl;
                continue;
            }

            if (bst.Find(delete_val)) {
                bst.deleteNode(delete_val);
                cout << "元素已删除。" << endl;
                cout << endl;
            }
            else {
                cout << "要删除的元素不存在。" << endl;
                cout << endl;
            }
        }
        else if (choose_feature == 3) {
            // 前序遍历
            cout << "前序遍历结果: ";
            bst.preOrderTraversal();
            cout << endl
                << endl;
        }
        else if (choose_feature == 4) {
            // 中序遍历
            cout << "中序遍历结果: ";
            bst.inOrderTraversal();
            cout << endl
                << endl;
        }
        else if (choose_feature == 5) {
            // 后序遍历
            cout << "后序遍历结果: ";
            bst.postOrderTraversal();
            cout << endl
                << endl;
        }
        else if (choose_feature == 6) {
            // 层序遍历
            cout << "层序遍历结果: ";
            bst.levelOrderTraversal();
            cout << endl
                << endl;
        }
        else if (choose_feature == 7) {
            // 获取树的深度
            cout << "树的深度为: " << bst.getHeight() << endl;
            cout << endl;
        }
        else if (choose_feature == 8) {
            // 获取树的宽度
            cout << "树的宽度为: " << bst.getWidth() << endl;
            cout << endl;
        }
        else if (choose_feature == 9) {
            // 获取度为0的节点数
            cout << "度为0的节点数: " << bst.countNodes(0) << endl;
            cout << endl;
        }
        else if (choose_feature == 10) {
            // 获取度为1的节点数
            cout << "度为1的节点数: " << bst.countNodes(1) << endl;
            cout << endl;
        }
        else if (choose_feature == 11) {
            // 获取度为2的节点数
            cout << "度为2的节点数: " << bst.countNodes(2) << endl;
            cout << endl;
        }
        else if (choose_feature == 0) {
            return; // 返回上一层
        }
        else {
            cout << "无效的选择，请重新输入。" << endl;
            cout << endl;
        }
    }
}

template <typename Type>
void CompleteBinaryTreeFeature() {
    CompleteBinaryTree<Type> cbt;
    string values; // 用于存储输入的元素
    Type temp;     // 用于存储输入的临时元素

    cout << "请输入完全二叉树的元素,以空格分开,不输入任何元素直接回车将返回:" << endl;
    getline(cin, values);
    if (values.empty()) {
        return;
    }

    stringstream ss(values);
    while (ss >> temp) {
        cbt.insert(temp);
    }

    cout << endl;
    while (true) {
        int choose_feature;
        cout << "构建完成,选择接下来的操作:" << endl;
        cout << "【1】查找元素" << endl;
        cout << "【2】删除元素" << endl;
        cout << "【3】前序遍历" << endl;
        cout << "【4】中序遍历" << endl;
        cout << "【5】后序遍历" << endl;
        cout << "【6】层序遍历" << endl;
        cout << "【7】获取树的深度" << endl;
        cout << "【8】获取树的宽度" << endl;
        cout << "【9】获取度为0的节点数" << endl;
        cout << "【10】获取度为1的节点数" << endl;
        cout << "【11】获取度为2的节点数" << endl;
        cout << "【0】返回上一层" << endl;

        cout << "请输入: ";
        cin >> choose_feature;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区
        cout << endl;

        if (choose_feature == 1) {
            // 查找元素
            Type search_val;
            int mode;
            cout << "请输入要查找的元素(直接回车将返回): ";
            string input;
            getline(cin, input);

            if (input.empty()) {
                continue;
            }

            // 将输入字符串转换为对应类型
            stringstream ss(input);
            if (!(ss >> search_val)) {
                cout << "输入格式错误" << endl;
                cout << endl;
                continue;
            }

            cout << "选择查找模式:【0】广度优先搜索,【1】深度优先搜索: ";
            cin >> mode;
            if (cbt.cbtFind(search_val, mode)) {
                cout << "元素存在于完全二叉树中。" << endl;
                cout << endl;
            }
            else {
                cout << "元素不存在于完全二叉树中。" << endl;
                cout << endl;
            }
        }
        else if (choose_feature == 2) {
            // 删除元素
            Type delete_val;
            string input;
            cout << "请输入要删除的元素(直接回车将返回): ";
            getline(cin, input);

            if (input.empty()) {
                continue;
            }

            // 将输入字符串转换为对应类型
            stringstream ss(input);
            if (!(ss >> delete_val)) {
                cout << "输入格式错误" << endl;
                cout << endl;
                continue;
            }

            if (cbt.cbtFind(delete_val, 0) || cbt.cbtFind(delete_val, 1)) {
                cbt.deleteNode(delete_val);
                cout << "元素已删除。" << endl;
                cout << endl;
            }
            else {
                cout << "要删除的元素不存在。" << endl;
                cout << endl;
            }
        }
        else if (choose_feature == 3) {
            // 前序遍历
            cout << "前序遍历结果: ";
            cbt.preOrderTraversal();
            cout << endl
                << endl;
        }
        else if (choose_feature == 4) {
            // 中序遍历
            cout << "中序遍历结果: ";
            cbt.inOrderTraversal();
            cout << endl
                << endl;
        }
        else if (choose_feature == 5) {
            // 后序遍历
            cout << "后序遍历结果: ";
            cbt.postOrderTraversal();
            cout << endl
                << endl;
        }
        else if (choose_feature == 6) {
            // 层序遍历
            cout << "层序遍历结果: ";
            cbt.levelOrderTraversal();
            cout << endl
                << endl;
        }
        else if (choose_feature == 7) {
            // 获取树的深度
            cout << "树的深度为: " << cbt.getHeight() << endl;
            cout << endl;
        }
        else if (choose_feature == 8) {
            // 获取树的宽度
            cout << "树的宽度为: " << cbt.getWidth() << endl;
            cout << endl;
        }
        else if (choose_feature == 9) {
            // 获取度为0的节点数
            cout << "度为0的节点数: " << cbt.countNodes(0) << endl;
            cout << endl;
        }
        else if (choose_feature == 10) {
            // 获取度为1的节点数
            cout << "度为1的节点数: " << cbt.countNodes(1) << endl;
            cout << endl;
        }
        else if (choose_feature == 11) {
            // 获取度为2的节点数
            cout << "度为2的节点数: " << cbt.countNodes(2) << endl;
            cout << endl;
        }
        else if (choose_feature == 0) {
            return; // 返回上一层
        }
        else {
            cout << "无效的选择，请重新输入。" << endl;
            cout << endl;
        }
    }
}

int main() {
    while (true) {
        int choose_tree;
        cout << "【1】二叉搜索树" << endl;
        cout << "【2】完全二叉树" << endl;
        cout << "【0】退出" << endl;

        cout << "请输入: ";
        cin >> choose_tree;
        cout << endl;

        if (choose_tree == 0)
            break;

        if (choose_tree == 1) {
            bool run = true;
            while (run) {
                int choose_element_type0;
                cout << "选择要构建的二叉搜索树的元素" << endl;
                cout << "【1】整数" << endl;
                cout << "【2】字符" << endl;
                cout << "【3】字符串" << endl;
                cout << "【4】浮点数" << endl;
                cout << "【0】返回上一层" << endl;

                cout << "请输入: ";
                cin >> choose_element_type0;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区
                cout << endl;

                switch (choose_element_type0) {
                case 1:
                    BinarySearchTreeFeature<int>();
                    break;
                case 2:
                    BinarySearchTreeFeature<char>();
                    break;
                case 3:
                    BinarySearchTreeFeature<string>();
                    break;
                case 4:
                    BinarySearchTreeFeature<float>();
                    break;
                case 0:
                    run = false;
                    break;
                default:
                    cout << "无效的选择" << endl;
                }
            }
        }
        else if (choose_tree == 2) {
            bool run = true;
            while (run) {
                int choose_element_type1;
                cout << "选择要构建的完全二叉树的元素" << endl;
                cout << "【1】整数" << endl;
                cout << "【2】字符" << endl;
                cout << "【3】字符串" << endl;
                cout << "【4】浮点数" << endl;
                cout << "【0】返回上一层" << endl;

                cout << "请输入: ";
                cin >> choose_element_type1;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区
                cout << endl;

                switch (choose_element_type1) {
                case 1:
                    CompleteBinaryTreeFeature<int>();
                    break;
                case 2:
                    CompleteBinaryTreeFeature<char>();
                    break;
                case 3:
                    CompleteBinaryTreeFeature<string>();
                    break;
                case 4:
                    CompleteBinaryTreeFeature<float>();
                    break;
                case 0:
                    run = false;
                    break;
                default:
                    cout << "无效的选择" << endl;
                }
            }
        }
    }
    // system("pause");
    return 0;
}