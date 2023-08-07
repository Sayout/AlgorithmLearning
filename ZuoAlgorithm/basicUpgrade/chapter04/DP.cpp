#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;
// TODO 机器人步行问题
// 找到机器人不行的方法数、
int getMethodsRobotGo(int N, int e, int K, int cur)
{
    if (K == 0)
    {
        return cur == e ? 1 : 0;
    }
    if (cur == N)
    {
        return getMethodsRobotGo(N, e, K - 1, N - 1);
    }
    if (cur == 1)
    {
        return getMethodsRobotGo(N, e, K - 1, 2);
    }
    return getMethodsRobotGo(N, e, K - 1, cur - 1) + getMethodsRobotGo(N, e, K - 1, cur + 1);
}

int getMethodsRobotGoMem(int N, int e, int K, int cur, vector<vector<int>> &dp)
{
    if (K == 0)
    {
        dp[K][cur] = cur == e ? 1 : 0;
        return dp[K][cur];
    }
    if (cur == N)
    {
        dp[K][cur] = getMethodsRobotGoMem(N, e, K - 1, N - 1, dp);
        return dp[K][cur];
    }
    if (cur == 1)
    {
        dp[K][cur] = getMethodsRobotGoMem(N, e, K - 1, 2, dp);
        return dp[K][cur];
    }
    dp[K][cur] = getMethodsRobotGoMem(N, e, K - 1, cur - 1, dp) + getMethodsRobotGoMem(N, e, K - 1, cur + 1, dp);
    return dp[K][cur];
}
int getMethodsRobotGoDP(int N, int e, int K_len, int s)
{
    vector<vector<int>> dp(K_len + 1, vector<int>(N + 1, -1)); // 初始化DP
    for (int cols = 0; cols < dp[0].size(); cols++)
    {
        dp[0][cols] = cols == e ? 1 : 0;
    }
    for (int K = 1; K <= K_len; K++)
    {
        for (int cur = 1; cur <= N; cur++)
        {
            if (cur == N) // 三种情况本来都是return 结尾，三种情况是互斥的
            {
                dp[K][cur] = dp[K - 1][N - 1];
            }
            else if (cur == 1)
            {
                dp[K][cur] = dp[K - 1][2];
            }
            else
            {
                dp[K][cur] = dp[K - 1][cur - 1] + dp[K - 1][cur + 1];
            }
        }
    }
    return dp[K_len][s];
}
// TODO换钱的最少货币数量:每张面值的货币可以有无数张
//  aim表示目标钱，coins面值货币数组，index货币种类下标，rest表示当前还需要配凑数目
int minCoinNumber(int aim, vector<int> coins, int index, int rest)
{
    if (rest < 0)
    {
        return -1; // 表示当前的方案不符合要求
    }
    if (rest == 0)
    {
        return 0; // 还需要当前货币0张
    }
    // rest>0的情况
    if (index == coins.size())
    {
        // 方案不成立
        return -1;
    }
    int number = 0;
    int minCoins = 999;
    while (number * coins[index] <= rest)
    {
        int curNum = minCoinNumber(aim, coins, index + 1, rest - number * coins[index]);
        if (curNum == -1)
        {
            number++;
            continue;
        }
        // number应该在判断之后加上去
        minCoins = curNum + number < minCoins ? curNum + number : minCoins;
        number++;
    }
    if (minCoins == 999)
    {
        return -1;
    }
    else
    {
        return minCoins;
    }
}
// index:0-coins.size()
// rest:0-aim;rest<0时，一律-1
// 全部初始化 -2
int minCoinNumberMem(int aim, vector<int> coins, int index, int rest, vector<vector<int>> dp)
{
    // TODO
    if (rest < 0)
    {
        return -1; // 表示当前的方案不符合要求
    }
    if (rest == 0)
    {
        dp[index][rest] = 0;
        return dp[index][rest]; // 还需要当前货币0张
    }
    // rest>0的情况
    if (index == coins.size())
    {
        // 方案不成立
        dp[index][rest] = -1;
        return dp[index][rest];
    }
    int number = 0;
    int minCoins = 999;
    while (number * coins[index] <= rest)
    {
        int curNum = minCoinNumberMem(aim, coins, index + 1, rest - number * coins[index], dp);
        dp[index][rest - number * coins[index]] = curNum;
        if (curNum == -1)
        {
            number++;
            continue;
        }
        // number应该在判断之后加上去
        minCoins = curNum + number < minCoins ? curNum + number : minCoins;
        number++;
    }
    if (minCoins == 999)
    {
        dp[index][rest] = -1;
        return dp[index][rest];
    }
    else
    {
        dp[index][rest] = minCoins;
        return dp[index][rest];
    }
}
// int minCoinNumberDP(int aim, vector<int> coins, int start_row, int start_cols)
// {
//     // TODO 由于rest小于0的情况是不合法的情况，除了一开始的数值就不合法以外，
//     // 其他这种情况在for(for（）)循环中通过条件语句判断了
//     if (start_cols < 0)
//     {
//         return -1; // 表示当前的方案不符合要求
//     }
//     vector<vector<int>> dp(coins.size() + 1, vector<int>(aim + 1, -2));

//     // rest>0的情况
//     for (int cols = 0; cols < dp[0].size(); cols++)
//     {
//         dp[coins.size()][cols] = -1;
//     }
//     for (int rows = 0; rows <= coins.size(); rows++)
//     {
//         dp[rows][0] = 0;
//     }

//     for (int index = dp.size() - 2; index >= 0; index--)
//     {
//         for (int rest = 1; rest < dp[0].size(); rest++)
//         {
//             //!!TODO:这里的枚举是否有必要？没有必要
//             // 反思：觉得这里不是很适合简化，因为每次都会产生一个number,最后还要类加上去
//             //  前提是不越界

//             int number = 0;
//             int minCoins = 999;
//             while (number * coins[index] <= rest)
//             {
//                 int curNum = dp[index + 1][rest - number * coins[index]];
//                 if (curNum == -1)
//                 {
//                      number++;
//                     continue;
//                 }
//                 // number应该在判断之后加上去
//                 minCoins = curNum + number < minCoins ? curNum + number : minCoins;
//                 number++;
//             }
//             if (minCoins == 999)
//             {
//                 dp[index][rest] = -1;
//             }
//             else
//             {
//                 dp[index][rest] = minCoins;
//             }
//         }
//     }
//     return dp[start_row][start_cols];
// }

int minCoinNumberDP(int aim, vector<int> coins, int start_row, int start_cols)
{
    // TODO 由于rest小于0的情况是不合法的情况，除了一开始的数值就不合法以外，
    // 其他这种情况在for(for（）)循环中通过条件语句判断了
    if (start_cols < 0)
    {
        return -1; // 表示当前的方案不符合要求
    }
    vector<vector<int>> dp(coins.size() + 1, vector<int>(aim + 1, -2));

    // rest>0的情况
    for (int cols = 0; cols < dp[0].size(); cols++)
    {
        dp[coins.size()][cols] = -1;
    }
    for (int rows = 0; rows <= coins.size(); rows++)
    {
        dp[rows][0] = 0;
    }

    for (int index = dp.size() - 2; index >= 0; index--)
    {
        for (int rest = 1; rest < dp[0].size(); rest++)
        {
            //!!TODO:这里的枚举是否有必要？没有必要
            // 反思：觉得这里不是很适合简化，因为每次都会产生一个number,最后还要类加上去
            //  前提是不越界

            int number = 0;
            int minCoins = 999;
            while (number * coins[index] <= rest)
            {
                int curNum = dp[index + 1][rest - number * coins[index]];
                if (curNum == -1)
                {
                    number++;
                    continue;
                }
                // number应该在判断之后加上去
                minCoins = curNum + number < minCoins ? curNum + number : minCoins;
                number++;
            }
            if (minCoins == 999)
            {
                dp[index][rest] = -1;
            }
            else
            {
                dp[index][rest] = minCoins;
            }
        }
    }
    return dp[start_row][start_cols];
}
// 如果是钱币问题，求一共的方法数
// index:0-coins.size() :coins.size() +1
// rest:0-aim :aim+1
int getCoinMethods(vector<int> coins, int index, int rest)
{
    if (rest < 0)
    {
        return 0;
    }
    if (rest == 0)
    {
        return 1;
    }
    // rest>0
    if (index == coins.size())
    {
        return 0;
    }
    int methods = 0;
    int number = 0;
    while (rest - number * coins[index] >= 0)
    {
        methods += getCoinMethods(coins, index + 1, rest - number * coins[index]);
        number++;
    }

    return methods;
}
int getCoinMethodsDP(vector<int> coins, int row, int aim)
{
    vector<vector<int>> dp(coins.size() + 1, vector<int>(aim + 1, 0));
    for (int j = 0; j < dp.size(); j++)
    {
        dp[coins.size()][j] = 0;
    }
    // 注意。这里是rest（cols）>0的情况
    for (int i = 0; i < dp.size(); i++)
    {
        dp[i][0] = 1;
    }
    for (int index = dp.size() - 2; index >= 0; index--)
    {
        for (int rest = 1; rest < dp[0].size(); rest++)
        {
            if (rest - coins[index] < 1)
            {
                int methods = 0;
                int number = 0;
                while (rest - number * coins[index] >= 0)
                {
                    methods += dp[index + 1][rest - number * coins[index]];
                    number++;
                }
                dp[index][rest]=methods;
            }else{
                 dp[index][rest]=dp[index][rest-coins[index]]+dp[index+1][rest];
            }
        }
    }
    return dp[row][aim];
}
// 纸牌游戏的DP
int b(vector<int> card, int L, int R);
int f(vector<int> card, int L, int R)
{
    if (L == R)
    {
        return card[L];
    }
    int maxScore = max(
        card[L] + b(card, L + 1, R),
        card[R] + b(card, L, R - 1));
    return maxScore; // 超，这里因为没有返回值导致我这里出错了
}
int b(vector<int> card, int L, int R)
{
    if (L == R)
    {
        return 0;
    }
    int minScore = min(
        f(card, L, R - 1),
        f(card, L + 1, R));
    return minScore;
}
int cardWinnerScore(vector<int> card, int L, int R)
{
    if (L <= R)
    {
        return max(f(card, L, R), b(card, L, R));
    }
    else
    {
        return -1;
    }
}
// left:左边界；
// right:右边界。。
// 当没有办法从逻辑中找到错误的时候，最好用断点调试一下
// 很可能是某个变量打错了
int cardWinnerScoreDP(vector<int> card, int left, int right)
{
    // dp
    // L:0-card.size()-1;
    // R:0-card。szie()-1

    int N = card.size();
    // 应该是几个函数就几张表
    vector<vector<int>> dpf(N, vector<int>(N, -1));
    vector<vector<int>> dpb(N, vector<int>(N, -1));
    for (int f = 0; f < dpf.size(); f++)
    {
        dpf[f][f] = card[f];
    }
    for (int b = 0; b < dpb.size(); b++)
    {
        dpb[b][b] = 0;
    }
    // L_end:N-2,,N-3,N-N
    for (int end = 0; end <= N - 2; end++)
    {
        for (int start = 0; start <= N - 2 - end; start++)
        {
            int L = start;
            int R = start + end + 1;
            int maxScore = max(
                card[L] + dpb[L + 1][R],
                card[R] + dpb[L][R - 1]);
            dpf[L][R] = maxScore;
            int minScore = min(
                dpf[L][R - 1],
                dpf[L + 1][R]);
            dpb[L][R] = minScore;
        }
    }
    return max(dpf[left][right], dpb[left][right]);
}
// TODO 马的走法
// cong (0,0)位置触发，走K步到达（x，y）的方法
// 可以反过来，cong (x,y)位置触发，走K步到达（0，0）的方法
// 象棋的限制：
const int X_lim = 10;
const int Y_lim = 9;
int methodsOfHorse(int x_step, int y_step, int k);
int getvalueOfHorseLimit(int x_step, int y_step, int k)
{
    if (x_step < 0 || x_step >= X_lim || y_step < 0 || y_step >= Y_lim)
    {
        return 0;
    }
    else
    {
        return methodsOfHorse(x_step, y_step, k);
    }
}
int methodsOfHorse(int x_step, int y_step, int k)
{
    if (k == 0)
    {
        return (x_step == 0 && y_step == 0) ? 1 : 0;
    }
    // 步数还没用完
    int methods = 0;
    methods = methods +
              getvalueOfHorseLimit(x_step - 1, y_step + 2, k - 1) +
              getvalueOfHorseLimit(x_step - 1, y_step - 2, k - 1) +
              getvalueOfHorseLimit(x_step + 1, y_step + 2, k - 1) +
              getvalueOfHorseLimit(x_step + 1, y_step - 2, k - 1) +
              getvalueOfHorseLimit(x_step - 2, y_step + 1, k - 1) +
              getvalueOfHorseLimit(x_step - 2, y_step - 1, k - 1) +
              getvalueOfHorseLimit(x_step + 2, y_step + 1, k - 1) +
              getvalueOfHorseLimit(x_step + 2, y_step - 1, k - 1);
    return methods;
}
int getvalueOfHorseLimitDP(int x_step, int y_step, int k, vector<vector<vector<int>>> dp)
{
    if (x_step < 0 || x_step >= X_lim || y_step < 0 || y_step >= Y_lim)
    {
        return 0;
    }
    else
    {
        return dp[k][x_step][y_step];
    }
}
int methodsOfHorseDP(int K, int X, int Y)
{
    // K:0-K :K+1
    // x_step: 0-9 :X_lim
    // y_step:0-8 :y_lim
    vector<vector<vector<int>>> dp(K + 1, vector<vector<int>>(X_lim, vector<int>(Y_lim, 0)));
    dp[0][0][0] = 1;
    for (int k = 1; k <= K; k++)
    {
        for (int x_step = 0; x_step < X_lim; x_step++)
        {
            for (int y_step = 0; y_step < Y_lim; y_step++)
            {
                int methods = 0;
                methods = methods +
                          getvalueOfHorseLimitDP(x_step - 1, y_step + 2, k - 1, dp) +
                          getvalueOfHorseLimitDP(x_step - 1, y_step - 2, k - 1, dp) +
                          getvalueOfHorseLimitDP(x_step + 1, y_step + 2, k - 1, dp) +
                          getvalueOfHorseLimitDP(x_step + 1, y_step - 2, k - 1, dp) +
                          getvalueOfHorseLimitDP(x_step - 2, y_step + 1, k - 1, dp) +
                          getvalueOfHorseLimitDP(x_step - 2, y_step - 1, k - 1, dp) +
                          getvalueOfHorseLimitDP(x_step + 2, y_step + 1, k - 1, dp) +
                          getvalueOfHorseLimitDP(x_step + 2, y_step - 1, k - 1, dp);
                dp[k][x_step][y_step] = methods;
            }
        }
    }
    return dp[K][X][Y];
}
// TODO Bob的生存概率
int bobLiveNumber(int M, int N, int m, int n, int K)
{
    if (m < 0 || m >= M || n < 0 || n >= N)
    {
        return 0;
    }
    if (K == 0)
    {
        return 1;
    }
    int liveNum = 0;
    liveNum = liveNum +
              bobLiveNumber(M, N, m + 1, n, K - 1) +
              bobLiveNumber(M, N, m - 1, n, K - 1) +
              bobLiveNumber(M, N, m, n + 1, K - 1) +
              bobLiveNumber(M, N, m, n - 1, K - 1);
    return liveNum;
}
int gcb(int a, int b)
{
    // 最大公约数
    int A = a;
    int B = b;
    a = max(A, B);
    b = A + B - a;

    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    cout << "公约数：" << a << endl;
    return a;
}
// start_m:0-M-1; M
// start_n:0-N-1; N
// K: 0-K K+1
int bobLiveNumberValue(int M, int N, int m, int n, int K, vector<vector<vector<int>>> dp)
{
    if (m < 0 || m >= M || n < 0 || n >= N)
    {
        return 0;
    }
    else
    {
        return dp[K][m][n];
    }
}
int bobLiveNumberDP(int M, int N, int start_m, int start_n, int K_step)
{
    vector<vector<vector<int>>> dp(K_step + 1, vector<vector<int>>(M, vector<int>(N, 0)));
    for (int m = 0; m < M; m++)
    {
        for (int n = 0; n < N; n++)
        {
            dp[0][m][n] = 1;
        }
    }
    for (int K = 1; K <= K_step; K++)
    {
        for (int m = 0; m < M; m++)
        {
            for (int n = 0; n < N; n++)
            {

                int liveNum = 0;
                liveNum = liveNum +
                          bobLiveNumberValue(M, N, m + 1, n, K - 1, dp) +
                          bobLiveNumberValue(M, N, m - 1, n, K - 1, dp) +
                          bobLiveNumberValue(M, N, m, n + 1, K - 1, dp) +
                          bobLiveNumberValue(M, N, m, n - 1, K - 1, dp);
                dp[K][m][n] = liveNum;
            }
        }
    }
    return dp[K_step][start_m][start_n];
}
void printBobLivePercetage(int M, int N, int m, int n, int K)
{
    int sumNum = pow(4, K);
    int liveNum = bobLiveNumber(M, N, m, n, K);
    int liveNumDP = bobLiveNumberDP(M, N, m, n, K);
    int gc = gcb(sumNum, liveNum);
    if (liveNum == 0)
    {
        cout << "0" << endl;
    }
    else
    {
        cout << "bob存活的方法：" << liveNum << endl;
        cout << "bob存活的方法：" << liveNumDP << endl;
        cout << liveNum / gc << "/" << sumNum / gc << endl;
    }
}
int main()
{
    int N = 5;
    int s = 2;
    int K = 4;
    int e = 4;

    int methodsRobot = getMethodsRobotGo(N, e, K, s);
    cout << "from " << s << " to " << e << " use " << K << " steps : " << methodsRobot << endl;
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, -1));
    methodsRobot = getMethodsRobotGoMem(N, e, K, s, dp);
    cout << "from " << s << " to " << e << " use " << K << " steps : " << methodsRobot << endl;
    methodsRobot = getMethodsRobotGoDP(N, e, K, s);
    cout << "from " << s << " to " << e << " use " << K << " steps : " << methodsRobot << endl;
    int aim = 45;
    vector<int> coins{5, 2, 3};
    int mCN = minCoinNumber(aim, coins, 0, aim);
    // index:0-coins.size()
    // rest:0-aim;rest<0时，一律-1
    // 全部初始化 -2
    cout << "minCoinNumber: " << mCN << endl;
    vector<vector<int>> dp01(coins.size() + 1, vector<int>(aim + 1, -2));
    mCN = minCoinNumberMem(aim, coins, 0, aim, dp01);
    cout << "minCoinNumber: " << mCN << endl;
    mCN = minCoinNumberDP(aim, coins, 0, aim);
    cout << "minCoinNumber: " << mCN << endl;
    vector<int> cards{2, 2, 100, 4};
    int L = 0;
    int R = cards.size() - 1;
    int winnerScore = cardWinnerScore(cards, L, R);
    cout << "winnerScore: " << winnerScore << endl;
    winnerScore = cardWinnerScoreDP(cards, L, R);
    cout << "winnerScore: " << winnerScore << endl;
    int x_start = 4;
    int y_start = 8;
    int k_step = 6;
    int HorseMethods = methodsOfHorse(x_start, y_start, k_step);
    cout << "HorseMethos: " << HorseMethods << endl;
    HorseMethods = methodsOfHorseDP(k_step, x_start, y_start);
    cout << "HorseMethos: " << HorseMethods << endl;

    // gcb(48,36);
    // gcb(48,20);
    // gcb(48,13);
    // gcb(116,24);
    int M = 4;
    int N_bob = 8;
    int m = 0;
    int n = 0;
    int K_bob = 6;
    printBobLivePercetage(M, N_bob, m, n, K_bob);
    int aims = 23;
    vector<int> coincoin{5, 2, 3};
    int gcM = getCoinMethods(coincoin, 0, aims);
    cout << "凑取钱币的方法：" << gcM << endl;
    gcM = getCoinMethodsDP(coincoin, 0, aims);
    cout << "凑取钱币的方法：" << gcM << endl;

    return 0;
}