// 打表
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

// TODO02 只提供6个每袋和8个
pair<int, int> getMinBags(int N)
{
    if (N < 6)
    {
        return make_pair<int, int>(-1, -1);
    }
    // if((N>6)&&(N<8)){
    //     return make_pair<int,int>(-1,-1);
    // }
    if (N > 8 && N < 14)
    {
        return make_pair<int, int>(-1, -1);
    }
    int origiEight = N / 8;
    int extraApple = N % 8;
    int sixBag = 0;
    if (extraApple != 0)
    {
        if (extraApple % 2 != 0)
        {
            return make_pair<int, int>(-1, -1);
        }
        else
        {
            int buchang = (6 - extraApple) / 2;
            origiEight = origiEight - buchang;
            sixBag = 1 + buchang;
        }
    }
    return pair<int, int>(origiEight, sixBag);
}
// TODO LC2244
class Solution01
{
public:
    int minimumRounds(vector<int> &tasks)
    {
        unordered_map<int, int> tsk_num;
        for (int i = 0; i < tasks.size(); i++)
        {
            if (tsk_num.find(tasks[i]) == tsk_num.end())
            {
                tsk_num[tasks[i]] = 1;
            }
            else
            {
                tsk_num[tasks[i]]++;
            }
        }
        int number_t = 0;
        int canDo = true;
        for (auto it = tsk_num.begin(); it != tsk_num.end(); it++)
        {
            int n = getMinItrators(it->second);
            if (n == -1)
            {
                canDo = false;
                break;
            }
            else
            {
                number_t = number_t + n;
            }
        }
        if (canDo == true)
        {
            return number_t;
        }
        else
        {
            return -1;
        }
    }
    // 对于每个任务返回最少的轮数
    int getMinItrators(int number)
    {
        // 2,3
        if (number < 2)
        {
            return -1;
        }
        // if(number>3&&number<5){
        //     return -1;
        // }
        int originTree = number / 3;
        int extraTask = number % 3;
        int twotask = 0;
        if (extraTask != 0)
        {
            int buchang = 2 - extraTask;
            originTree = originTree - buchang;
            twotask = 1 + buchang;
        }
        return originTree + twotask;
    }
};
// TODO :动物吃草 打表法
//先手后手绝顶聪明，最后谁赢？
//先手返回0，后手返回1
int grazeWinner(int grass){
 //0     1   2   3   4   5   6   7    8   9   10
 //后    先  后  先  先   后  先  后   
 if(grass>=0&&grass<5){
    if(grass==0||grass==2){
        return 1;
    }else{
        return 0;
    }
    }
    //先手clever,先手会选择自己胜利的情况
    //先手choose grass:1,4,16...
    int beforeEat=1;
    while(grass-beforeEat>0){
        //后手调用，1表示后手的后手，也就是先手
        if(grazeWinner(grass-beforeEat)==1){
            return 0;//找到一种情况就可以返回
        }
        //防止溢出
        if(beforeEat>(grass/4)){
            //!!TODO 提前break,防止溢出
            break;
        }
        beforeEat=beforeEat*4;
    }
    //没有返回，说明没找到自己胜利的情况
    return 1;
 }
// 10100
int grazeWinnerTT(int grass){
    int yushu=grass%5;
    if(yushu==0||yushu==2){
        return 1;
    }else{
        return 0;
    }
}
//LeetCode 292 Nim
class Solution {
public:
    // bool canWinNim(int n) {
    //     // 1 2 3 4 5 6
    //     // w w w t w 
    //     if(n>=1&&n<=5){
    //         if(n==4){
    //             return false;
    //         }else{
    //             return true;
    //         }
    //     }
    //     int number =1;
    //     while(n-number>=0&& number<4){
    //         if(canWinNim(n-number)==false){
    //             return true;
    //         }
    //         number++;
    //     }
    //     return false;
    // }
        bool canWinNim(int n) {
        // 1 2 3 4 | 5 6
        // 1 1 1 0 | 1 1
        if((n)%4+1==4){
            return false;
        }else{
            return true;
        }
    }
};
int main()
{

    pair<int, int> bags = getMinBags(14);
    cout << bags.first << "," << bags.second << endl;

    Solution01 *s = new Solution01();
    vector<int> task{4, 4, 4, 4};
    // int numDo = s->minimumRounds(task);
    // cout << "numDO: " << numDo << endl<< endl;

    Solution *s1 = new Solution();
    // Graze 打表
    for(int i=0;i<4*4*4;i++){
        cout<<s1->canWinNim(i)<<endl;
    }
    return 0;
}