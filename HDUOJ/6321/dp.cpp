#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 2048

const int mod = 1e9 + 7;
int dp[2][SIZE];
int ans[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(dp, 0, sizeof(dp));
        dp[1][0] = 1;
        int vertexNum, oprNum;
        cin >> vertexNum >> oprNum;
        for (int i = 0; i < oprNum; i++)
        {
            char opr;
            int from, to;
            cin >> opr >> from >> to;
            from--;
            to--;

            for (int j = 0; j < (1 << vertexNum); j++)
                dp[i & 1][j] = dp[!(i & 1)][j];

            int cnt = (1 << from) | (1 << to);
            if (opr == '+')
            {
                for (int j = 0; j < (1 << vertexNum); j++)
                {
                    if (!(j & cnt))
                    {
                        dp[i & 1][j ^ cnt] = (dp[!(i & 1)][j ^ cnt] + dp[!(i & 1)][j]) % mod;
                    }
                }
            }
            else if (opr == '-')
            {
                for (int j = 0; j < (1 << vertexNum); j++)
                {
                    if (!(j & cnt))
                    {
                        dp[i & 1][j ^ cnt] = (dp[!(i & 1)][j ^ cnt] - dp[!(i & 1)][j] + mod) % mod;
                    }
                }
            }

            memset(ans, 0, sizeof(ans));
            for (int j = 0; j < (1 << vertexNum); j++)
            {
                int cntNum = __builtin_popcount(j);
                ans[cntNum] += dp[i & 1][j];
                ans[cntNum] %= mod;
            }
            
            for (int j = 2; j <= vertexNum; j += 2)
            {
                if (j > 2)
                    cout << " ";
                cout << ans[j];
            }
            cout << endl;
        }
    }
    return 0;
}