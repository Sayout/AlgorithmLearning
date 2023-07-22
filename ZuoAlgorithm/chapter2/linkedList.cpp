// 链表章节
#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <stack>
#include <unordered_map>
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

// TODO4 链表划分
// Method01 利用数组 41-52:11min
template <typename T>
void swap(vector<T> &arr, int i, int j)
{
    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

template <typename T>
void classifyList01(Node<T> *headNode)
{
    Node<T> *temp = headNode->next;
    vector<T> help;
    while (temp != nullptr)
    {
        help.push_back(temp->value);
        temp = temp->next;
    }
    int small = -1;
    int big = help.size();
    T randNum = help[rand() % big];
    cout << "randNum: " << randNum << endl;
    int i = 0;
    while (i < big)
    {
        if (help[i] < randNum)
        {
            swap(help, ++small, i++);
        }
        else if (help[i] > randNum)
        {
            swap(help, --big, i);
        }
        else
        {
            i++;
        }
    }
    i = 0;
    temp = headNode->next;
    while (temp != nullptr)
    {
        temp->value = help[i++];
        temp = temp->next;
    }
    printLinkedList(headNode);
    cout << endl;
}
// Method02 利用六个边界标志:这种情况可以保持整体稳定 12-
template <typename T>
void classifyList02(Node<T> *headNode)
{
    Node<T> *SH = nullptr;
    Node<T> *ST = nullptr;
    Node<T> *EH = nullptr;
    Node<T> *ET = nullptr;
    Node<T> *BH = nullptr;
    Node<T> *BT = nullptr;
    // 分别代表小于区域，等于区域，大于区域的头和尾
    // 划分

    Node<T> *temp = headNode->next;
    if (temp == nullptr)
    {
        return;
    }
    T randNum = temp->value;
    cout << "ranNum: " << randNum << endl;
    while (temp != nullptr)
    {
        Node<T> *next = temp->next;
        // 记得保存next,不然等会划分全部变成nullptr
        if (temp->value < randNum)
        {
            if (SH == nullptr)
            {
                SH = temp;
            }
            else
            {
                ST->next = temp; //!!注意，这里应该是尾巴的next进行连接
            }
            ST = temp;
            ST->next = nullptr; //!!这一步不能忘记，否则会形成环形
        }
        else if (temp->value == randNum)
        {
            if (EH == nullptr)
            {
                EH = temp;
            }
            else
            {
                ET->next = temp;
            }
            ET = temp;
            ET->next = nullptr; // 这一步不能忘记，否则会形成环形
        }
        else
        {
            if (BH == nullptr)
            {
                BH = temp;
            }
            else
            {
                BT->next = temp;
            }
            BT = temp;
            BT->next = nullptr; // 这一步不能忘记，否则会形成环形
        }
        temp = next;
    }
    // 连接
    if (ST != nullptr)
    {
        // 小于区域不为空
        headNode->next = SH; //!!
        ST->next = (ET == nullptr) ? BH : EH;
        // TODO 后面的数：（BH:EH）还不能打括号,否则报错
    }
    if (EH != nullptr)
    {
        // 等于区域不为空
        ET->next = BH;
    }
    if (ST == nullptr)
    {
        headNode->next = (EH == nullptr) ? BH : EH;
    }
    printLinkedList(headNode);
}

// TODO5 复制含有随机指针节点的链表
template <typename T>
class RNode
{
public:
    RNode<T> *next = nullptr;
    RNode<T> *random = nullptr;
    T value = 0;
    RNode() {}
    RNode(T v) { this->value = v; }
};
// method01 哈希表克隆方法
template <typename T>
RNode<T> *copyRandomLinkedList01(RNode<T> *headNode)
{
    unordered_map<RNode<T> *, RNode<T> *> linked_map;
    RNode<T> *temp = headNode->next;
    RNode<T> *Rhead = new RNode<T>;
    RNode<T> *Rtemp;

    while (temp != nullptr)
    {
        Rtemp = new RNode<T>();
        Rtemp->value = temp->value;
        linked_map[temp] = Rtemp;
        // linked_map.insert({temp,Rtemp});
        temp = temp->next;
    }
    // 注意还有一个空值需要记录
    linked_map[nullptr] = nullptr;
    temp = headNode->next;
    while (temp != nullptr)
    {
        Rtemp = linked_map[temp];
        Rtemp->next = linked_map[temp->next];
        Rtemp->random = linked_map[temp->random];
        temp = temp->next;
    }
    Rhead->next = linked_map[headNode->next];
    return Rhead;
}
// method02 追加链表方法
template <typename T>
RNode<T> *copyRandomLinkedList02(RNode<T> *headNode)
{
    RNode<T> *temp = headNode->next;
    RNode<T> *Rhead = new RNode<T>;
    RNode<T> *Rtemp;
    // 追加连接
    while (temp != nullptr)
    {
        Rtemp = new RNode<T>();
        Rtemp->value = temp->value;
        Rtemp->next = temp->next;
        temp->next = Rtemp;
        temp = Rtemp->next;
    }
    // Random指针更新
    temp = headNode->next;
    while (temp != nullptr)
    {
        Rtemp = temp->next;
        Rtemp->random = temp->random->next;
        temp = temp->next->next;
    }
    //!!头指针指向
    Rhead->next = headNode->next->next;
    // 断开
    temp = headNode->next;
    while (temp != nullptr)
    {
        Rtemp = temp->next;
        temp->next = temp->next->next;
        temp = temp->next;
        Rtemp->next = (temp != nullptr) ? temp->next : nullptr;
    }
    return Rhead;
}
int main()
{
    srand(time(NULL));
    Node<int> *headNode = new Node<int>();
    Node<int> *headNode01 = new Node<int>();
    // vector<int> arr{1, 2, 2, 2, 2, 2, 1, 5};
    vector<int> arr01{1, 3, 3};
    // createLinkedList(arr, headNode);
    // createLinkedList(arr01, headNode01);
    // // printPublicArea(headNode,headNode01);
    // cout << isReversable01(headNode) << endl;
    // cout << isReversable02(headNode) << endl;
    // cout << isReversable03(headNode) << endl;
    // cout << isReversable01(headNode01) << endl;
    // cout << isReversable02(headNode01) << endl;
    // cout << isReversable03(headNode01) << endl;
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
    vector<int> arr;
    int maxLen = 100;
    int maxNum = 500;
    generatorVec(arr, maxLen, maxNum);
    createLinkedList(arr, headNode);
    classifyList01(headNode);
    createLinkedList(arr, headNode01);
    classifyList02(headNode01);

    // 随即链表实例
    RNode<int> *Rhead = new RNode<int>();
    RNode<int> *Rnode01 = new RNode<int>(1);
    RNode<int> *Rnode02 = new RNode<int>(2);
    RNode<int> *Rnode03 = new RNode<int>(3);
    RNode<int> *Rnode04 = new RNode<int>(4);
    Rhead->next = Rnode01;
    Rnode01->next = Rnode02;
    Rnode02->next = Rnode03;
    Rnode03->next = Rnode04;
    Rnode01->random = Rnode03;
    Rnode02->random = Rnode01;
    Rnode03->random = Rnode02;
    Rnode04->random = Rnode02;
    RNode<int> *copyHead = copyRandomLinkedList02(Rhead);
    // RNode<int> *copyHead = copyRandomLinkedList01(Rhead);

    RNode<int> *temp = Rhead->next;
    while (temp != nullptr)
    {
        cout << "value: " << temp->value << " ";
        if (temp->next != nullptr)
        {
            cout << "next: " << temp->next->value << " ";
        }
        if (temp->next != nullptr)
        {
            cout << "random: " << temp->random->value << " ";
        }
        temp = temp->next;
    }
    cout << endl;
    temp = copyHead->next;
    while (temp != nullptr)
    {
        cout << "value: " << temp->value << " ";
        if (temp->next != nullptr)
        {
            cout << "next: " << temp->next->value << " ";
        }
        if (temp->next != nullptr)
        {
            cout << "random: " << temp->random->value << " ";
        }
        temp = temp->next;
    }
    return 0;
}