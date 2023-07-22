// 链表章节
#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <stack>
using namespace std;

template <typename T>
class Node
{
public:
    T value = 0;
    Node *next = nullptr;
    Node(T v)
    {
        this->value = v;
    }
    Node() {}
    ~Node() {}
};

template <typename T>
class DNode
{
public:
    T value;
    DNode *last = nullptr;
    DNode *next = nullptr;
    DNode(T v)
    {
        this->value = v;
    }
    DNode() {}
    ~DNode() {}
};

template <typename T>
void printLinkedList(Node<T> *headNode)
{
    if (headNode == nullptr)
    {
        return;
    }
    Node<T> *temp = headNode->next;
    while (temp != nullptr)
    {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}

template <typename T>
void printLinkedList(DNode<T> *headNode)
{
    if (headNode == nullptr)
    {
        return;
    }
    DNode<T> *temp = headNode->next;
    while (temp != nullptr)
    {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}

template <typename T>
void createLinkedList(vector<T> arr, Node<T> *headNode)
{
    Node<int> *temp = headNode;
    for (int i = 0; i < arr.size(); i++)
    {
        Node<T> *node = new Node<T>();
        node->value = arr[i];
        temp->next = node;
        temp = node;
    }
}

template <typename T>
void generatorVec(vector<T> &arr, int maxLen, int maxNum)
{
    for (int m = 0; m < (rand() % (maxLen + 1)); m++)
    {
        arr.push_back((rand() % (maxNum + 1)));
    }
}

// TODO1:反转单链表和双链表
template <typename T>
void reverseLinkedList(Node<T> *headNode)
{
    if (headNode == nullptr || headNode->next == nullptr || headNode->next->next == nullptr)
    {
        return;
    }
    else
    {
        Node<T> *p = headNode->next;
        Node<T> *last = nullptr;
        Node<T> *next = p->next;
        p->next = last;
        while (next != nullptr)
        // 注意这里，由于p->next已经反向了，所以应该用next
        {
            last = p;
            p = next;
            next = next->next;
            p->next = last;
        }
        headNode->next = p;
    }
}

template <typename T>
void createDLinkedList(vector<T> arr, DNode<T> *headNode)
{
    DNode<int> *temp = headNode;
    for (int i = 0; i < arr.size(); i++)
    {
        DNode<T> *node = new DNode<T>();
        node->value = arr[i];
        node->last = temp;
        temp->next = node;
        temp = node;
    }
}
template <typename T>
void reverseDLinkedList(DNode<T> *headNode)
{
    if (headNode == nullptr || headNode->next == nullptr || headNode->next->next == nullptr)
    {
        return;
    }
    DNode<T> *p = headNode->next;
    DNode<T> *next = p->next;
    p->next = nullptr;
    p->last = next;
    while (next != nullptr)
    {
        p = next;
        next = next->next;
        p->next = p->last;
        p->last = next;
    }
    headNode->next = p;
}
// TODO2 打印两个有序链表的公共部分
template <typename T>
void printPublicArea(Node<T> *h1, Node<T> *h2)
{
    Node<T> *temp01 = h1->next;
    Node<T> *temp02 = h2->next;
    // 有序链表，直接遍历就好了
    //  1,2,2,2,3,4,4,5
    // 1,2,2,4,4,5
    while (temp01 != nullptr && temp02 != nullptr)
    {
        if (temp01->value < temp02->value)
        {
            temp01 = temp01->next;
        }
        else if (temp01->value > temp02->value)
        {
            temp02 = temp02->next;
        }
        else
        {
            cout << temp01->value << "  ";
            temp01 = temp01->next;
            temp02 = temp02->next;
        }
    }
    cout << endl;
}

// TODO3 判断一个链表是否为回文结构
// Method01:直接压栈 5min
template <typename T>
bool isReversable01(Node<T> *headNode)
{
    stack<T> help;
    Node<T> *temp = headNode->next;
    while (temp != nullptr)
    {
        help.push(temp->value);
        temp = temp->next;
    }
    temp = headNode->next;
    bool flag = true;
    while (temp != nullptr)
    {
        if ((temp->value) != help.top())
        {
            flag = false;
            break;
        }
        help.pop();
        temp = temp->next;
    }
    return flag;
}
// Method02:快慢指针+栈 12min+debug,因为odd的考虑
template <typename T>
bool isReversable02(Node<T> *headNode)
{
    int flag = true;
    Node<T> *slow = headNode;
    Node<T> *fast = headNode->next;
    stack<T> help;
    // 无论长度如何:慢指针先更新，快指针遇到null时停止
    bool odd = false; // 记录长度是奇数偶数
    if (fast == nullptr || (fast->next == nullptr))
    {
        return true;
    }
    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast != nullptr)
        {
            fast = fast->next;
        }
        else
        {
            odd = true;
            break;
        }
    }
    // 慢指针指向中点
    Node<T> *mid = slow;
    if (odd == true)
    { // 奇数时中点不入栈
        mid = mid->next;
    }
    while (mid != nullptr)
    {
        help.push(mid->value);
        mid = mid->next;
    }
    mid = headNode->next;
    while (!help.empty())
    {
        if ((help.top()) != (mid->value))
        {
            flag = false;
            break;
        }
        help.pop();
        mid = mid->next;
    }
    return flag;
}
// Method03:快慢指针+链表反转 20min(前提是对反转链表很熟悉，且对odd判断熟悉)
template <typename T>
bool isReversable03(Node<T> *headNode)
{
    printLinkedList(headNode);
    bool falg = true;
    Node<T> *slow = headNode;
    Node<T> *fast = headNode->next;
    bool odd = false;
    if (fast == nullptr || (fast->next == nullptr))
    {
        return true;
    }
    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast == nullptr)
        {
            odd = true;
            break;
        }
        else
        {
            fast = fast->next;
        }
    }
    Node<T> *mid = slow;
    Node<T> *newHead = new Node<int>();
    Node<T> *last = mid;
    Node<T> *next = mid->next;
    mid->next = nullptr;
    while (next != nullptr)
    {
        mid = next;
        next = next->next;
        mid->next = last;
        last = mid;
    }
    newHead->next = mid;
    Node<T> *newTemp = newHead->next;
    mid = headNode->next;
    while (mid != slow)
    {
        if (mid->value != newTemp->value)
        {
            falg = false;
            break;
        }
        mid = mid->next;
        newTemp = newTemp->next;
    }
    // 调整成原来的结构
    mid = newHead->next;
    last = nullptr;
    next = mid->next;
    mid->next = last;
    while (next != nullptr)
    {
        last = mid;
        mid = next;
        next = next->next;
        mid->next = last;
    }
    printLinkedList(headNode);
    return falg;
}
int main()
{
    srand(time(NULL));
    Node<int> *headNode = new Node<int>();
    Node<int> *headNode01 = new Node<int>();
    vector<int> arr{1, 2, 2, 2, 2, 2, 1, 5};
    vector<int> arr01{1, 3, 3};
    createLinkedList(arr, headNode);
    createLinkedList(arr01, headNode01);
    // printPublicArea(headNode,headNode01);
    cout << isReversable01(headNode) << endl;
    cout << isReversable02(headNode) << endl;
    cout << isReversable03(headNode) << endl;
    cout << isReversable01(headNode01) << endl;
    cout << isReversable02(headNode01) << endl;
    cout << isReversable03(headNode01) << endl;
    /*
     vector<int> arr;
     int maxLen = 50;
     int maxNum = 500;
     generatorVec(arr, maxLen, maxNum);

     createLinkedList(arr, headNode);
     printLinkedList(headNode);
     reverseLinkedList(headNode);
     printLinkedList(headNode);
     */
    DNode<int> *headNodeD = new DNode<int>();

    /*
    createDLinkedList(arr, headNodeD);
    printLinkedList(headNodeD);
    reverseDLinkedList(headNodeD);
    printLinkedList(headNodeD);
    // 手动释放内存
    Node<int> *temp = headNode;
    while (headNode != nullptr)
    {
        headNode = headNode->next;
        delete temp;
        temp = headNode;
    }
    */

    return 0;
}