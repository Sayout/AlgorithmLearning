// 异或问题
/*
1.无额外空间交换临时变量
2.一个数组中有一种数出现了奇数次，其他数都出现了偶数次，怎么找到这一个数
    所有数进行异或，最后得到的数，就是出现奇数次的数
3.一个数组中有两种数出现了奇数次，其他数都出现了偶数次，怎么找到这两个数

*/
#include<iostream>
using namespace std;
int getUniqueOdd(int arr[], int len)
//我测，java写多了，数组的中括号要写在后面
{
    // 1,2,2,3,3,3,4,4,1
    // 相等的数异或为0，0和任何数异或结果为任何数字
    int unique = 0;
    for (int i = 0; i < len; i++)
    {
        unique = unique ^ arr[i];
    }
    cout << "Number occurred odd times: " << unique << endl;
    return unique;
}
void getDoubleOdd(int arr[],int len)
{
    //当数组中有两个出现次数为奇数次的数字
     int unique = 0;
    for (int i = 0; i < len; i++)
    {
        unique = unique ^ arr[i];
    }
    //unique=a^b,既然两个数一定不一样，异或后的结果中一定有1
    int rightOne=unique&(~unique+1);
    int a=0;
    int b=0;
    for(int i=0;i<len;i++){
        if(arr[i]&rightOne!=0){
            a=a^arr[i];
        }
    }
    b=a^unique;
    cout<<"two Numbers occurred odd times: a= "<<a<<" b= "<<b<<endl;;
}
int main()
{
    int arr[11]={1,2,2,3,3,3,4,4,1,1,1};
    int uniqueOdd=getUniqueOdd(arr,11);
    int arr01[12]={1,2,2,3,3,3,4,4,4,1,1,1};
    getDoubleOdd(arr01,12);
    return 0;
}