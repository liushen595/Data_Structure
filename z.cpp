#include <iostream>
#include <vector>
#include "MyAlgorithm.cpp"
using namespace std;

// auto test(auto a) {
//     cout << a << endl;
// }

int main() {
    int arry[5] = {1,2,3,4,5};
    cout << *(arry + 3);
    string s = "fskhfkafkjnk";
    int p = MyAlgorithm::KMP_Macth(s, "fkafkj");
    cout << p << endl;
    //test(1);

    system("pause");
    return 0;
}
