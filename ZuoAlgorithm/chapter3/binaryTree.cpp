/*
 * @Author: Sayout zwbalala@icloud.com
 * @Date: 2023-07-27 11:52:01
 * @LastEditors: Sayout zwbalala@icloud.com
 * @LastEditTime: 2023-07-29 12:14:27
 * @FilePath: \C++\ZuoAlgorithm\chapter3\binaryTree.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <stack>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
using namespace std;
// **二叉树**
template <typename T>
class Node
{
public:
    T value;
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node(T v)
    {
        this->value = v;
    }
    Node() {}
};
// TODO01 递归遍历：前中后序
template <typename T>
void beforeReadRe(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->value << " ";
    beforeReadRe(root->left);
    beforeReadRe(root->right);
}

template <typename T>
void midReadRe(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    midReadRe(root->left);
    cout << root->value << " ";
    midReadRe(root->right);
}

template <typename T>
void afterReadRe(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    afterReadRe(root->left);
    afterReadRe(root->right);
    cout << root->value << " ";
}

// TODO02 非递归遍历：前中后序
template <typename T>
void beforeRead(Node<T> *root)
{
    stack<Node<T> *> stack;
    Node<T> *temp = root;
    stack.push(temp);

    while (!stack.empty())
    {
        temp = stack.top();
        cout << temp->value << " ";
        stack.pop();
        // 先右再左
        if (temp->right != nullptr)
        {
            stack.push(temp->right);
        }
        if (temp->left != nullptr)
        {
            stack.push(temp->left);
        }
    }
}
template <typename T>
void midRead(Node<T> *root)
{
    // 左边界弹入，打印，是否有右子树，有，对右子树循环循环
    stack<Node<T> *> stack0;
    Node<T> *temp = root;
    // stack0.push(temp);
    // temp=temp->left;
    while (temp != nullptr)
    {
        stack0.push(temp);
        temp = temp->left;
    }
    while (!stack0.empty())
    {
        temp = stack0.top();
        cout << temp->value << " ";
        stack0.pop();
        if (temp->right != nullptr)
        {
            temp = temp->right;
            while (temp != nullptr)
            {
                stack0.push(temp);
                temp = temp->left;
            }
        }
    }
}
template <typename T>
void afterRead(Node<T> *root)
{
    stack<Node<T> *> stack0;
    stack<Node<T> *> collector;
    Node<T> *temp = root;
    stack0.push(temp);
    while (!stack0.empty())
    {
        temp = stack0.top();
        collector.push(temp);
        stack0.pop();
        if (temp->left != nullptr)
        {
            stack0.push(temp->left);
        }
        if (temp->right != nullptr)
        {
            stack0.push(temp->right);
        }
    }
    while (!collector.empty())
    {
        temp = collector.top();
        cout << temp->value << " ";
        collector.pop();
    }
}
// TODO3 宽度优先遍历--》求二叉树的最大宽度
template <typename T>
int depthPriority(Node<T> *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int maxDepth = 0;
    Node<T> *temp = root;
    queue<Node<T> *> que;
    // 记录宽度的一系列变量
    unordered_map<Node<T> *, int> node_level;
    que.push(temp);
    node_level[temp] = 1;
    int curr_nodes = 0;
    int curr_level = 1;
    while (!que.empty())
    {
        temp = (que.front());
        cout << temp->value << " ";
        que.pop();
        if (curr_level == node_level.at(temp))
        {
            curr_nodes++;
        }
        else
        {
            // 说明进入下一层
            maxDepth = max(maxDepth, curr_nodes);
            curr_nodes = 1;
            curr_level++;
        }
        if (temp->left != nullptr)
        {
            que.push(temp->left);
            node_level[temp->left] = node_level.at(temp) + 1;
        }
        if (temp->right != nullptr)
        {
            que.push(temp->right);
            node_level[temp->right] = node_level.at(temp) + 1;
        }
    }
    // 注意，在最后一层结束之后直接结束循环，没有将最后一层的nodes更新到maxDepth中
    maxDepth = max(maxDepth, curr_nodes);
    return maxDepth;
}
// methods 2：不使用额外空间
template <typename T>
int depthPriority00(Node<T> *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int maxDepth = 0;
    Node<T> *temp = root;
    queue<Node<T> *> que;
    // 记录宽度的一系列变量
    que.push(temp);
    // node_level[temp]=1;
    int curr_nodes = 1;
    int curr_level = 1;
    Node<T> *curr_end = temp;
    Node<T> *next_end = nullptr;
    while (!que.empty())
    {
        temp = (que.front());
        cout << temp->value << " ";
        que.pop();
        if (temp->left != nullptr)
        {
            que.push(temp->left);
            // node_level[temp->left]=node_level.at(temp)+1;
            next_end = temp->left;
        }
        if (temp->right != nullptr)
        {
            que.push(temp->right);
            // node_level[temp->right]=node_level.at(temp)+1;
            next_end = temp->right;
        }
        if (temp != curr_end)
        {
            curr_nodes++;
        }
        else
        {
            // 说明将进入下一层
            maxDepth = max(maxDepth, curr_nodes);
            curr_nodes = 0;
            curr_end = next_end;
        }
    }
    // 注意，在最后一层结束之后直接结束循环，没有将最后一层的nodes更新到maxDepth中
    maxDepth = max(maxDepth, curr_nodes);
    return maxDepth;
}
// TODO 宽度优先问题：判断是否是完全二叉树
template <typename T>
bool isCompeleteTree(Node<T> *root)
{
    if (root == nullptr)
    {
        cout << "compelete Binary tree" << endl;
        return true;
    }
    queue<Node<T> *> que;
    Node<T> *temp = root;
    que.push(root);
    bool flag = true; // 表示当前遍历的节点的左右孩子双全
    while (!que.empty())
    {
        temp = que.front();
        if (temp->left != nullptr)
        {
            que.push(temp->left);
        }
        if (temp->right != nullptr)
        {
            que.push(temp->right);
        }
        if (temp->right != nullptr && temp->left == nullptr)
        {
            cout << "Not compelete Binary tree" << endl;
            return false;
        }
        if (!flag && (temp->right != nullptr || temp->left != nullptr))
        {
            cout << "Not compelete Binary tree" << endl;
            return false;
        }
        if (temp->right == nullptr || temp->left == nullptr)
        {
            flag = false;
        }
        que.pop();
    }
    cout << "compelete Binary tree" << endl;
    return true;
}

// TODO 4递归套路一系列
// 搜索二叉树：
template <typename T>
class SearchReturn
{
public:
    T min;
    T max;
    bool isSearch;
    SearchReturn(T min_, T max_, bool isSearch_)
    {
        this->min = min_;
        this->max = max_;
        this->isSearch = isSearch_;
    }
};
template <typename T>
SearchReturn<T> isSearchTree(Node<T> *root)
{
    // 搜索二叉树的中序遍历结果是一个递增的
    // 除了全局变量记录外，还可以使用递归套路
    // 这一题还是直接中序遍历全局白能量简单一点
    if (root == nullptr)
    {
        return SearchReturn<T>((T)999, (T)-1, true);
        // 这里初始化不初始好会出问题，当是叶子节点时，min,max都应当是自己
    }
    SearchReturn<T> SRL = isSearchTree(root->left);
    SearchReturn<T> SRR = isSearchTree(root->right);
    T maxL = SRL.max;
    T minR = SRR.min;
    T min = SRL.min <= root->value ? SRL.min : root->value;
    min = min <= SRR.min ? min : SRR.min;
    T max = SRL.max >= root->value ? SRL.max : root->value;
    max = max >= SRR.max ? max : SRR.max;
    bool isSearch = (SRL.isSearch) && (SRR.isSearch) && (maxL < root->value) && (minR > root->value);
    return SearchReturn<T>(min, max, isSearch);
    // 注意这里没有 new
}
template <typename T>
bool isSearchTree00(Node<T> *root)
{
    static bool isSearch = true;
    static T before;
    if (root == nullptr)
    {
        return true;
    }
    if (isSearch == false)
        return false;
    isSearchTree00(root->left);
    if (before > root->value)
    {
        isSearch = false;
    }
    before = root->value;
    isSearchTree00(root->right);
    return isSearch;
}

// TODO 平衡二叉树
class BalanceRetuen
{
public:
    bool isBalance;
    int height;
    // int rightHeight;
    BalanceRetuen(bool iB, int H)
    {
        this->isBalance = iB;
        this->height = H;
        // this->rightHeight=rH;
    }
};
template <typename T>
BalanceRetuen isBalanceTree(Node<T> *root)
{
    if (root == nullptr)
    {
        return BalanceRetuen(true, 0);
    }
    BalanceRetuen BL = isBalanceTree(root->left);
    BalanceRetuen BR = isBalanceTree(root->right);
    int height = max(BL.height, BR.height) + 1;
    bool isbanlanced = (abs(BL.height - BR.height) < 2) && (BL.isBalance) && (BR.isBalance);
    return BalanceRetuen(isbanlanced, height);
}
// TODO 按段是否是满二叉树

class FullReturn
{
public:
    bool isFull;
    int height;
    int nodes;

    FullReturn(bool iF, int h, int ns)
    {
        this->height = h;
        this->isFull = iF;
        this->nodes = ns;
    }
};
template <typename T>
FullReturn isFullTree(Node<T> *root)
{
    if (root == nullptr)
    {
        return FullReturn(true, 0, 0);
    }
    FullReturn LF = isFullTree(root->left);
    FullReturn RF = isFullTree(root->right);
    int nodes = LF.nodes + RF.nodes + 1;
    int height = max(LF.height, RF.height) + 1;
    bool isFull = (LF.isFull) && (RF.isFull) && (nodes == ((1 << (height)) - 1));
    return FullReturn(isFull, height, nodes);
    // TODO ！！记住！！不要随便调整class以及解析函数中参数的位置，否则容易出错
}

// TODO 找最低公共祖先
//  在找最低公共祖先的时候 two methods:
// methods 借用hashMap记录节点的父节点，这样相当于在原来的二叉树中插入了parent指针
// TODO:在getMapping()设置父节点的映射时应该在调用getMapping函数之前自行设置root.parent=root
template <typename T>
void getMapping(Node<T> *root, unordered_map<Node<T> *, Node<T> *> &mapping)
{
    if (root == nullptr)
        return;
    if (root->right != nullptr)
    {
        mapping[root->right] = root;
    }
    if (root->left != nullptr)
    {
        mapping[root->left] = root;
    }
    getMapping(root->left, mapping);
    getMapping(root->right, mapping);
}
template <typename T>
void commonAncestor(Node<T> *root, Node<T> *node01, Node<T> *node02)
{
    unordered_map<Node<T> *, Node<T> *> map_parent;
    unordered_set<Node<T> *> ancestors;
    map_parent[root] = root;
    getMapping(root, map_parent);
    Node<T> *temp01 = node01;
    //!! 注意，map_parent，应该注意当当前节点是另外一个节点的祖先节点的情况，所以当前节点一定要加入到ancestors中
    ancestors.insert(temp01);
    while (map_parent[temp01] != temp01)
    {
        ancestors.insert(map_parent[temp01]);
        temp01 = map_parent[temp01];
    }
    temp01 = node02;
    if (ancestors.find(node02) != ancestors.end())
    {
        cout << node02->value << "是" << node01->value << "的祖先节点" << endl;
    }
    while (map_parent[temp01] != temp01)
    {
        if (ancestors.find(map_parent[temp01]) != ancestors.end())
        {
            cout << node02->value << "和" << node01->value << "的祖先节点是" << (map_parent[temp01])->value << endl;
            break;
        }
        temp01 = map_parent[temp01];
    }
}

// methods 分析几种情况
// 由于递归本质上是从底层往顶层进行递归，所以从最底层开始做如下判断：
/*
（1）self=node1,向上传递
（2）self=node2,向上传递
（3）self=nullptr ，return nullptr
（4）其他情况：对子树进行分类
*/
// 找到的一定是最近的祖先

template <typename T>
Node<T> *getCommonAncestor(Node<T> *root, Node<T> *node01, Node<T> *node02)
{
    if (root == nullptr || root == node01 || root == node02)
    {
        return root;
    }
    Node<T> *left = getCommonAncestor(root->left, node01, node02);
    Node<T> *right = getCommonAncestor(root->right, node01, node02);
    if ((left == node01 && right == node02) || (left == node02 && right == node01))
    {
        return root;
    }
    // if(left==nullptr&&right==nullptr){return nullptr;}

    return left == nullptr ? right : left; // 当出现子节点不是nullptr的情况时，除了两边都不是空情况，其他都返回非空节点
}
// 【纸条打印】
void printFlodPaper(int N, string flag)
{
    if (N == 0)
    {
        return;
    }
    printFlodPaper(N - 1, "down");
    cout << flag << " ";
    printFlodPaper(N - 1, "up");
}
// TODO【先序序列化】：序列化和反序列化的时候，不知道为什么用string和vector都会出现错误，最后用queue的方法，（参数时引用）最终解决了问题
// TODO:这里有点疑惑的？？
//  处理字符串的时候，在通过下标获取数字的时候，不知道为什么返回的是int 类型
//  ！！to_string()转化成字符串s.compare()比较两个字符串的内容是否一致，否则==按照内存地址判断是否是同一个字符串
template <typename T>
void serializeBefore(Node<T> *root, queue<char> &s)
{
    if (root == nullptr)
    {
        s.push('#');
        return;
    }
    s.push(root->value + '0');

    serializeBefore(root->left, s);
    serializeBefore(root->right, s);
}
// index表示字符串开始的下标
// 注意，使用template的时候，函数的参数里面必须有template

Node<int> *serializeBeforeRe(queue<char> &s)
{
    if (s.empty())
    {
        return nullptr;
    }
    if (s.front() == '#')
    {
        s.pop();
        return nullptr;
    }
    else
    {
        Node<int> *node = new Node<int>(s.front() - 48);
        s.pop();
        if (!s.empty())
        {
            node->left = serializeBeforeRe(s);
        }
        if (!s.empty())
        {
            node->right = serializeBeforeRe(s);
        }
        return node;
    }
}

// TODO 找后继节点
template <typename T>
Node<T> *findMidNext(Node<T> *root, Node<T> *node)
{
    if (root == nullptr || node == nullptr)
    {
        return nullptr;
    }
    unordered_map<Node<T> *, Node<T> *> map_parent;
    map_parent[root] = root;
    getMapping(root, map_parent);
    if (node->right != nullptr)
    {
        Node<T> *temp = node->right;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        cout << "nextNode: " << temp->value << endl;
        return temp;
    }
    else
    {
        // 没有右子树
        Node<T> *parent = node;
        while ((map_parent[parent] != parent) && (map_parent[parent]->left != parent))
        {
            parent = map_parent[parent];
        }
        if (map_parent[parent]->left != parent)
        {
            cout << "没有后继节点" << endl;
            return nullptr;
        }
        else
        {
            cout << "nexxtPoint:" << map_parent[parent]->value << endl;
            return map_parent[parent];
        }
    }
}
int main()
{
    // 创建二叉树
    Node<int> *node01 = new Node<int>(1); // 4
    Node<int> *node02 = new Node<int>(2); // 2
    Node<int> *node03 = new Node<int>(3); // 6
    Node<int> *node04 = new Node<int>(4); // 1
    Node<int> *node05 = new Node<int>(5); // 3
    Node<int> *node06 = new Node<int>(6); // 5
    Node<int> *node07 = new Node<int>(7); // 7
    // Node<int> root=new Node(8);
    node01->left = node02;
    node01->right = node03;
    node02->left = node04;
    node02->right = node05;
    node03->left = node06;
    node03->right = node07;

    beforeReadRe(node01);
    cout << endl;
    midReadRe(node01);
    cout << endl;
    afterReadRe(node01);
    cout << endl;

    beforeRead(node01);
    cout << endl;
    midRead(node01);
    cout << endl;
    afterRead(node01);
    cout << endl;

    int maxDepth = depthPriority(node01);
    cout << endl;
    cout << "maxDepth: " << maxDepth << endl;

    SearchReturn<int> SR = isSearchTree(node01);
    if (SR.isSearch)
        cout << "是搜索二叉树" << endl;
    else
        cout << "不是搜索二叉树" << endl;
    bool isSearch = isSearchTree00(node01);
    if (isSearch == true)
        cout << "是搜索二叉树" << endl;
    else
        cout << "不是搜索二叉树" << endl;

    BalanceRetuen BR = isBalanceTree(node01);
    if (BR.isBalance == true)
        cout << "是平衡二叉树" << endl;
    else
        cout << "不是平衡二叉树" << endl;

    isCompeleteTree(node01);

    FullReturn iF = isFullTree(node01);
    if (iF.isFull == true)
        cout << "是满二叉树" << endl;
    else
        cout << "不是满二叉树" << endl;
    // commonAncestor(node01,node01,node05);
    // commonAncestor(node01,node05,node07);
    // commonAncestor(node01,node04,node05);
    // cout<< getCommonAncestor(node01,node01,node05)->value<<endl;
    // cout<<getCommonAncestor(node01,node05,node07)->value<<endl;
    // cout<< getCommonAncestor(node01,node04,node05)->value<<endl;

    printFlodPaper(3, "down");
    cout << endl;
    // 最好不要用string ，string由于是标准库，不能调试
    queue<char> str;
    (serializeBefore(node01, str));
    queue<char> copy = str;
    while (!copy.empty())
    {
        cout << copy.front() << endl;
        copy.pop();
    }
    Node<int> *s_node = serializeBeforeRe(str);
    beforeReadRe(s_node);
    //    string s1=to_string(122);
    // cout<<s1<<endl;
    findMidNext(node01, node07);
    findMidNext(node01, node05);
    findMidNext(node01, node02);
    return 0;
}