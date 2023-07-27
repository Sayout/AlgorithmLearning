/*
 * @Author: Sayout zwbalala@icloud.com
 * @Date: 2023-07-27 11:52:01
 * @LastEditors: Sayout zwbalala@icloud.com
 * @LastEditTime: 2023-07-27 18:15:05
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
int main()
{
    // 创建二叉树
    Node<int> *node01 = new Node<int>(1);
    Node<int> *node02 = new Node<int>(2);
    Node<int> *node03 = new Node<int>(3);
    Node<int> *node04 = new Node<int>(4);
    Node<int> *node05 = new Node<int>(5);
    Node<int> *node06 = new Node<int>(6);
    Node<int> *node07 = new Node<int>(7);
    // Node<int> root=new Node(8);
    node01->left = node02;
    node01->right = node03;
    node02->left = node04;
    // node02->right = node05;
    // node03->left = node06;
    // node03->right = node07;

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
    return 0;
}