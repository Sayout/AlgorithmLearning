#include <iostream>
#include <vector>
using namespace std;
void printMulTab()
{
    int n;
    cin >> n;
    // 选择乘法表的维度
    vector<vector<int>> mulTab;
    for (int i = 0; i < n; i++)
    {
        // 创建空的二维动态数组
        mulTab.push_back(vector<int>());
    }
    for (int i = 0; i < mulTab.size(); i++)
    {
        for (int j = 0; j <= i; j++)
        {
            mulTab.push_back((i + 1) * (j + 1));
        }
    }
    for (int i = 0; i < mulTab.size(); i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << i + 1 << " * " << j + 1 << " = " << mulTab[i][j] << "\t";
        }
        cout << endl;
    }
}
int main()
{
    printMulTab();

    return 0;
}