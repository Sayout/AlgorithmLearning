/*
 * @Author: Sayout zwbalala@icloud.com
 * @Date: 2023-07-27 11:52:01
 * @LastEditors: Sayout zwbalala@icloud.com
 * @LastEditTime: 2023-07-27 20:11:40
 * @FilePath: \C++\ZuoAlgorithm\chapter3\binaryTree.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <stack>
#include <queue>
#include <cmath>
#include <unordered_map>
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
    //TODO ！！记住！！不要随便调整class以及解析函数中参数的位置，否则容易出错
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

    FullReturn iF=isFullTree(node01);
    if(iF.isFull==true)
        cout << "是满二叉树" << endl;
    else
        cout << "不是满二叉树" << endl;
    return 0;
}