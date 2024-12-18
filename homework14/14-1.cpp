#include <iostream>
#include <vector>
using namespace std;

const int N = 9;  // 图的顶点个数（从0到8共9个顶点）
int graph[N][N] = {0};  // 邻接矩阵存储图，初始化为0
bool visited[N];  // 标记数组，记录顶点是否被访问

// 递归函数：DFS 遍历图，寻找所有经过所有顶点的简单路径
void dfs(int node, vector<int>& path, int totalNodes) {
    // 遍历所有邻接顶点
    for (int next = 0; next < totalNodes; ++next) {
        // 检查是否有边且未访问过该顶点
        if (graph[node][next] && !visited[next]) {
            visited[next] = true;       // 标记为已访问
            path.push_back(next);       // 加入路径
            dfs(next, path, totalNodes);// 递归访问下一个顶点
            path.pop_back();            // 回溯
            visited[next] = false;      // 撤销标记
        }
    }

    // 如果路径长度等于所有顶点，输出路径
    if (path.size() == totalNodes) {
        cout << "[";
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << ", "; // 逗号分隔
        }
        cout << "]" << endl;
        return;
    }
}

int main() {
    int start;  // 起始点编号
    cout << "请输入起始点编号: ";
    cin >> start;

    // 初始化邻接矩阵（根据题目提供的图结构）
    int edges[][2] = {
        {0, 1}, {0, 5}, {1, 2}, {2, 3}, {2, 5}, {3, 8},
        {8, 4}, {4, 5}, {4, 6}, {5, 6}, {5, 7}, {6, 7}
    };

    // 填充邻接矩阵
    for (auto& edge : edges) {
        graph[edge[0]][edge[1]] = 1;
        graph[edge[1]][edge[0]] = 1;  // 无向图
    }

    // 初始化访问标记
    fill(visited, visited + N, false);

    // 从起点出发进行 DFS
    vector<int> path;
    path.push_back(start);
    visited[start] = true;

    cout << "所有经过所有顶点的路径为：" << endl;
    dfs(start, path, N);

    system("pause");
    return 0;
}
