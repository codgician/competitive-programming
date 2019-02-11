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

#define SIZE 21
#define DP_SIZE (1 << 21)

typedef struct _Prob
{
    long long int a, b;
    int reqNum, reqState;
} Prob;

Prob arr[SIZE];
long long int dp[DP_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int probNum;
    while (cin >> probNum)
    {
        for (int i = 0; i < probNum; i++)
        {
            cin >> arr[i].a >> arr[i].b >> arr[i].reqNum;
            arr[i].reqState = 0;

            for (int j = 0; j < arr[i].reqNum; j++)
            {
                int cnt;
                cin >> cnt;
                cnt--;

                if (cnt == i)
                {
                    probNum--;
                    i--;
                    break;
                }

                arr[i].reqState |= (1 << cnt);
            }
        }

        long long int ans = 0;
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        for (int i = 0; i < (1 << probNum); i++)
        {
            if (dp[i] == -1)
                continue;

            for (int j = 0; j < probNum; j++)
            {
                if (i & (1 << j) || (i & arr[j].reqState) != arr[j].reqState)
                    continue;
                int cntStep = __builtin_popcount(i) + 1;
                long long int newScr = cntStep * arr[j].a + arr[j].b;
                dp[i | (1 << j)] = max(dp[i | (1 << j)], dp[i] + newScr);
                ans = max(ans, dp[i | (1 << j)]);
            }
        }
        
        cout << ans << endl;
    }
    return 0;
}