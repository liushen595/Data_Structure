#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <stdexcept>

// 顶层抽象模板类
template <typename VertexType, typename WeightType>
class Graph {
public:
    // 析构函数
    virtual ~Graph() = default;

    // 添加一个顶点
    virtual void addVertex(const VertexType& vertex) = 0;

    // 移除一个顶点
    virtual void removeVertex(const VertexType& vertex) = 0;

    // 添加一条边
    virtual void addEdge(const VertexType& from, const VertexType& to, const WeightType& weight) = 0;

    // 移除一条边
    virtual void removeEdge(const VertexType& from, const VertexType& to) = 0;

    // 获取边的权重
    virtual WeightType getEdgeWeight(const VertexType& from, const VertexType& to) const = 0;

    // 设置边的权重
    virtual void setEdgeWeight(const VertexType& from, const VertexType& to, const WeightType& weight) = 0;

    // 获取所有顶点
    virtual std::vector<VertexType> getVertices() const = 0;

    // 获取一个顶点的邻接点
    virtual std::vector<VertexType> getAdjacentVertices(const VertexType& vertex) const = 0;

    // 检查是否存在某条边
    virtual bool hasEdge(const VertexType& from, const VertexType& to) const = 0;

    // 检查图是否为空
    virtual bool isEmpty() const = 0;

    // 获取顶点数
    virtual size_t getVertexCount() const = 0;

    // 获取边数
    virtual size_t getEdgeCount() const = 0;

    // 清空图
    virtual void clear() = 0;

    // 检查是否包含某个顶点
    virtual bool containsVertex(const VertexType& vertex) const = 0;

protected:
    // 保护的构造函数，防止直接实例化
    Graph() = default;
};

#endif // GRAPH_H