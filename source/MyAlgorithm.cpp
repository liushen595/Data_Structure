#include "MyAlgorithm.hpp"

namespace MyAlgorithm {
    vector<int> GetNext(const string &str_in) {
        int m = str_in.length();
        vector<int> next(m, 0);
        next[0] = -1;
        int j = -1;

        for (size_t i = 1; i < m; i++) {
            while (j >= 0 && str_in[i] != str_in[j + 1]) {
                j = next[j];
            }
            if (str_in[i] == str_in[j + 1]) {
                j++;
            }
            next[i] = j;
        }
        return next;
    }

    int KMP_Macth(const string &s, const string &t) {
        vector<int> next;
        int n = t.length();
        int m = s.length();
        int valid_p = -1;

        if (n >= m) {
            next = GetNext(t);
            int j = 0;  // 模式串位置
            for (int i = 0; i < s.size(); i++) // 主串位置
            {
                while (j > 0 && s[i] != t[j]) {
                    j = next[j];
                }
                if (s[i] == t[j]) {
                    j++;
                }
                if (j == t.size()) {
                    return i - j + 1;  // 匹配成功，返回起始位置
                }
            }
            return -1;  // 匹配失败
        }
        else
            return -1;
    }
}