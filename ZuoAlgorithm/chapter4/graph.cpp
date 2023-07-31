#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;

// TODO 图表
class Edge;
class Node;
class Graph;
class Node
{
public:
    int value;
    int in;               // 入度
    int out;              // 出度
    vector<Node *> nexts; // 临接节点
    vector<Edge *> edges; // 邻接边
    Node(int v)
    {
        this->value = v;
        in = 0;
        out = 0;
    }
};

class Edge
{
public:
    Node *from;
    Node *to;
    int weight;
    Edge() {}
    Edge(Node *fromNode, Node *toNode, int w)
    {
        this->from = fromNode;
        this->to = toNode;
        this->weight = w;
    }
};

class Graph
{
public:
    unordered_map<int, Node *> nodes; // 点集
    unordered_set<Edge *> edges;      // 边集
};

// arrGraph:N*3 的数组，分别表示fromNodeValue ,toNodeValue,EdgeWeight
Graph *transforGraph(vector<vector<int>> arrGraph)
{
    Graph *graph = new Graph();
    for (int i = 0; i < arrGraph.size(); i++)
    {
        int fromValue = arrGraph[i][0];
        int toValue = arrGraph[i][1];
        int weightValue = arrGraph[i][2];
        // nodes edges;
        if (graph->nodes.find(fromValue) == graph->nodes.end())
        {
            // fromValue不在nodes里面,判断的原因是为了确定是否需要创建新的节点
            (graph->nodes)[fromValue] = new Node(fromValue);
        }
        if ((graph->nodes).find(toValue) == graph->nodes.end())
        {
            // fromValue不在nodes里面,判断的原因是为了确定是否需要创建新的节点
            (graph->nodes)[toValue] = new Node(toValue);
        }
        Node *fromNode = ((graph->nodes)[fromValue]);
        Node *toNode = ((graph->nodes)[toValue]);
        fromNode->out++;
        toNode->in++;
        fromNode->nexts.push_back(toNode);
        Edge *newEdge = new Edge(fromNode, toNode, weightValue);
        (fromNode->edges).push_back(newEdge);
        (graph->edges).insert(newEdge);
    }
    return graph;
}
// TODO 图的遍历
// 宽度优先遍历
void widthProority(Graph *graph)
{
    Node *node = (((graph->nodes).begin())->second);
    // 随机获取一个节点
    queue<Node *> que;
    unordered_set<Node *> selected_node; // 记录已经加入的节点
    que.push(node);
    selected_node.insert(node);
    while (!que.empty())
    {
        node = que.front();
        cout << node->value << " ";
        vector<Node *> nextNodes = node->nexts;
        for (int i = 0; i < nextNodes.size(); i++)
        {
            if (selected_node.find(nextNodes[i]) == selected_node.end())
            {
                que.push(nextNodes[i]);
                selected_node.insert(nextNodes[i]);
            }
        }
        que.pop();
    }
    cout << endl;
}
// 深度优先遍历
void depthPrority(Graph *graph)
{
    Node *node = (graph->nodes.begin())->second;
    stack<Node *> sta;
    sta.push(node);
    // 进stack的时候就应该进行打印
    cout << node->value << " ";
    unordered_set<Node *> selected_nodes;
    selected_nodes.insert(node);
    while (!sta.empty())
    {
        node = sta.top();
        sta.pop();
        vector<Node *> nextNode = node->nexts;
        int index = 0;
        while (index < nextNode.size() && (selected_nodes.find(nextNode[index]) != selected_nodes.end()))
        {
            index++;
        }
        // 每次只会找到一个满足条件的压入
        if (index < nextNode.size())
        {
            selected_nodes.insert(nextNode[index]);
            sta.push(node);
            sta.push(nextNode[index]);
            cout << nextNode[index]->value << " ";
        }
    }
    cout << endl;
}
// TODO topsis Sort
// 容器比较器
struct cmp
{
public:
    bool operator()(Node *a, Node *b)
    {
        return (a->in) > (b->in);
        // 小根堆,important
    }
};
bool myCmp(Node *a, Node *b)
{
    return (a->in) < (b->in);
}
// void topsisSort(Graph *graph)
// {
//     // 按照入度的数量从小到大进行排序
//     vector<Node *> priQue;
//     for (auto i = (graph->nodes).begin(); i != (graph->nodes).end(); i++)
//     {
//         priQue.push_back(i->second);
//     }
//     unordered_set<Node *> selected;
//     sort(priQue.begin(), priQue.end(), myCmp);
//     // 找入度为0的
//     queue<Node *> que;
//     int num = 0;
//     while (num != priQue.size())
//     {
//         Node *temp = priQue[num];
//         if (temp->in == 0 && (selected.find(temp) == selected.end()))
//         {
//             cout << temp->value << " ";
//             selected.insert(temp);
//             // 清理相关的入度
//             for (int i = 0; i < (temp->nexts).size(); i++)
//             {
//                 ((temp->nexts)[i]->in)--;
//                 // heap排序的索引最好不要随意改变，直接这样改变得到结果是不对的
//             }
//             sort(priQue.begin(), priQue.end(), myCmp);
//             num++;
//         }
//         else
//         {
//             cout << "仍有节点未被排序" << endl;
//             break;
//         }
//     }
//     cout << endl;
// }
void topsisSort(Graph *graph)
{
    priority_queue<Node *, vector<Node *>, cmp> priQue;
    for (auto i = graph->nodes.begin(); i != graph->nodes.end(); i++)
    {
        priQue.push(i->second);
    }
    queue<Node *> zeroNodes;
    while (!priQue.empty())
    {
        if (priQue.top()->in == 0)
        {
            zeroNodes.push(priQue.top());
            priQue.pop();
        }
        else
        {
            break;
        }
    }
    while (!zeroNodes.empty())
    {
        Node *temp = zeroNodes.front();
        cout << temp->value << " ";
        zeroNodes.pop();
        for (auto it = temp->nexts.begin(); it != temp->nexts.end(); it++)
        {
            ((*it)->in)--;
            if ((*it)->in == 0)
            {
                zeroNodes.push(*it);
            }
        }
    }
    cout << endl;
}
// TODO 最小生成树K算法和Prim算法
// K 算法基于边，P算法基于点
class SetS
{
public:
    // hashMap映射一个节点属于的集合
    unordered_map<Node *, vector<Node *>> map_set;
    SetS(unordered_map<int, Node *> nodes)
    {
        // 初始胡
        for (auto it = nodes.begin(); it != nodes.end(); it++)
        {
            vector<Node *> temp{it->second};
            map_set[it->second] = temp;
        }
    }
    // 判断是否是同一个集合中额节点
    bool isSame(Node *node01, Node *node02)
    {
        return map_set[node01] == map_set[node02];
    }
    //!!集合合并操作
    // TODO: 这里需要注意一下，好像在set01里增加了数组之后，数组就会发生变化
    // 而在原来的node-->set 映射保持不变，导致set01的映射发生错误，解决方法就是
    // 在将set02的节点全部加入set01之后，再手动设置原来的set01和set02节点中的所有映射
    vector<Node *> unionSet(Node *node01, Node *node02)
    {
        vector<Node *> set01 = map_set[node01];
        vector<Node *> set02 = map_set[node02];
        for (int i = 0; i < set02.size(); i++)
        {
            set01.push_back(set02[i]);
            // map_set[set02[i]]=set01;
            // 加入集合，改变映射
        }
        for (int i = 0; i < set01.size(); i++)
        {
            map_set[set01[i]] = set01;
            // 加入集合，改变映射
        }
        return set01;
    }
};
class edgeCmp
{
public:
    bool operator()(Edge *e1, Edge *e2)
    {
        return (e1->weight) > (e2->weight);
        // 小根堆
    }
};
void Krustkra(Graph *graph)
{
    SetS *sets = new SetS(graph->nodes);
    // 初始化点集合
    // 边排序，边的长度不变，可以用比较器改造的优先级队列
    priority_queue<Edge *, vector<Edge *>, edgeCmp> priQue;
    for (auto it = graph->edges.begin(); it != graph->edges.end(); it++)
    {
        priQue.push(*it);
    }

    int sumLength = 0;
    while (!priQue.empty())
    {
        Edge *tempEdge = priQue.top();
        Node *from = tempEdge->from;
        Node *to = tempEdge->to;
        if (!sets->isSame(from, to))
        {
            // 可以加入集合
            sets->unionSet(from, to);
            cout << "from: " << from->value << " --weight=" << tempEdge->weight << "--  to: " << to->value << endl;
            sumLength += (tempEdge->weight);
        }
        priQue.pop();
    }
    cout << "最小生成树的大小：" << sumLength << endl;
}

// Prim算法
void Prim(Graph *graph)
{
    int sumLegth = 0;
    Node *node = (graph->nodes.begin())->second;
    // edge的长度不会改变，仍然采用优先级队列保存edge
    priority_queue<Edge *, vector<Edge *>, edgeCmp> priQue;
    for (auto it = (node->edges).begin(); it != (node->edges).end(); it++)
    {
        priQue.push(*it);
    }
    unordered_set<Node *> selected;
    selected.insert(node);
    while (!priQue.empty())
    {
        Edge *edge = priQue.top();
        priQue.pop(); // 在获取到top之后就应该pop，否则新更新的最短边会被pop
        if (selected.find(edge->to) == selected.end())
        {
            // 节点未被拉入
            cout << "from: " << edge->from->value << " --weigth=" << edge->weight
                 << " -- to: " << edge->to->value << endl;
            sumLegth = sumLegth + edge->weight;
            selected.insert(edge->to);
            // 把新加入的边加入优先级队列
            for (int i = 0; i < ((edge->to)->edges).size(); i++)
            {
                if (selected.find((((edge->to)->edges)[i])->to) == selected.end())
                {
                    // 相等表明未加入已选集合
                    priQue.push(((edge->to)->edges)[i]);
                }
            }
        }
    }
    cout << "sumLength:" << sumLegth << endl;
}
void printPath(unordered_map<Node *, Node *> path, Node *end)
{
    stack<Node *> sta;
    Node *temp = end;
    while (path[temp] != temp)
    {
        sta.push(temp);
        temp = path[temp];
    }
    cout << temp->value << "-->";
    while (!sta.empty())
    {
        temp = sta.top();
        cout << temp->value << "-->";
        sta.pop();
        /* code */
    }
}
// TODO 最短路径问题 Dijsktra
void Dijsktra(Graph *graph)
{
    Node *node = (graph->nodes.begin())->second;
    cout << "node: " << node->value << " 到各点距离：" << endl;
    unordered_map<Node *, int> result_map;
    unordered_map<Node *, Node *> path;
    unordered_set<Node *> selected;
    result_map[node] = 0;
    selected.insert(node);
    path[node] = node;
    int minWeight = 999;
    Node *minNode = nullptr;
    for (int i = 0; i < node->edges.size(); i++)
    {
        // 更新距离
        int tempweight = node->edges[i]->weight;
        Node *tempNode = node->edges[i]->to;
        result_map[tempNode] = tempweight;
        path[tempNode] = node;
    }
    while (selected.size() != graph->nodes.size())
    {
        // update
        for (int i = 0; i < (node->edges.size()); i++)
        {
            Node *tempNode = node->edges[i]->to;
            int distance = result_map[node];
            int weight = (node->edges[i])->weight;
            if (selected.find(tempNode) == selected.end())
            {
                if (result_map.find(tempNode) == result_map.end())
                {
                    // 表明result此前并没有该点记录
                    result_map[tempNode] = distance + weight;
                    path[tempNode] = node;
                }
                else
                {
                    if ((distance + weight) <= (result_map[tempNode]))
                    {
                        result_map[tempNode] = (distance + weight);
                        path[tempNode] = node;
                    }
                }
            }
        }
        minWeight = 999;
        minNode = nullptr;
        for (auto i = result_map.begin(); i != result_map.end(); i++)
        {
            Node *tempNode = i->first;
            int tempLength = i->second;
            if ((selected.find(tempNode) == selected.end()) && (tempLength <= minWeight))
            {
                minWeight = tempLength;
                minNode = tempNode;
            }
        }
        // 找到minNOde;使用node记录在更新的过程中的最短边
        if (minNode != nullptr)
        {
            selected.insert(minNode);
            node = minNode;
        }
    }
    cout << "打印路径和长度:" << endl;
    for (auto it = result_map.begin(); it != result_map.end(); it++)
    {
        cout << "到" << it->first->value << "的路径：" << endl;
        printPath(path, it->first);
        cout << endl;
        cout << "总长度为：" << it->second << endl;
    }
}
int main()
{ //{3,4,4},{4,3,4}
    vector<vector<int>> graphArr{{1, 3, 2}, {1, 2, 5}, {4, 2, 3}, {2, 5, 2}, {6, 5, 3}, {4, 6, 6}, {3, 1, 2}, {2, 1, 5}, {2, 4, 3}, {5, 2, 2}, {5, 6, 3}, {6, 4, 6}};
    Graph *graph = transforGraph(graphArr);
    widthProority(graph);
    depthPrority(graph);
    vector<vector<int>> graphArr01{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 4, 1}};
    Graph *graph01 = transforGraph(graphArr01);
    topsisSort(graph01);
    vector<vector<int>> graphArr02{{1, 3, 1}, {2, 3, 5}, {3, 4, 5}, {3, 5, 6}, {3, 6, 4}, {1, 2, 6}, {1, 4, 5}, {2, 5, 3}, {5, 6, 6}, {4, 6, 2}, {3, 1, 1}, {3, 2, 5}, {4, 3, 5}, {5, 3, 6}, {6, 3, 4}, {2, 1, 6}, {4, 1, 5}, {5, 2, 3}, {6, 5, 6}, {6, 4, 2}};
    Graph *graph02 = transforGraph(graphArr02);
    Krustkra(graph02);
    Prim(graph02);
    vector<vector<int>> graphArr03{{1, 4, 2}, {4, 1, 2}, {4, 5, 16}, {5, 4, 16}, {2, 5, 10}, {5, 2, 10}, {1, 2, 3}, {2, 1, 3}, {1, 3, 15}, {3, 1, 15}, {3, 5, 14}, {5, 3, 14}, {3, 4, 7}, {4, 3, 7}, {3, 2, 2}, {2, 3, 2}};
    Graph *graph03 = transforGraph(graphArr03);
    Dijsktra(graph03);
    return 0;
}