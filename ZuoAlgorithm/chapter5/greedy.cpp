#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;
// TODO :前缀树
// class Node {
// public:
//     int pass = 0;
//     int end = 0;
//     vector<Node*>nexts;
//     Node() {
//         for (int i = 0;i < 26;i++) {
//             nexts.push_back(nullptr);
//         }
//     }
// };
// void createPreTree(vector<char>s, Node* root) {
//     Node* node = root;
//     root->pass++;
//     if (s.size() == 0) {
//         root->end++;
//     }
//     vector<Node*>*next = &(root->nexts);
//     //TODO:一个十分关键的问题，vector<Node*>*next并不是像指针、数组一类的东西，这样的赋值并不是基于地址的，因而所有的操作不会对root起作用，所以
//     //这里使用引用
//     Node* temp;
//     for (int i = 0;i < s.size();i++) {

//         int index = s[i] - 97;

//         if (((*next)[index]) == nullptr) {
//             temp = new Node();
//             (*next)[index] = temp;
//         }
//         (*next)[index]->pass++;
//         if (i == (s.size() - 1)) {
//             (*next)[index]->end++;
//         }
//         next = &((*next)[index]->nexts);
//     }
// }
template <typename T>
class Node
{
public:
    int pass = 0;
    int end = 0;
    unordered_map<T, Node<T> *> hashMap;
};
template <typename T>
void createPreTree(vector<T> s, Node<T> *root)
{
    Node<T> *node = root;
    root->pass++;
    if (s.size() == 0)
    {
        root->end++;
    }
    unordered_map<T, Node<T> *> *hashmap = &(root->hashMap);
    // TODO:一个十分关键的问题，vector<Node*>*next并不是像指针、数组一类的东西，这样的赋值并不是基于地址的，因而所有的操作不会对root起作用，所以
    // 这里使用引用
    Node<T> *temp;
    for (int i = 0; i < s.size(); i++)
    {
        if ((*hashmap).find(s[i]) == (*hashmap).end())
        {
            temp = new Node<T>();
            (*hashmap)[s[i]] = temp;
        }
        ((*hashmap)[s[i]])->pass++;
        if (i == (s.size() - 1))
        {
            (*hashmap)[s[i]]->end++;
        }
        hashmap = &((*hashmap)[s[i]]->hashMap);
    }
}
// 单词出现的次数
template <typename T>
int getWordTimes(Node<T> *root, vector<char> word)
{
    Node<T> *node = root;
    int times = 0;
    unordered_map<T, Node<T> *> h_map = root->hashMap;
    for (int i = 0; i < word.size(); i++)
    {
        if (h_map.find(word[i]) != h_map.end())
        {
            // exist
            if (i == (word.size() - 1))
            {
                times = (h_map[word[i]])->end;
                return times;
            }
            h_map = (h_map[word[i]])->hashMap;
        }
        else
        {
            return times;
        }
    }
    return times;
}
// 前缀出现的次数
template <typename T>
int getPreTimes(Node<T> *root, vector<char> word)
{
    Node<T> *node = root;
    int times = 0;
    unordered_map<T, Node<T> *> h_map = root->hashMap;
    for (int i = 0; i < word.size(); i++)
    {
        if (h_map.find(word[i]) != h_map.end())
        {
            // exist
            if (i == (word.size() - 1))
            {
                times = (h_map[word[i]])->pass;
                return times;
            }
            h_map = (h_map[word[i]])->hashMap;
        }
        else
        {
            return times;
        }
    }
    return times;
}
// 前缀树删除word
template <typename T>
void deletePreWord(Node<T> *root, vector<char> word)
{
    if (getWordTimes(root, word) > 0)
    {
        Node<T> *node = root;
        unordered_map<T, Node<T> *> *h_map = &(root->hashMap);
        // 这里必须是引用
        vector<Node<T> *> startDelete;
        for (int i = 0; i < word.size(); i++)
        {
            unordered_map<T, Node<T> *> *h_temp;
            bool erase = false;
            ((*h_map)[word[i]])->pass--;
            if (i == (word.size() - 1))
            {
                ((*h_map)[word[i]])->end--;
            }
            if (((*h_map)[word[i]])->pass == 0)
            {
                // 释放节点:
                // 只有该条路上的节点会被释放，所以，记录该条路径上的节点题解记录该条hashMap
                // 当获取下一条hashMap时，就可以在记录的前一条hashMap中国进行erase,注意，要使用引用
                h_temp = h_map;
                erase = true;
                startDelete.push_back((*h_map)[word[i]]);
            }
            h_map = &(((*h_map)[word[i]])->hashMap);
            if (erase)
            {
                h_temp->erase(word[i]);
            }
        }
        // 从startDelete开始释放节点
        for (int i = 0; i < startDelete.size(); i++)
        {
            delete startDelete[i];
            startDelete[i] = nullptr;
        }
    }
    else
    {
        for (int i = 0; i < word.size(); i++)
        {
            cout << word[i];
        }
        cout << "不存在" << endl;
    }
}
// TODO:贪心
// 字符串拼接最小字典序
bool PinjieCmp(const string &s1, const string &s2)
{
    return (s1 + s2) < (s2 + s1);
}
string pingJieString(vector<string> strs)
{
    sort(strs.begin(), strs.end(), PinjieCmp);
    string result = "";
    for (int i = 0; i < strs.size(); i++)
    {
        result.append(strs[i]);
    }
    return result;
}
// haffuman coding
template <typename T>
int minCostGetMoney(vector<T> needArr)
{
    priority_queue<T, vector<T>, greater<T>> help;
    // 默认less大根堆
    for (int i = 0; i < needArr.size(); i++)
    {
        help.push(needArr[i]);
    }
    int sum = 0;
    while (!help.empty())
    {
        int tempSum = 0;
        tempSum = tempSum + help.top();
        help.pop();
        if (!help.empty())
        {
            tempSum = tempSum + help.top();
            sum += tempSum;
            help.pop();
            help.push(tempSum);
        }
    }
    return sum;
}
// 会议室时间安排
template <typename T>
class Meet
{
public:
    T start = 0;
    T end = 0;
    Meet(T s, T e)
    {
        this->start = s;
        this->end = e;
    }
};
template <typename T>
bool meetCMP(const Meet<T> &m1, const Meet<T> &m2)
{
    return m1.end < m2.end;
}
template <typename T>
int maxTimesMeeting(vector<Meet<T>> meetings)
{
    // 每一行两个数字，代表开始时间和结束时间
    sort(meetings.begin(), meetings.end(), meetCMP<T>);
    // 注意，使用template时，在比较器中也需要说明《T》
    int times = 0;
    T last_start = 0;
    T last_end = 0;
    for (int i = 0; i < meetings.size(); i++)
    {
        if (meetings[i].start >= last_end)
        {
            times++;
            cout << "meet" << times << ": " << meetings[i].start << "--" << meetings[i].end << endl;
            last_end = meetings[i].end;
        }
    }
    return times;
}
// 项目利润最大化
template <typename T>
class Project
{
public:
    T cost;
    T profit;
    Project(T c, T p)
    {
        this->cost = c;
        this->profit = p;
    }
};
template <typename T>
struct CostCmp
{
    bool operator()(Project<T> *p1, Project<T> *p2)
    {
        return (p1->cost) > (p2->cost); // 小根堆
    }
};
template <typename T>
struct ProfitCmp
{
    bool operator()(Project<T> *p1, Project<T> *p2)
    {
        return (p1->profit) < (p2->profit); // 大根堆
    }
};
template <typename T>
T getMaxProfit(int numLim, int moneyLim, vector<T> cost, vector<T> profit)
{
    T sumFit = 0;
    priority_queue<Project<T> *, vector<Project<T> *>, CostCmp<T>> minCost_heap;
    priority_queue<Project<T> *, vector<Project<T> *>, ProfitCmp<T>> maxProfit_heap;
    for (int i = 0; i < cost.size(); i++)
    {
        Project<T> *pro = new Project<T>(cost[i], profit[i]);
        minCost_heap.push(pro);
    }
    while ((!minCost_heap.empty()) && (minCost_heap.top()->cost <= moneyLim))
    {
        // ！！ 注意判空
        maxProfit_heap.push(minCost_heap.top());
        minCost_heap.pop();
    }
    int number = numLim < cost.size() ? numLim : cost.size();
    while (!maxProfit_heap.empty() && (number != 0))
    { // 狐疑项目数量限制
        // 通过maxProfit_heap记录可以被开始的项目，这样会根据能力限制项目制作的数目
        Project<T> *pro = maxProfit_heap.top();
        maxProfit_heap.pop();
        cout << "cost: " << pro->cost << ", profit: " << pro->profit << endl;
        sumFit = pro->profit + sumFit;
        moneyLim = moneyLim + pro->profit;
        while ((!minCost_heap.empty()) && (minCost_heap.top()->cost <= moneyLim))
        {
            maxProfit_heap.push(minCost_heap.top());
            minCost_heap.pop();
        }
        number--;
    }
    return sumFit;
}
// 堆应用：数据流中，随时可以取得中位数
void getQuickMidNum(vector<int> arr)
{
    int midNum = -1;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    priority_queue<int, vector<int>, less<int>> max_heap;
    if (arr.size() == 0)
    {
        cout << "数据流空" << endl;
    }
    max_heap.push(arr[0]);
    int index = 1;
    int min_len = 0;
    int max_len = 1;
    while ((index < arr.size()))
    {
        if (arr[index] <= max_heap.top())
        {
            max_heap.push(arr[index]);
            max_len++;
        }
        else
        {
            min_heap.push(arr[index]);
            min_len++;
        }
        if (max_len - min_len >= 2)
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
            min_len++;
            max_len--;
        }
        else if (max_len - min_len <= -2)
        {
            max_heap.push(min_heap.top());
            min_heap.pop();
            max_len++;
            min_len--;
        }
        index++;
    }
    if (min_len == max_len)
    {
        midNum = (min_heap.top() + max_heap.top()) / 2;
    }
    else
    {
        midNum = min_len > max_len ? min_heap.top() : max_heap.top();
    }
    cout << "中位数：" << midNum << endl;
}
int main()
{
    vector<vector<char>> s_arr{{'a', 'b', 'c'}, {'a', 'c'}, {'a', 'd'}, {'d', 'f'}, {'b', 'f'}, {'a', 'f'}, {'f', 'e'}, {'e', 'f'}, {'a', 'b'}, {'a', 'b', 'c'}, {'a', 'f', 'b'}, {}, {}};
    Node<char> *root = new Node<char>();
    for (int i = 0; i < s_arr.size(); i++)
    {
        createPreTree(s_arr[i], root);
    }
    cout << getWordTimes(root, vector<char>{'a', 'b'}) << endl;
    cout << getPreTimes(root, vector<char>{'a', 'b'}) << endl;
    // deletePreWord(root, vector<char>{'e', 'f'}) ;
    cout << pingJieString(vector<string>{"ab", "abc"}) << endl;
    cout << minCostGetMoney(vector<int>{1, 2, 3, 4, 5, 6, 7, 7});
    Meet<float> meet01(0, 1.5);
    Meet<float> meet02(1.0, 1.5);
    Meet<float> meet03(0, 0.5);
    Meet<float> meet04(2, 3);
    Meet<float> meet05(2.5, 3.5);
    Meet<float> meet06(3, 3.5);
    Meet<float> meet07(2.5, 3);
    Meet<float> meet08(2, 2.5);
    cout << endl;
    int times = maxTimesMeeting(vector<Meet<float>>{meet01, meet02, meet03, meet04, meet05, meet06, meet07, meet08});
    cout << "会议数目：" << times << endl;
    vector<float> cost{5, 6, 5, 9, 7, 8, 9, 130, 100, 90};
    vector<float> profit{5, 6, 6, 7, 8, 8, 9, 80, 120, 100};
    float maxFit = getMaxProfit(6, 5, cost, profit);
    cout << "最大利润: " << maxFit << endl;
    getQuickMidNum(vector<int>{1, 50, 3, 4, 2, 8, 10, 43, 5, 10, 10, 20}); // 1,2,3,4,5,8,10,10,10,20,43,50
    return 0;
}