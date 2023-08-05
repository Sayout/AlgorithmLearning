#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
// 树形 DP
template <typename T>
class Node
{
public:
    T value;
    Node<T> *left;
    Node<T> *right;
    Node(T v)
    {
        this->value = v;
        this->left = nullptr;
        this->right = nullptr;
    }
};
class TreeInfo
{
public:
    int maxDistance;
    int height;
    TreeInfo(int d, int h)
    {
        this->maxDistance = d;
        this->height = h;
    }
};
template <typename T>
TreeInfo *getMaxDistance(Node<T> *root)
{
    if (root == nullptr)
    {
        return new TreeInfo(0, 0);
    }
    Node<T> *temp = root;
    TreeInfo *leftInfo = getMaxDistance(root->left);
    TreeInfo *rightInfo = getMaxDistance(root->right);
    int maxDis = max(leftInfo->maxDistance, rightInfo->maxDistance);
    int selfHeight = max(leftInfo->height, rightInfo->height) + 1;
    int centDis = (leftInfo->height + rightInfo->height + 1);
    maxDis = maxDis > centDis ? maxDis : centDis;
    return new TreeInfo(maxDis, selfHeight);
}
// 派对最大快乐值
class Employee
{
public:
    int happy;                      // 员工能带来的快乐值
    vector<Employee *> subordinate; // 员工直属下级
    // 这里不进行value的更改，所以直接值引用就行
    Employee(int hp)
    {
        this->happy = hp;
    }
};
class HappyClass
{
public:
    int Maxparti;
    int n_Maxparti;
    HappyClass(int p, int n)
    {
        this->Maxparti = p;
        this->n_Maxparti = n;
    }
};
HappyClass *getMaxHappyLevel(Employee *boss)
{
    if (boss == nullptr)
    {
        return new HappyClass(0, 0);
    }
    // 参与
    int parti = boss->happy;
    int N_parti = 0;
    vector<Employee *> tempVec = (boss->subordinate);
    for (int i = 0; i < tempVec.size(); i++)
    {
        HappyClass *HC = getMaxHappyLevel(tempVec[i]);
        parti = parti + HC->n_Maxparti;
        N_parti = N_parti + max(
                                HC->Maxparti, HC->n_Maxparti);
    }
    return new HappyClass(parti, N_parti);
}
// Morris遍历
template <typename T>
void Morris(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    Node<T> *cur = root;
    while (cur != nullptr)
    {
        if (cur->left == nullptr)
        {
            // 头节点没有左子树
            //  指针右移
            cur = cur->right;
        }
        else
        {
            // 找到左子树的右边界
            Node<T> *rightBound = cur->left;
            while (rightBound->right != nullptr && rightBound->right != cur)
            {
                rightBound = rightBound->right;
            }
            if (rightBound->right == nullptr)
            {
                rightBound->right = cur;
                // 第一次遍历含左子树的节点
                cur = cur->left;
            }
            else if (rightBound->right == cur)
            {
                rightBound->right = nullptr;
                cur = cur->right;
            }
        }
    }
}
// 改造morris进行先序中序后序遍历
// Morris遍历
template <typename T>
void MorrisMid(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    Node<T> *cur = root;
    while (cur != nullptr)
    {
        if (cur->left == nullptr)
        {
            // 头节点没有左子树
            //  指针右移
            cout << cur->value << " ";
            cur = cur->right;
        }
        else
        {
            // 找到左子树的右边界
            Node<T> *rightBound = cur->left;
            while (rightBound->right != nullptr && rightBound->right != cur)
            {
                rightBound = rightBound->right;
            }
            if (rightBound->right == nullptr)
            {
                rightBound->right = cur;
                // 第一次遍历含左子树的节点
                cout << cur->value << " ";
                cur = cur->left;
            }
            else if (rightBound->right == cur)
            {
                rightBound->right = nullptr;
                // 第二次遍历

                cur = cur->right;
            }
        }
    }
    cout << endl;
}
template <typename T>
void MorrisFirst(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    Node<T> *cur = root;
    while (cur != nullptr)
    {
        if (cur->left == nullptr)
        {
            // 头节点没有左子树
            //  指针右移
            cout << cur->value << " ";
            cur = cur->right;
        }
        else
        {
            // 找到左子树的右边界
            Node<T> *rightBound = cur->left;
            while (rightBound->right != nullptr && rightBound->right != cur)
            {
                rightBound = rightBound->right;
            }
            if (rightBound->right == nullptr)
            {
                rightBound->right = cur;
                // 第一次遍历含左子树的节点
                cur = cur->left;
            }
            else if (rightBound->right == cur)
            {
                rightBound->right = nullptr;
                // 第二次遍历
                cout << cur->value << " ";
                cur = cur->right;
            }
        }
    }
    cout << endl;
}
// 相当于链表大的逆序打印并调整回原来的结构
template <typename T>
void reversePrint(Node<T> *root)
{
    Node<T> *pre = nullptr;
    Node<T> *cur = root;
    if (cur == nullptr)
    {
        cout << root->value << " ";
    }

    while (cur != nullptr)
    {
        Node<T> *next = cur->right;
        cur->right = pre;
        pre = cur;
        cur = next;
    }
    cur = pre;
    pre = nullptr;
    while (cur != nullptr)
    {
        cout << cur->value << " ";
        Node<T> *next = cur->right;
        cur->right = pre;
        pre = cur;
        cur = next;
    }
}
template <typename T>
void MorrisBehind(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    Node<T> *cur = root;
    while (cur != nullptr)
    {
        if (cur->left == nullptr)
        {
            // 头节点没有左子树
            //  指针右移
            cur = cur->right;
        }
        else
        {
            // 找到左子树的右边界
            Node<T> *rightBound = cur->left;
            while (rightBound->right != nullptr && rightBound->right != cur)
            {
                rightBound = rightBound->right;
            }
            if (rightBound->right == nullptr)
            {
                rightBound->right = cur;
                // 第一次遍历含左子树的节点
                cur = cur->left;
            }
            else if (rightBound->right == cur)
            {
                rightBound->right = nullptr;
                // 第二次遍历
                // 在这里进行右边界的逆序打印，为了保证空间复杂度为1，不使用stack
                reversePrint(cur->left);
                cur = cur->right;
            }
        }
    }
    reversePrint(root);
    cout << endl;
}
// Morris遍历应用，中序方法确定是否是搜索二叉树
template <typename T>
bool MorrisBST(Node<T> *root)
{
    if (root == nullptr)
    {
        return true;
    }
    Node<T> *cur = root;
    int preValue = -1;
    while (cur != nullptr)
    {
        if (cur->left == nullptr)
        {
            // 头节点没有左子树
            //  指针右移
            if (preValue > cur->value)
            {
                return false;
            }
            preValue = cur->value;
            cur = cur->right;
        }
        else
        {
            // 找到左子树的右边界
            Node<T> *rightBound = cur->left;
            while (rightBound->right != nullptr && rightBound->right != cur)
            {
                rightBound = rightBound->right;
            }
            if (rightBound->right == nullptr)
            {
                rightBound->right = cur;
                // 第一次遍历含左子树的节点
                cur = cur->left;
            }
            else if (rightBound->right == cur)
            {
                rightBound->right = nullptr;
                if (preValue > cur->value)
                {
                    return false;
                }
                preValue = cur->value;
                cur = cur->right;
            }
        }
    }
    return true;
}
int main()
{
    // Node<int>*node01=new Node<int>(1);
    // Node<int>*node02=new Node<int>(2);
    // Node<int>*node03=new Node<int>(3);
    // Node<int>*node04=new Node<int>(4);
    // Node<int>*node05=new Node<int>(5);
    // Node<int>*node06=new Node<int>(6);
    // Node<int>*node07=new Node<int>(7);
    // Node<int>*node08=new Node<int>(8);
    // Node<int>*node09=new Node<int>(9);
    // Node<int>*node10=new Node<int>(10);
    // Node<int>*node11=new Node<int>(11);
    // Node<int>*node12=new Node<int>(12);
    // Node<int>*node13=new Node<int>(13);
    // Node<int>*node14=new Node<int>(14);
    Node<int> *node01 = new Node<int>(8);
    Node<int> *node02 = new Node<int>(2);
    Node<int> *node03 = new Node<int>(13);
    Node<int> *node04 = new Node<int>(1);
    Node<int> *node05 = new Node<int>(7);
    Node<int> *node06 = new Node<int>(6);
    Node<int> *node07 = new Node<int>(3);
    Node<int> *node08 = new Node<int>(4);
    Node<int> *node09 = new Node<int>(5);
    Node<int> *node10 = new Node<int>(14);
    Node<int> *node11 = new Node<int>(9);
    Node<int> *node12 = new Node<int>(12);
    Node<int> *node13 = new Node<int>(10);
    Node<int> *node14 = new Node<int>(11);
    node01->left = node02;
    node01->right = node03;
    node02->left = node04;
    node02->right = node05;
    node03->left = node11;
    node03->right = node10;
    node05->left = node06;
    node11->right = node12;
    node12->left = node13;
    // node02->right=node05;
    node06->left = node07;
    node07->right = node08;
    node08->right = node09;
    // node02->right=node05;
    // node02->left=node04;
    node13->right = node14;
    TreeInfo *TI = getMaxDistance(node01);
    cout << "maxDistance" << TI->maxDistance << endl;
    Employee *boss = new Employee(1);
    // Employee*employee=new Employee(1);
    Employee *employee1 = new Employee(20);
    Employee *employee2 = new Employee(4);
    Employee *employee3 = new Employee(30);
    Employee *employee4 = new Employee(5);
    Employee *employee5 = new Employee(5);
    Employee *employee6 = new Employee(4);
    Employee *employee7 = new Employee(2);
    Employee *employee8 = new Employee(30);
    Employee *employee9 = new Employee(20);
    Employee *employee10 = new Employee(50);
    Employee *employee11 = new Employee(30);
    boss->subordinate.push_back(employee1);
    boss->subordinate.push_back(employee2);
    boss->subordinate.push_back(employee3);
    boss->subordinate.push_back(employee4);
    employee1->subordinate.push_back(employee5);
    employee1->subordinate.push_back(employee6);
    employee2->subordinate.push_back(employee7);
    employee2->subordinate.push_back(employee8);
    employee4->subordinate.push_back(employee9);
    employee4->subordinate.push_back(employee10);
    employee6->subordinate.push_back(employee11);

    HappyClass *HC = getMaxHappyLevel(boss);
    cout << "派对的最大欢乐值为 " << max(HC->Maxparti, HC->n_Maxparti) << endl;

    MorrisFirst(node01);
    MorrisMid(node01);
    MorrisBehind(node01);
    cout << "isSearchTree " << MorrisBST(node01) << endl;
    return 0;
}