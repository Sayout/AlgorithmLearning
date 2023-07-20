/*
 * @Author: Sayout 2052707592@qq.com
 * @Date: 2023-07-17 08:47:13
 * @LastEditors: Sayout 2052707592@qq.com
 * @LastEditTime: 2023-07-17 16:31:21
 * @FilePath: \C++\first.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <cmath>
using namespace std;

void getResolution()
{
    // 计算一元二次方程的根
    float a, b, c, x1, x2, discrimination, realPart, imaginaryPart;
    cout << "Please input a,b,c," << endl;
    cin >> a >> b >> c;
    discrimination = b * b - 4 * a * c;
    if (discrimination == 0)
    {
        x1 = -b / (2 * a);
        cout << "unique resolution: x= " << x1 << endl;
    }
    else if (discrimination > 0)
    {
        x1 = (-b + sqrt(discrimination)) / (2 * a);
        x2 = (-b - sqrt(discrimination)) / (2 * a);
        cout << "two real resolution: x1= " << x1 << " ,x2= " << x2 << endl;
    }
    else
    {
        realPart = -b / (2 * a);
        imaginaryPart = sqrt(-discrimination) / (2 * a);

        cout << "two image resolution: x1= " << realPart << "-i*" << imaginaryPart << " ,x2= " << realPart << "+i*" << imaginaryPart << endl;
    }
}
void isRunYear()
{
    cout << "Please enter a year" << endl;
    int year;
    cin >> year;
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                cout << year << "是闰年" << endl;
            }
            else
            {
                cout << year << "不是闰年" << endl;
            }
        }
        else
        {
            cout << year << "是闰年" << endl;
        }
    }
    else
    {
        cout << year << "不是闰年" << endl;
    }
}
void drawTriangle()
{
    // 杨辉三角的绘制
    int arr[6][13];
    // 初始化全部为 0,注意左右都多增加一列
    // 注意cpp中需要对数组手动初始化
    for (int n = 0; n < 6; n++)
    {
        arr[n][0] = 0;
        arr[n][12] = 0;
    }
    for (int m = 1; m < 12; m++)
    {
        arr[0][m] = 0;
    }
    arr[0][6] = 1;
    for (int m = 1; m < 12; m++)
    {
        if (m != 6)
        {
            cout << "  ";
        }
        else
        {
            printf("%d", arr[0][m]);
        }
    }
    cout << endl;
    for (int i = 1; i < 6; i++)
    {
        for (int j = 1; j < 12; j++)
        {
            // 对周边的1赋值
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j + 1];
            if (arr[i][j] != 0)
            {
                // cout<<arr[i][j];
                printf("%2d", arr[i][j]);
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}
void getMax()
{
    // 求最大公约数:不断大数-小数，知道两者相等
    cout << "please enter two number" << endl;
    int a, b;
    cin >> a >> b;
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    cout << a << endl;
}
void getMin()
{
    // 求最小公倍数
    cout << "PLease enter two numbers" << endl;
    int a, b;
    cin >> a >> b;
    int maxNumber = a > b ? a : b;
    while (true)
    {
        if (maxNumber % a == 0 && maxNumber % b == 0)
        {
            cout << maxNumber << endl;
            break;
        }
        else
        {
            maxNumber++;
        }
    }
}
int main()
{
    // getMax();
    // isRunYear();
    // getResolution();
    // drawTriangle();
    getMin();
    return 0;
}