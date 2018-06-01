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

long long int dp[SIZE][SIZE];
int cntArr[SIZE];

inline void init()
{
    dp[0][0] = 1;
    for (int i = 1; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            dp[i][j] = 0;
            if (j == 4)
                continue;
            for (int k = 0; k < 10; k++)
            {
                if (k == 4 || (j == 6 && k == 2))
                    continue;
                dp[i][j] += dp[i - 1][k];
            }
        }
    }
}


inline long long int work(int cnt)
{
    long long int ans = 0;
    int len = 0;
    while (cnt)
    {
        cntArr[len++] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len] = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        for (int j = 0; j < cntArr[i]; j++)
        {
            if (j == 4 || (cntArr[i + 1] == 6 && j == 2))
                continue;
            ans += dp[i + 1][j];
        }

        if (cntArr[i] == 4 || (cntArr[i + 1] == 6 && cntArr[i] == 2))
            break;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int leftPt, rightPt;
    while (cin >> leftPt >> rightPt)
    {
        if (leftPt == 0 && rightPt == 0)
            break;
        cout << work(rightPt + 1) - work(leftPt) << endl;
    }
    return 0;
}