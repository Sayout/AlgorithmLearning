#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
// TODO01:一根长度为L的绳子，求绳子最多能覆盖其中的几个点
int getMaxCoverPoints(vector<int> points, int length)
{
    // 从当前节点出发，向后滑动L范围
    int L = 0;
    int maxNodes = 0;
    int R = L;
    for (int i = 0; i < points.size() - 1; i++)
    {
        int index = i;
        L = points[index];
        R = points[index + 1];
        int nodes = 1;
        while (R - L <= length)
        {
            nodes++;
            index++;
            if (index >= points.size())
            {
                break;
            }
            R = points[index + 1];
        }
        maxNodes = max(maxNodes, nodes);
    }
    cout << "max covered points: " << maxNodes << endl;
}

int main()
{
    vector<int> arr01{1, 4, 5, 8, 9, 10, 11, 24, 45, 67, 68, 69, 70, 71, 73, 74, 76};
    int L = 15;
    getMaxCoverPoints(arr01, L);
    
    return 0;
}