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
#include <cassert>
using namespace std;

#define SIZE 16
#define DP_SIZE (1 << 16)

typedef struct _Subject
{
    string name;
    int ddl, time;
} Subject;

Subject arr[SIZE];
pair<int, int> dp[DP_SIZE];
int ans[SIZE], tmp[SIZE], num;
int cntFst;

bool isSmaller()
{
    if (ans[0] == -1)
        return true;
    for (int i = num - 1; i >= 0; i--)
    {
        if (tmp[i] > ans[i])
            return false;
        if (tmp[i] < ans[i])
            return true;
    }
    return false;
}

void dfs(int cntState, int depth)
{
    if (cntState == 0)
    {
        if (isSmaller())
        {
            for (int i = 0; i < depth; i++)
                ans[i] = tmp[i];
        }
        return;
    }
    for (int i = 0; i < num; i++)
    {
        int cnt = 1 << i;
        if (!(cntState & cnt))
            continue;
        int scr = dp[cntState ^ cnt].second + arr[i].time - arr[i].ddl;
        if (scr < 0)
            scr = 0;
        if (dp[cntState].first == dp[cntState ^ cnt].first + scr)
        {
            tmp[depth] = i;
            dfs(cntState ^ cnt, depth + 1);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> num;
        int state = 1 << num;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i].name >> arr[i].ddl >> arr[i].time;
        }

        dp[0] = make_pair(0, 0);
        for (int i = 1; i < state; i++)
        {
            dp[i].first = INT_MAX;
            for (int j = 0; j < num; j++)
            {
                int cnt = 1 << j;
                if (!(i & cnt))
                    continue;
                int scr = dp[i ^ cnt].second + arr[j].time - arr[j].ddl;
                if (scr < 0)
                    scr = 0;
                if (dp[i].first > dp[i ^ cnt].first + scr)
                {
                    dp[i].first = dp[i ^ cnt].first + scr;
                    dp[i].second = dp[i ^ cnt].second + arr[j].time;
                }
            }
        }

        cout << dp[state - 1].first << endl;
        memset(ans, -1, sizeof(ans));
        dfs(state - 1, 0);
        for (int i = num - 1; i >= 0; i--)
            cout << arr[ans[i]].name << endl;
    }

    return 0;
}