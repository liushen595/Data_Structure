#include <iostream>
#include <vector>
#include <string>
#include <cctype>

int main() {
    std::string input;
    std::cout << "请输入字符串: ";
    std::getline(std::cin, input);  // 读取输入字符串，包括空格

    std::vector<int> numbers;  // 用于存储提取出的数字
    std::string temp = "";  // 临时存储连续的数字字符

    for (char ch : input) {
        if (std::isdigit(ch)) {
            temp += ch;  // 如果是数字字符，添加到临时字符串
        }
        else {
            if (!temp.empty()) {
                numbers.push_back(std::stoi(temp));  // 将连续数字转为整数并存储
                temp.clear();  // 清空临时字符串，为下一个数字做准备
            }
        }
    }

    // 检查最后的 temp，如果结尾是数字，需要添加到数组
    if (!temp.empty()) {
        numbers.push_back(std::stoi(temp));
    }

    std::cout << "共找到 " << numbers.size() << " 个整数：" << std::endl;
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << "a[" << i << "] = " << numbers[i] << std::endl;
    }

    return 0;
}
