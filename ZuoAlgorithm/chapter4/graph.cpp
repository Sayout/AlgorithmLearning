#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include<queue>
#include<stack>
using namespace std;

// TODO 图表
class Edge;
class Node;
class Graph;
class Node
{
public:
    int  value;
    int in;                  // 入度
    int out;                 // 出度
    vector<Node *> nexts; // 临接节点
    vector<Edge *> edges; // 邻接边
    Node(int  v)
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
    int  weight;
    Edge() {}
    Edge(Node *fromNode, Node *toNode, int  w)
    {
        this->from = fromNode;
        this->to = toNode;
        this->weight = w;
    }
};


class Graph
{
public:
    unordered_map<int , Node*> nodes; // 点集
    unordered_set<Edge*> edges;         // 边集
};

// arrGraph:N*3 的数组，分别表示fromNodeValue ,toNodeValue,EdgeWeight
Graph*transforGraph(vector<vector<int>  > arrGraph)
{
    Graph   *graph = new Graph();
    for (int i = 0; i < arrGraph.size(); i++)
    {
        int  fromValue = arrGraph[i][0];
        int  toValue = arrGraph[i][1];
        int  weightValue = arrGraph[i][2];
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
        Node   *fromNode = ((graph->nodes)[fromValue]);
        Node   *toNode = ((graph->nodes)[toValue]);
        fromNode->out++;
        toNode->in++;
        fromNode->nexts.push_back(toNode);
        Edge *newEdge = new Edge(fromNode, toNode, weightValue);
        (fromNode->edges).push_back(newEdge);
        (graph->edges).insert(newEdge);
    }
    return graph;
}
//TODO 图的遍历
//宽度优先遍历
void widthProority(Graph *graph){
    Node*node=(((graph->nodes).begin())->second);
    //随机获取一个节点
    queue<Node*>que;
    unordered_set<Node*> selected_node;//记录已经加入的节点
    que.push(node);
    selected_node.insert(node);
    while(!que.empty()){
        node=que.front();
        cout<<node->value<<" ";
        vector <Node*>nextNodes=node->nexts;
        for(int i=0;i<nextNodes.size();i++){
            if(selected_node.find(nextNodes[i])==selected_node.end()){
            que.push(nextNodes[i]);
            selected_node.insert(nextNodes[i]);
            }
        }
        que.pop();
    }
    cout<<endl;
}
//深度优先遍历
void depthPrority(Graph*graph){
    Node*node=(graph->nodes.begin())->second;
    stack<Node*> sta;
    sta.push(node);
    //进stack的时候就应该进行打印
    cout<<node->value<<" ";
    unordered_set<Node*> selected_nodes;
    selected_nodes.insert(node);
    while(!sta.empty()){
        node=sta.top();
         sta.pop();
        vector< Node*>nextNode=node->nexts;
        int index=0;
        while(index<nextNode.size()&&(selected_nodes.find(nextNode[index])!=selected_nodes.end() )){
            index++;
        }
        //每次只会找到一个满足条件的压入
        if(index<nextNode.size()){
            selected_nodes.insert(nextNode[index]);
            sta.push(node);
            sta.push(nextNode[index]);
            cout<<nextNode[index]->value<<" ";
        }
    }
    cout<<endl;
}
// TODO topsis Sort

int main()
{   //{3,4,4},{4,3,4}
    vector<vector<int>> graphArr{{1,3,2},{1,2,5},{4,2,3},{2,5,2},{6,5,3},{4,6,6},{3,1,2},{2,1,5},{2,4,3},{5,2,2},{5,6,3},{6,4,6}};
    Graph*graph= transforGraph(graphArr);
    widthProority(graph);
    depthPrority(graph);

    return 0;
}