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
        //TODO:!!! 注意，左移的时候，不要让其大于Stardand
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

int main()
{
    int N = 8;
    // N=1,2,3,都是0种
    vector<int> paths(N, -1);
    cout << N << " QueenMethods:" << getNQueen(N) << endl;
    // TODO：打印二进制形式数字的方法
    //  int a = 1;
    //  std::bitset<32> x(a);
    //  std::cout << x << '\n';
    return 0;
}
