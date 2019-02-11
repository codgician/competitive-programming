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
int probNum;

long long int ans = 0;

void dfs(int state, long long int cntScr)
{
    if (dp[state] >= cntScr)
    {
        return;
    }
    dp[state] = cntScr;
    ans = max(ans, cntScr);

    int cntStep = __builtin_popcount(state) + 1;
    if (cntStep > probNum)
        return;

    for (int i = 0; i < probNum; i++)
    {
        if (state & (1 << i))
            continue;

        if ((state & arr[i].reqState) == arr[i].reqState)
        {
            int nextState = state | (1 << i);
            long long int nextScr = cntScr + arr[i].a * cntStep + arr[i].b;
            dfs(nextState, nextScr);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> probNum)
    {
        memset(dp, -1, sizeof(dp));
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

        ans = 0;
        dfs(0, 0);

        cout << ans << endl;
    }
    return 0;
}