#ifndef MY_ALGORITHM_H  // 防止重复包含
#define MY_ALGORITHM_H

#include <vector>
#include <string>
using namespace std;

namespace MyAlgorithm {
    vector<int> GetNext(const string &str_in);
    int KMP_Macth(const string &s, const string &t);

}

#endif  // MY_ALGORITHM_H