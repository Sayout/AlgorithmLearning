// 几种排序方法
#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

template <typename T>
void swap(vector<T> &arr, int i, int j)
{
    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

template <typename T>
void printArr(vector<T> arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " " << endl;
    }
    cout << endl;
}
// 生成对数器
template <typename T>
vector<T> generateArr(int maxLength, int maxNumber)
{
    int len = (T)(rand() % (maxLength + 1));
    vector<T> arr;
    for (int i = 0; i < len; i++)
    {
        arr.push_back((T)(rand() % (maxNumber + 1)));
    }
    return arr;
}
template <typename T>
void printVector(vector<T> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << "  ";
    }
    cout << endl;
    cout << endl;
}
template <typename T>
bool isEqual(vector<T> v1, vector<T> v2)
{
    int len01 = v1.size();
    int len02 = v2.size();
    if (len01 != len02)
    {
        cout << "not the Same" << endl;
        return false;
    }
    else
    {
        for (int i = 0; i < len01; i++)
        {
            if (v1[i] != v2[i])
            {
                cout << "not the Same" << endl;
                return false;
            }
        }
        cout << "The Same arr" << endl;
        return true;
    }
}
template <typename T>
vector<T> arrTovec(T arr[], int len)
{
    vector<T> vec(len, 0);
    for (int i = 0; i < len; i++)
    {
        vec[i] = arr[i];
    }
    return vec;
}
// 选择排序:注意，交换的时候记录的是下标，所以设置的初始变量也是下标
template <typename T>
void selectSort(vector<T> &arr, int len)
{
    int index;
    for (int i = 0; i < len; i++)
    {
        index = i; // 从i开始
        for (int j = i; j < len; j++)
        {
            index = arr[j] < arr[index] ? j : index;
        }
        swap(arr, i, index);
    }
}
// 冒泡排序
template <typename T>
void bubbleSort(vector<T> &arr, int len)
{
    for (int i = len - 2; i >= 1; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            if (arr[j + 1] < arr[j])
            {
                swap(arr, j, j + 1);
            }
        }
    }
}
// 插入排序
template <typename T>
void insertSort(vector<T> &arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr, j, j - 1);
            }
        }
    }
}
template <typename T>
void copyVector(vector<T> &vector01, vector<T> vector02)
{
    if (vector01.size() == 0)
    {
        vector01 = vector02;
    }
    else
    {
        vector01.swap(vector02);
        // swap会清空原来的vector02
    }
}
template <typename T>
void merge(vector<T> &arr, int s, int e, int m)
{
    // 左边有序，右边有序，merge
    int p1 = s;
    int p2 = m + 1;
    int p0 = 0;
    vector<T> tempArr(e - s + 1, 0);

    while (p1 <= m && p2 <= e) // not overbounded
    {
        tempArr[p0++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= m)
    {
        tempArr[p0++] = arr[p1++];
    }
    while (p2 <= e)
    {
        tempArr[p0++] = arr[p2++];
    }
    // copyVector(arr, tempArr);
    // TODO ! 这里每次copy就把原来的数组截断了,所以不能用Copy
    p0 = 0;
    while (s <= e)
    {
        arr[s++] = tempArr[p0++];
    }
}
// 归并排序：Master公式--O(NlogN)
template <typename T>
void mergeSort(vector<T> &arr, int s, int e)
{
    if (s >= e)
    {
        return;
    }
    else
    {
        int m = s + ((e - s) >> 1);
        // 注意在进行求中间值的时候，该用括号括起来的用括号
        mergeSort(arr, s, m);
        mergeSort(arr, m + 1, e);
        merge(arr, s, e, m);
    }
}
// TODO 归并排序的推展问题：小和问题
template <typename T>
int mergeSum(vector<T> &arr, int s, int e, int m)
{
    int p1 = s;
    int p2 = m + 1;
    int p0 = 0;
    int minSum = 0;
    vector<T> tempArr(e - s + 1, 0);
    while (p1 <= m && p2 <= e)
    {
        minSum = arr[p1] < arr[p2] ? (e - p2 + 1) * arr[p1] + minSum : 0 + minSum;
        tempArr[p0++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
        // merge过程产生小和,当两边相等时，一定是先拷贝右边的小和
    }
    while (p1 <= m)
    {
        tempArr[p0++] = arr[p1++];
    }
    while (p2 <= e)
    {
        tempArr[p0++] = arr[p2++];
    }
    // 记得拷贝
    p0 = 0;
    while (s <= e)
    {
        arr[s++] = tempArr[p0++];
    }
    return minSum;
}

template <typename T>
int getMinSum(vector<T> &arr, int s, int e)
{
    if (s >= e)
    {
        return 0;
    }
    else
    {
        // 左边小和+右边小和+归并产生的小和
        int m = s + ((e - s) >> 1);
        return getMinSum(arr, s, m) + getMinSum(arr, m + 1, e) + mergeSum(arr, s, e, m);
    }
}

// TODO 归并排序的推展问题：逆序对问题

// TODO 堆排序问题
template <typename T>
void heapInsert(vector<T> &arr, int &heapSize)
{
    // insert时检查是否比父亲大，大的时候需要进行swap
    int index = heapSize;

    while (arr[(index - 1) / 2] < arr[index]) // 这里的判断包含越界的情况
    {
        swap(arr, (index - 1) / 2, index);
        index = (index - 1) / 2;
    }
    heapSize++;
}
/// @brief
/// @tparam T
/// @param arr
/// @param heapSize 当前堆的大小
/// @param heapifyIndex 表示从哪个地方做heapify
template <typename T>
void heapify(vector<T> &arr, int heapSize, int heapifyIndex)
{
    int index = heapifyIndex;
    while (index * 2 + 1 < heapSize)
    {
        // 当有字节点时，才需要进行调整
        int left = index * 2 + 1;
        int right = left + 1;
        int maxSonIndex = left;
        if ((right < heapSize) && (arr[right] > arr[left]))
        {
            maxSonIndex = right; // 比较子节点
        }
        if (arr[maxSonIndex] < arr[index])
        {
            maxSonIndex = index; // 比较子节点最大和父节点
        }
        if (maxSonIndex == index)
        {
            break; // 不再需要进行比较
        }
        else
        {
            swap(arr, index, maxSonIndex);
            // 进行交换
            index = maxSonIndex;
        }
    }
}
template <typename T>
void heapSort(vector<T> &arr)
{
    /*
    1.调整大根堆：两种方案NlgN VS N
    2.大根堆的最大和heapSize-1位置进行交换
    3.heapify
    */
    // meathod 01 :NlgN
    /*int heapSize=0;
    for(int i=0;i<arr.size();i++){
     heapInsert(arr,heapSize);
    }*/
    int heapSize = arr.size();
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        heapify(arr, heapSize, i);
        // 从下面开始进行调整
    }
    //    cout<<"调整大根堆后的vector:"<<endl;
    //    printVector(arr);
    swap(arr, 0, --heapSize);
    // NlgN
    while (heapSize > 0)
    {
        // 一直heapify到index=0;
        heapify(arr, heapSize, 0);
        swap(arr, 0, --heapSize);
    }
    // printVector(arr);
}

// TODO堆结构的使用
// TODO 优先级队列-->系统堆
// 基本有序问题的求解
template <typename T>
void nearlySort(vector<T> &arr, int k)
{
    // 依次将前K个数进小根堆
    priority_queue<int, vector<int>, greater<T>> que;
    vector<int> tempArr;
    // 优先级队列默认是大根堆，参数less<T>;小根堆参数是greater<T>
    int i = 0;
    int min = (arr.size() - 1) < k ? (arr.size() - 1) : k;
    for (; i <= min; i++)
    {
        que.push(arr[i]);
    }
    int index = 0;
    while (que.size() != 0)
    {
        tempArr.push_back(que.top());
        que.pop();
        if (i < arr.size())
        {
            que.push(arr[i++]);
        }
    }
    arr.swap(tempArr);
}
// TODO 随机 快速排序
template <typename T>
pair<int, int> partition(vector<T> &arr, int s, int e)
{
    int randIndex = s + (rand() % (e - s + 1));
    swap(arr, e, randIndex); // 随机选择一个数，放在队尾，用来进行划分
    int lessBound = s - 1;
    int moreBound = e + 1;
    // 找到等于小于和大于区域的上下边界
    int pointer = s;
    int tempNumber = arr[e];
    while (pointer < moreBound)
    {
        if (arr[pointer] < tempNumber && moreBound > lessBound)
        {
            // 和上边界的下一个交换
            swap(arr, pointer, lessBound + 1);
            lessBound++;
            pointer++;
        }
        else if (arr[pointer] == tempNumber)
        {
            pointer++;
        }
        else
        {
            swap(arr, pointer, moreBound - 1);
            moreBound--; // pointer不能自增，因为此时还没有进行比较
        }
    }
    return make_pair(lessBound, moreBound);
}
template <typename T>
void quickSort(vector<T> &arr, int s, int e)
{
    if (s < e)
    {
        pair<int, int> bound = partition(arr, s, e);
        int lessBound = bound.first;
        int moreBound = bound.second;
        quickSort(arr, s, lessBound);
        quickSort(arr, moreBound, e);
        // 分别对大于区小于区域进行partition划分
    }
}

int main()
{
    srand(time(NULL));
    // 设定随机数种子
    // int arr[12] = {1, 5, 35, 71, 34, 56, 24, 13, 8, 13, 16, 13};
    int arr_len = 12;

    // printArr(arr,arr_len);
    // selectSort(arr,arr_len);
    // bubbleSort(arr,arr_len);
    // insertSort(arr,arr_len);
    // printArr(arr,arr_len);
    int maxLen = 500;
    int maxNumber = 500;
    int testTime = 50;
    for (int i = 0; i < testTime; i++)
    {
        vector<int> arr01 = generateArr<int>(maxLen, maxNumber);
        vector<int> arr02 = arr01; // 直接复制就好了
        // printVector(arr01);
        // insertSort(arr01, arr01.size());
        // printVector(arr01);
        // cout<<endl;
        // bubbleSort(arr02,arr02.size());
        // printVector(arr02);
        // mergeSort(arr02, 0, arr02.size() - 1);
        heapSort(arr01);
        quickSort(arr02, 0, arr02.size() - 1);
        // cout<<endl;
        // printVector(arr02);
        // cout<<endl;
        isEqual(arr01, arr02);
        cout << endl;
    }

    /*
      vector<int> arr = generateArr<int>(20, maxNumber);
        printVector(arr);
        int minSum=getMinSum(arr,0,arr.size()-1);
        printVector(arr);
        cout<<"minSum为："<<minSum<<endl;
    */
    // vector<int> arr = generateArr<int>(35, maxNumber);
    // cout<<"初始数组为："<<endl;
    // printVector(arr);
    // heapSort(arr);
    vector<int> nearSort;
    nearSort.push_back(2);
    nearSort.push_back(4);
    nearSort.push_back(8);
    nearSort.push_back(0);
    nearSort.push_back(9);
    nearSort.push_back(5);
    nearSort.push_back(7);
    nearSort.push_back(7);
    nearlySort(nearSort, 3);
    printVector(nearSort);
    return 0;
}