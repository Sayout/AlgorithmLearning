// 二分查找使用与很多问题
/*
1,有序数组二分查找
2,有序数组>=某个数最左侧位置
3,局部最小值问题
*/
#include <iostream>
using namespace std;
// 二分查找
int binarySearch(int arr[], int s, int e, int number)
{
    if (s > e)
    {
        cout << "not exist number: " << number << endl;
        return -1;
    }
    int m = s +( (e - s) >>1);
    if (arr[m] == number)
    {
        cout << "the index of 'm' is " << m << endl;
        return m;
    }
    else if (arr[m] < number)
    {
        return binarySearch(arr, m + 1,e , number);
    }
    else
    {
        return binarySearch(arr, s, m-1, number);
    }
}
//找>=的最左边
int binaryLessRight(int arr[], int s, int e, int number,int record)
{
    if (s > e)
    {
        return record;
    }
    int m = s + ((e - s) >>1);
    if (arr[m] >= number)//往左边找
    {   
        record=m;
        return binaryLessRight(arr, s, m-1, number,record);
    }
    else 
    {
        return binaryLessRight(arr, m + 1,e , number,record);
    }
}
//record 初始值为-1
void lessRight(int arr[], int s, int e, int number,int record){
    int index= binaryLessRight(arr,s,e,number,record);
    if(index==-1){
        cout<<"not exist!!"<<endl;
    }else{
        cout<<"index :"<<index<<endl;
    }
}
//求局部最小值:没有重复值
int areaMinBinary(int arr[],int s,int e){
    // 1.判断两端
    if(s<e){
       int m=s+((e-s)>>1); 
       if(arr[m]>arr[m+1]){
        return areaMinBinary(arr,m,e);
       }
       if(arr[m-1]<arr[m]){
        return areaMinBinary(arr,s,m);
        }
        return m;
    }
    else{
        return -1;
    }
}
int areaMin(int arr[],int s,int e){
    // 1.判断两端
    int index;
    if(s<e){
        if(arr[s]<arr[s+1]){
            index=s;
            cout<<"局部最小值的index为："<<index<<endl;
            return s;
        }
        if(arr[e-1]>arr[e]){
            index=e;
            cout<<"局部最小值的index为："<<index<<endl;
            return e;
        }
        // 判断medium
        index =areaMinBinary(arr,s,e);
        cout<<"局部最小值的index为："<<index<<endl;
        return index;
    }else{
        cout<<"没有局部最小值"<<endl;//一般只有一个数值的情况
        return -1;
        //没有局部最小值，返回index=-1
    }
}
int main()
{
    int arr[15]={1,4,6,7,9,10,12,15,17,18,25,25,46,47,87};
    int arr_len=15;
    // binarySearch(arr,0,arr_len-1,1);
//    lessRight(arr,0,arr_len-1,87,-1);
//    lessRight(arr,0,arr_len-1,1,-1);
//    lessRight(arr,0,arr_len-1,25,-1);
    int arr_01[10]={0,1,2,3,4,5,6,7,8,9};
    int arr_02[10]={1,0,2,3,4,6,7,8,9,10};
    int arr_03[10]={8,7,6,4,5,6,7,8,9,10};
    int arr_04[1]={8};
    areaMin(arr_01,0,9);
    areaMin(arr_02,0,9);
    areaMin(arr_03,0,9);
    areaMin(arr_04,0,0);
    return 0;
}