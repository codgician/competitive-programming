#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 10
using namespace std;

int dp[SIZE][SIZE];
int cntArr[SIZE];

inline void init()
{
    for (int i = 1; i < 10; i++)
    {
        dp[0][i] = 1;
    }
    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            for (int k = 1; k <= j; k++)
            {
                if (j % k == 0)
                {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }
}

inline int work(int cnt)
{
    int len = 0;
    while (cnt)
    {
        cntArr[len++] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len] = 0;

    int ans = 0;
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            ans += dp[i][j];
        }
    }
    for (int j = 1; j < cntArr[len - 1]; j++)
    {
        ans += dp[len - 1][j];
    }

    for (int i = len - 2; i >= 0; i--)
    {
        for (int j = cntArr[i] - 1; j > 0; j--)
        {
            if (cntArr[i + 1] % j == 0)
            {
                ans += dp[i][j];
            }
        }
        if (cntArr[i] == 0 || cntArr[i + 1] < cntArr[i] || cntArr[i + 1] % cntArr[i] != 0)
            break;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        cout << work(rightPt + 1) - work(leftPt) << endl;
    }
    return 0;
}