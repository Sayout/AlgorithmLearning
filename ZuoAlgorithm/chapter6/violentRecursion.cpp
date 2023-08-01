#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>
#include <bitset>
using namespace std;
// TODO:N Queen
bool isValid(int rows, int cols, vector<int> paths)
{
    for (int i = 0; i <= rows - 1; i++)
    {
        // 注意，判断是否合法的时候，是对前面的几行进行检查，所以这里需要注意一下
        if ((paths[i] == cols) || (abs(i - rows) == abs(paths[i] - cols)))
        {
            return false;
        }
    }
    return true;
}
int getNQueenMethods(int rows, vector<int> paths, int N)
{
    if (N == 1)
    {
        return 1;
    }
    if (rows >= N)
    {
        return 1;
    }
    int methods = 0;
    for (int i = 0; i < paths.size(); i++)
    {
        if (rows == 0)
        {
            // rows才是行
            paths[rows] = i;
            methods += getNQueenMethods(rows + 1, paths, N);
            paths[rows] = -1;
            continue;
        }
        if (isValid(rows, i, paths))
        {
            paths[rows] = i;
            methods += getNQueenMethods(rows + 1, paths, N);
            paths[rows] = -1;
        }
    }
    return methods;
}
// TODO 使用位运算加速NQueen:判断是否合法的过程加速
// 只能解决32位的
int getNQueenMethodsQuick(int rows, int Standard, int colLim, int leftLim, int rightLim, int N)
{
    if (rows == N)
    {
        return 1;
    }
    cout << "row==" << rows << endl;
    int sumLim = colLim | leftLim | rightLim;
    std::bitset<10> m(colLim);
    std::cout << "colLim" << m << '\n';

    std::bitset<10> n(leftLim);
    std::cout << "leftLim" << n << '\n';

    std::bitset<10> p(rightLim);
    std::cout << "rightLim" << p << '\n';

    std::bitset<10> z(sumLim);
    std::cout << "sumLim" << z << '\n';
    if ((sumLim) == Standard)
    {
        return 0;
    }
    int methods = 0;
    while (sumLim != Standard)
    {
        std::bitset<10> h(sumLim);
        std::cout << "sumLim" << h << '\n';
        int temp = (~sumLim) & (Standard);

        std::bitset<10> x(temp);
        std::cout << "temp" << x << '\n';
        int rightOne = ((~temp) + 1) & temp;
        std::bitset<10> y(rightOne);
        std::cout << "rightOne" << y << '\n';
        // TODO:!!! 注意，左移的时候，不要让其大于Stardand
        methods += (getNQueenMethodsQuick(rows + 1, Standard, (colLim | rightOne), (((leftLim << 1) & Standard) | ((rightOne << 1) & Standard)), ((rightLim >> 1) | (rightOne >> 1)), N));
        sumLim = (sumLim | rightOne);
    }
    return methods;
}
int getNQueen(int N)
{
    if (N > 32)
    {
        return getNQueenMethods(0, vector<int>(N, -1), N);
    }
    else
    {
        int leftLim = 0;
        int rightLim = 0;
        int colLim = 0;
        int standard = (1 << (N)) - 1;
        return getNQueenMethodsQuick(0, standard, colLim, leftLim, rightLim, N);
    }
}
// hanoTower
void hanoToewr(char from, char to, char other, int n)
{
    // 搬动1-n：from->to
    if (n == 1)
    {
        cout << "move " << n << " " << from << " --> " << to << endl;
        return;
    }
    hanoToewr(from, other, to, n - 1);
    cout << "move " << n << " " << from << " --> " << to << endl;
    hanoToewr(other, to, from, n - 1);
}
// 打印字符串
// （1）打印一个字符串的全部子序列，包括空字符串
void printSubStr(int i, vector<char> preStr, vector<char> str)
{
    if (i == str.size())
    {
        for (int m = 0; m < preStr.size(); m++)
        {
            cout << preStr[m];
        }
        cout << endl;
        return;
    }
    printSubStr(i + 1, preStr, str);
    preStr.push_back(str[i]);
    printSubStr(i + 1, preStr, str);
}
// （2）打印一个字符串的全部排列
template <typename T>
void swap(vector<T> &str, int i, int j)
{
    T temp = str[i];
    str[i] = str[j];
    str[j] = temp;
}
// index 之前的位置已经排序完毕，index之后的位置需要进行排序
template <typename T>
void printCompeleteSort(int index, vector<T> preSort)
{
    // a,b,c,d,e,f
    if (index == preSort.size())
    {
        for (int i = 0; i < preSort.size(); i++)
        {
            cout << preSort[i];
        }
        cout << endl;
    }
    for (int i = index; i < preSort.size(); i++)
    {
        swap(preSort, index, i);
        printCompeleteSort(index + 1, preSort);
        swap(preSort, index, i);
    }
}
// 去重版全排列
// 每一个位置确定字母时，判断当前位置的字母是否有重复出现的
template <typename T>
void printCompeleteSortWithOutSame(int index, vector<T> preSort)
{
    // a,b,c,d,e,f
    if (index == preSort.size())
    {
        for (int i = 0; i < preSort.size(); i++)
        {
            cout << preSort[i];
        }
        cout << endl;
    }
    unordered_set<T> visit;
    for (int i = index; i < preSort.size(); i++)
    {
        if (visit.find(preSort[i]) == visit.end())
        {
            // 表明此位置的字母没有重复过
            swap(preSort, index, i);
            visit.insert(preSort[i]);
            printCompeleteSortWithOutSame(index + 1, preSort);
            // 真的无语了，忘记把这里改成WithoutSame
            swap(preSort, index, i);
        }
    }
}
// 逆序栈：不适用任何的额外空间
// f函数：移除栈底元素，并返回栈底
int f(stack<int> &sta)
{
    // 提前保证非空
    int temp = sta.top();
    sta.pop();
    if (sta.empty())
    {
        return temp;
    } // 栈底时，直接return，没有进行压栈
    int result = f(sta);
    sta.push(temp);
    return result;
}
void reverseStack(stack<int> &sta)
{
    // 第一个弹出来的数，第一个压进去
    // 保存top()，然后清空栈
    if (sta.empty())
    {
        return;
    }
    int temp = f(sta);
    reverseStack(sta);
    sta.push(temp);
}
//字符串组合
int strCombination(int index,vector<int>str){
    
    if(index==str.size()){
        return 1;
    }
    if(index>str.size()){
        return 0;
        //越界的情况，此时一定是组合导致的
    }
    if(str[index]==0){
        return 0;
    }
    int method=0;
    if(str[index]==1){
        //等于1的时候可以选择自己独立或者进行组合
        method=strCombination(index+1,str)+strCombination(index+2,str);
    }else if(str[index]==2&&(index+1<str.size())&&(str[index+1]<=6)){
        method=strCombination(index+1,str)+strCombination(index+2,str);
    }else{
      //另外的情况，只能自己组合
    method=strCombination(index+1,str);  
    }
    return method; 
}
// 当前遍历到index下标的项目，我可以选择装或者不装
int bagProblem(vector<int>weights,vector <int>values,int weightLim,int alreadyWeight,int index){
    int alreadyValue=0;
    if(index==weights.size()){
        //没有超重的情况下，走到这一步
        return 0;
    }
    
    //在后面提前判断是否超重
    // if(alreadyWeight>weightLim){
    //     return 0;
    // }
    int have=0;
    int n_have=0;
    if(alreadyWeight+weights[index]<=weightLim){
        have=bagProblem(weights,values,weightLim,alreadyWeight+weights[index],index+1)+values[index];
    }
    if(alreadyWeight<=weightLim){
        n_have=bagProblem(weights,values,weightLim,alreadyWeight,index+1);
    }
    return max(have,n_have);
}
//纸牌博弈问题
//先手函数
int bScore(vector<int>arr,int L,int R);
int fScore(vector<int>arr,int L,int R){
    int score=0;
    if(L==R){
        return arr[L];
    }
    score=max(arr[L]+bScore(arr,L+1,R),arr[R]+bScore(arr,L,R-1));
    return score;
}
//后手函数
int bScore(vector<int>arr,int L,int R){
    int score=0;
    if(L==R){
        return 0;
    }
    score=min(fScore(arr,L+1,R),fScore(arr,L,R-1));
    return score;
}
int main()
{
    int N = 8;
    // N=1,2,3,都是0种
    vector<int> paths(N, -1);
    // cout << N << " QueenMethods:" << getNQueen(N) << endl;
    // TODO：打印二进制形式数字的方法
    //  int a = 1;
    //  std::bitset<32> x(a);
    //  std::cout << x << '\n';
    hanoToewr('f', 't', 'o', 3);
    printSubStr(0, vector<char>{}, vector<char>{'a', 'b', 'c'});
    cout << endl;
    printCompeleteSort(0, vector<char>{'a', 'a', 'b', 'c'});
    cout << endl;
    printCompeleteSortWithOutSame(0, vector<char>{'a', 'a', 'b', 'c'});
    stack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    sta.push(4);
    sta.push(5);
    // cout<<"栈底: "<<f(sta)<<endl;;
    reverseStack(sta);
    while (!sta.empty())
    {
        cout << sta.top() << " ";
        sta.pop();
    }
    cout << endl;
    cout<<"组合的种类："<<strCombination(0,vector<int>{1,1,1,2,7})<<endl;
    // vector<int>weight{1,2,5,7,8,3,4,5};
    // vector<int>value{1,4,5,6,10,3,6,8};
    vector<int>weight{1,2,5,7,8,3,4,5};
    vector<int>value{1,2,5,7,8,3,4,5};
    int weightLim=15;
    cout<<"bagProblem: maxvalue "<<bagProblem(weight,value,weightLim,0,0)<<endl;;
    vector<int>card{1,100,4};
    int f=fScore(card,0,card.size()-1);
    int b=bScore(card,0,card.size()-1);
    cout<<"Winner Score: "<<max(f,b)<<endl;
    return 0;
}
