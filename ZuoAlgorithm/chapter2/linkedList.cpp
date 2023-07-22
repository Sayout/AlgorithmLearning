// 链表章节
#include <iostream>
#include <list>
#include <vector>
#include <ctime>
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

int main()
{
    srand(time(NULL));
    Node<int> *headNode = new Node<int>();
    vector<int> arr;
    int maxLen = 50;
    int maxNum = 500;
    generatorVec(arr, maxLen, maxNum);

    createLinkedList(arr, headNode);
    printLinkedList(headNode);
    reverseLinkedList(headNode);
    printLinkedList(headNode);

    DNode<int> *headNodeD = new DNode<int>();
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

    return 0;
}