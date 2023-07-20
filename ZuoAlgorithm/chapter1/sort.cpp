// 几种排序方法
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
template <typename T>
void swap(vector<T> &arr, int i, int j)
{
    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
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
    //! TODO ! 这里每次copy就把原来的数组截断了,所以不能用Copy  
    p0=0;          
    while(s<=e){
        arr[s++]=tempArr[p0++];
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
        //注意在进行求中间值的时候，该用括号括起来的用括号
        mergeSort(arr, s, m);
        mergeSort(arr, m + 1, e);
        merge(arr, s, e, m);
    }
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
        cout<<"not the Same"<<endl;
        return false;
    }
    else
    {
        for (int i = 0; i < len01; i++)
        {
            if (v1[i] != v2[i])
            {   
                cout<<"not the Same"<<endl;
                return false;
            }
        }
        cout<<"The Same arr"<<endl;
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

int main()
{
    srand(time(NULL));
    // 设定随机数种子
    int arr[12] = {1, 5, 35, 71, 34, 56, 24, 13, 8, 13, 16, 13};
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
        insertSort(arr01, arr01.size());
        // printVector(arr01);
        // cout<<endl;
        // bubbleSort(arr02,arr02.size());
        // printVector(arr02);
        mergeSort(arr02, 0, arr02.size() - 1);
        // cout<<endl;
        // printVector(arr02);
        // cout<<endl;
        isEqual(arr01, arr02);
        cout<<endl;
    }

    return 0;
}