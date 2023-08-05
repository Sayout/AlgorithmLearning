#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;
int getReverse(int a)
{
    // 0变1，1变0
    return 1 ^ a;
    // 注意0变1，1变0应该是与1异或而不是~
}
int getMaxBit(int a, int b)
{
    // 需要判断是否会越界
    int signA = (unsigned int)a >> 31;
    int signB = (unsigned int)b >> 31;
    int c = (unsigned int)(a - b) >> 31;
    // cout<< "c "<<c<<endl;
    // 同号不会越界
    int noSameSign = signA ^ signB;
    int isSameSign = 1 ^ noSameSign;
    // cout<<"noSameSign "<<noSameSign<<endl;
    int returnA = (isSameSign & (getReverse(c))) | (noSameSign & (getReverse(signA)));
    int returnB = getReverse(returnA);
    return returnA * a + returnB * b;
}
bool isTwoPower(int number)
{
    // 要求只有一个1
    int rightOne = number & (~number + 1);
    return ((rightOne | number) == rightOne);
}
bool isFourPower(int number)
{
    if (isTwoPower(number))
    {
        int temp = number & (0x55555555);
        return temp != 0;
        // 只有一个1且1只在偶数位上
    }
    else
    {
        return false;
    }
}
int addBit(int a, int b)
{
    // 无进位相加的结果加进位信息
    int result = a;
    // cout << a << " + " << b << " = ";
    while (b != 0)
    {
        result = a ^ b;
        b = (a & b) << 1;
        a = result;
    }
    // cout << result << endl;
    return result;
}
int subBit(int a, int b)
{
    // cout << a << " - " << b << " = ";
    b = (~b + 1);
    int result = addBit(a, b);
    // cout << result << endl;
    return result;
}
void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

int multipleBit(int a, int b)
{
    cout << a << " * " << b << " = ";
    int signA = a >> 31;
    int signB = b >> 31;
    int sign = signA ^ signB;
    if (sign == 0)
    {
        // tonghao
        if (signA)
        {
            // 都是负数
            a = ~a + 1;
            b = ~b + 1;
        }
    }
    else
    {
        // 负号放在前面
        // 正数放在后面
        if (signB)
        {
            swap(a, b);
        }
    }
    // 后面的算法适用于B>=0的情况
    int B = b;
    // int A=a;
    int result = 0;
    while (B != 0)
    {
        // std::bitset<20> x(B);
        // std::cout << x << '\n';
        int rightOne = (addBit(~(B), 1)) & B;
        int move = 0;
        while (rightOne != 1)
        {
            move = addBit(move, 1);
            rightOne = rightOne >> 1;
        }
        result = addBit(result, (a << move));
        // 由于rightOne在求move的时候已经被破坏，所以需要重新求解
        rightOne = (addBit(~(B), 1)) & B;
        B = (~rightOne) & (B);
    }
    cout << result << endl;
    return result;
}
int divBit(int a, int b)
{
    // 因为这里是a右移，所以，当符号相异的时候，将b化成负号
    cout << a << " / " << b << " = ";
    int signA = a >> 31;
    int signB = b >> 31;
    int sign = signA ^ signB;
    // 无论是同号还是异号，A都不能是负数都需要取反
    if (signA)
    {
        // 都是负数
        a = addBit(~a, 1);
    }
    if (signB)
    {
        b = addBit(~b, 1);
    }

    int result = 0;
    int A = a;
    while (A != 0)
    {
        int temp = A;
        int mov = 0;
        while ((A >> 1) > b)
        {
            A = A >> 1;
            mov = addBit(mov, 1);
        }
        result = addBit(result, (1 << mov));
        A = subBit(temp, (b << mov));
        temp = A;
    }
    if (sign)
    {
        result = addBit(~result, 1);
    }
    cout << result << endl;
    return result;
}
int main()
{
    cout << getMaxBit(1, 2) << endl;
    cout << getMaxBit(-1, 2) << endl;
    cout << getMaxBit(-1, -2) << endl;
    // cout<<((unsigned int)-1>>31)<<endl;
    cout << isTwoPower(2) << endl;
    cout << isTwoPower(6) << endl;
    cout << isFourPower(2) << endl;
    cout << isFourPower(4) << endl;
    cout << isFourPower(6) << endl;

    addBit(1, 2);
    addBit(-1, -2);
    addBit(-1, 2);
    subBit(1, 2);
    subBit(-1, -2);
    subBit(-1, 2);

    multipleBit(6, 5);
    multipleBit(-6, 5);
    multipleBit(-6, -5);
    divBit(30, -5);
    divBit(-30, -5);
    divBit(-30, 5);
    return 0;
}