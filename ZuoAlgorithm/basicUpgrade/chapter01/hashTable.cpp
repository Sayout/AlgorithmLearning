#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <queue>
#include <stack>
#include <unordered_set>
#include <cmath>
#include <algorithm>
using namespace std;

class RandomPool
{
public:
    int size = 0;
    unordered_map<int, char> index_node;
    unordered_map<char, int> node_index;
    void insertElement(char value)
    {
        // 不重复插入
        if (node_index.find(value) == node_index.end())
        {
            // map中不存在
            index_node[this->size] = value;
            node_index[value] = this->size;
            this->size++;
        }
    }
    void deleteElement(char value)
    {
        if (node_index.find(value) == node_index.end())
        {
            return;
        }
        else
        {
            int index = node_index[value];
            char lastValue = index_node[this->size - 1];
            char lastIndex = this->size - 1;
            if (index != (this->size - 1))
            {
                node_index.erase(value);
                node_index[lastValue] = lastIndex;
                index_node.erase(lastIndex);
                index_node[index] = lastValue;
            }
            else
            {
                index_node.erase(index);
                node_index.erase(value);
            }
            this->size--; // 千万不要忘记了
        }
    }
    // 等概率随机返回结构中的任何一个key
    char getRandom()
    {
        srand(time(NULL));
        int index = rand() % (this->size);
        return index_node[index];
    }
    RandomPool() {}
};
// TODO island
// 感染后的结果需要进行体现，所以引用不可少
void infect(vector<vector<int>> &area, int row, int col)
{
    if (row < 0 || row >= area.size() || col < 0 || col >= area[0].size() || area[row][col] != 1)
    {
        return;
    }
    area[row][col] = 2;
    infect(area, row - 1, col);
    infect(area, row + 1, col);
    infect(area, row, col - 1);
    infect(area, row, col + 1);
}
void island(vector<vector<int>> area)
{
    int number = 0;
    int rows = area.size();
    int cols = area[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (area[i][j] == 1)
            {
                infect(area, i, j);
                number++;
            }
        }
    }
    cout << "Number of islands :" << number << endl;
}
// TODO 并查集，union,isSameSet达到较高的复杂度
template <typename T>
class Node
{
public:
    T value;
    Node(T v)
    {
        this->value = v;
    }
};
template <typename T>
class ParallelSearchSet
{
public:
    unordered_map<T, Node<T> *> value_node;
    unordered_map<Node<T> *, Node<T> *> node_set;
    unordered_map<Node<T> *, int> set_size;

    ParallelSearchSet(vector<T> values)
    {
        for (int i = 0; i < values.size(); i++)
        {
            if (value_node.find(values[i]) == value_node.end())
            {
                value_node[values[i]] = new Node<T>(values[i]);
            }
        }
        // 初始化并查集，并查集的所有节点各自形成一个集合
        for (auto it = this->value_node.begin(); it != this->value_node.end(); it++)
        {
            T value = it->first;
            Node<T> *node = it->second;
            if (node_set.find(node) == node_set.end())
            {
                node_set[node] = node;
            }
            if (set_size.find(node) == set_size.end())
            {
                set_size[node] = 1;
            }
        }
    }

    Node<T> *findHead(Node<T> *node)
    {
        // finHead过程中进行扁平化处理

        queue<Node<T> *> que;
        while (node_set[node] != node)
        {
            // 扁平化
            que.push(node);
            node = node_set[node];
        }
        while (!que.empty())
        {
            Node<T> *temp = que.front();
            node_set[temp] = node;
            que.pop();
        }
        return node;
    }
    bool isSameSet(T value1, T value2)
    {
        Node<T> *node01 = nullptr;
        Node<T> *node02 = nullptr;
        if (value_node.find(value1) != value_node.end())
        {
            node01 = value_node[value1];
        }
        if (value_node.find(value2) != value_node.end())
        {
            {
                node02 = value_node[value2];
            }
            if (node01 == nullptr || node02 == nullptr)
            {
                return false;
            }
            return findHead(node01) == findHead(node02);
        }
    }
    void unionSet(T value1, T value2)
    {
        if (!isSameSet(value1, value2))
        {
            // isSameSet中已经判断是否存在value1,value2
            // 合并的过程应该是将size更大的Set覆盖数量较小的set
            Node<T> *node01 = value_node[value1];
            Node<T> *node02 = value_node[value2];
            Node<T> *head01 = node_set[node01];
            Node<T> *head02 = node_set[node02];
            int size1 = set_size[head01];
            int size2 = set_size[head02];
            if (size1 >= size2)
            {
                node_set[head02] = head01;
                set_size.erase(head02);
                set_size[head01] = size1 + size2;
            }
        }
    }
};
// TODO KMP算法
// nextArr[i]表示前i-1个字符串的最长前后缀最匹配和

vector<int> getNextArr(vector<char> charArr)
{
    vector<int> nextArr;
    if (charArr.size() == 0)
    {
        return nextArr;
    }
    nextArr = vector<int>(charArr.size(), 0);
    if (charArr.size() >= 1)
    {
        nextArr[0] = -1;
    }
    if (charArr.size() >= 2)
    {
        nextArr[1] = 0;
    }
    int index = 2;
    int next_index = nextArr[index - 1];
    while (index < charArr.size())
    {
        if (charArr[index - 1] == charArr[next_index])
        {
            nextArr[index] = next_index + 1;
            index++;
            next_index = nextArr[index - 1];
        }
        else if (next_index == 0)
        {
            nextArr[index] == 0;
            index++;
            next_index = nextArr[index - 1];
        }
        else
        {
            next_index = nextArr[next_index];
        }
    }
    return nextArr;
}
int KMPGetSubStr(vector<char> str1, vector<char> str2)
{
    int index01 = 0;
    int index02 = 0;
    if (str2.size() > str1.size())
    {
        return -1;
    }
    vector<int> nextArr = getNextArr(str2);
    while (index01 < str1.size() && index02 < str2.size())
    {
        if (str1[index01] == str2[index02])
        {
            index01++;
            index02++;
        }
        else if (index02 == 0)
        {
            index01++;
        }
        else
        {
            index02 = nextArr[index02];
        }
    }
    if (index02 == str2.size())
    {
        return (index01 - index02);
    }
    else
    {
        return -1;
    }
}
int main()
{
    RandomPool *RP = new RandomPool();
    RP->insertElement('a');
    RP->insertElement('b');
    RP->insertElement('b');
    RP->insertElement('c');
    RP->insertElement('d');
    RP->insertElement('c');
    cout << RP->getRandom() << endl;
    cout << RP->getRandom() << endl;
    cout << RP->getRandom() << endl;
    cout << RP->getRandom() << endl;
    RP->deleteElement('b');
    RP->deleteElement('a');
    cout << RP->getRandom() << endl;
    cout << RP->getRandom() << endl;
    vector<vector<int>> islands{{0, 0, 1, 0, 1, 0}, {1, 1, 1, 0, 1, 0}, {1, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0}};
    island(islands);

    vector<char> arr_char{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    ParallelSearchSet<char> *PS = new ParallelSearchSet<char>(arr_char);
    PS->unionSet('a', 'b');
    cout << "a和b是否属于同一个集合？" << PS->isSameSet('a', 'b') << endl;
    PS->unionSet('b', 'c');
    cout << "a和c是否属于同一个集合？" << PS->isSameSet('a', 'c') << endl;
    PS->unionSet('f', 'g');
    cout << "f和g是否属于同一个集合？" << PS->isSameSet('f', 'g') << endl;
    PS->unionSet('d', 'e');
    cout << "d和e是否属于同一个集合？" << PS->isSameSet('d', 'e') << endl;
    PS->unionSet('g', 'e');
    cout << "f和d是否属于同一个集合？" << PS->isSameSet('f', 'd') << endl;

    vector<char> subStr{'a', 'b', 'b', 's', 't', 'a', 'b', 'b', 'e', 'c', 'a', 'b', 'b', 's', 't', 'a', 'b', 'b'};
    vector<char> str01{'a', 'b', 'b', 's', 'a', 'b', 'b', 't', 'c', 'a', 'b', 'b', 's', 'a', 'b', 'b', 't', 'c', 'a', 'b', 'b', 's', 'a', 'b', 'b', 'w'};
    vector<char> str02{'a', 'b', 'b', 's', 'a', 'b', 'b', 't', 'c', 'a', 'b', 'b', 's', 'a', 'b', 'b', 'w'};

    vector<int> nextArr = getNextArr(subStr);
    cout << "匹配字串开始的位置index01: " << KMPGetSubStr(str01, str02) << endl;
    return 0;
}