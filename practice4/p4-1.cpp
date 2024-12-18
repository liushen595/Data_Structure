#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 判断两点是否连通，使用BFS
bool isConnected(int start, int end, const vector<vector<bool>>& graph, int n) {
    vector<bool> visited(n + 1, false); // 动态分配访问标记
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == end) {
            return true; // 找到目标点
        }

        for (int i = 1; i <= n; ++i) {
            if (graph[curr][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    return false; // 没有找到路径
}

int main() {
    int n, q;
    cin >> n >> q;

    // 使用向量初始化邻接矩阵
    vector<vector<bool>> graph(n + 1, vector<bool>(n + 1, false));

    while (q--) {
        char cmd;
        int u, v;
        cin >> cmd >> u >> v;

        if (cmd == 'I') {
            graph[u][v] = true;
            graph[v][u] = true; // 无向图需要双向连接
        }
        else if (cmd == 'D') {
            graph[u][v] = false;
            graph[v][u] = false; // 删除双向连接
        }
        else if (cmd == 'Q') {
            if (isConnected(u, v, graph, n)) {
                cout << "Y" << endl;
            }
            else {
                cout << "N" << endl;
            }
        }
    }

    system("pause");
    return 0;
}
