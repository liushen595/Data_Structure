#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100;  // 最大结点个数
int graph[MAXN][MAXN]; // 邻接矩阵
bool visited[MAXN];    // 访问标记数组

// 深度优先搜索（DFS）遍历图
void dfs(int node, int n) {
    visited[node] = true;  // 标记当前节点已访问
    for (int next = 0; next < n; ++next) {
        // 如果 next 节点与当前节点相连，且未访问
        if (graph[node][next] == 1 && !visited[next]) {
            dfs(next, n);  // 递归访问
        }
    }
}

int main() {
    int n;  // 图的结点个数
    cin >> n;

    // 输入邻接矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    // 初始化访问标记数组
    fill(visited, visited + n, false);

    int components = 0;  // 连通分量个数

    // 遍历所有节点，寻找未访问的节点，启动新的DFS
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) { // 如果当前节点未访问
            dfs(i, n);     // 启动新的DFS
            components++;  // 连通分量数加1
        }
    }

    // 输出连通分量个数
    cout << components << endl;

    system("pause");
    return 0;
}
