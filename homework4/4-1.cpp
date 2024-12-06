#include <iostream>
#include <vector>
using namespace std;

void FillMatrix(vector<vector<int>> &matrix, int top, int bottom, int left, int right, int num) {
    if (top > bottom || left > right) return;

    //从左到右
    for (int i = left; i <= right; i++) {
        matrix[top][i] = num;
        num++;
    }
    top++;

    //从上到下
    for (int i = top; i <= bottom; i++) {
        matrix[i][right] = num;
        num++;
    }
    right--;

    //从右到左
    if (top <= bottom) {
        for (int i = right; i >= left; i--) {
            matrix[bottom][i] = num;
            num++;
        }
        bottom--;
    }

    //从下到上
    if (left <= right) {
        for (int i = bottom; i >= top; i--) {
            matrix[i][left] = num;
            num++;
        }
        left++;
    }

    FillMatrix(matrix, top, bottom, left, right, num);
}

void OutMatrix(const vector<vector<int>> &matrix) {
    for (const vector<int> &row : matrix) {
        for (int num : row)
            cout << num << " ";
        cout << endl;
    }
}

int main() {
    int n, num = 1;
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    FillMatrix(matrix, 0, n - 1, 0, n - 1, num);
    OutMatrix(matrix);

    system("pause");
    return 0;
}