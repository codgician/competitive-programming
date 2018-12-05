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

#define SIZE 1010
#define VAL_SIZE 1000010

typedef struct _Edge
{
    int to, val, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int vertexNum, powerLim, cntLim;

int dp[SIZE];

void addEdge(int from, int to, int val)
{
    arr[arrPt] = {to, val, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    dp[cntPt] = INT_MAX;
    int cntAns = 0;

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);
        
        if (arr[i].val > cntLim)
        {
            if (dp[nextPt] == INT_MAX)
            {
                cntAns = INT_MAX;
                break;
            }
            else
            {
                cntAns += dp[nextPt];
            }
        }
        else
        {
            cntAns += min(dp[nextPt], arr[i].val);
        }
    }

    if (cntAns != 0)
        dp[cntPt] = cntAns;
}

bool check(int cnt)
{
    cntLim = cnt;
    dfs(0, -1);
    if (dp[0] > powerLim)
        return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> vertexNum >> powerLim)
    {
        if (vertexNum == 0 && powerLim == 0)
            break;
        memset(head, -1, sizeof(head));
        arrPt = 0;

        int leftPt = INT_MAX, rightPt = 0;
        for (int i = 1; i < vertexNum; i++)
        {
            int from, to, val;
            cin >> from >> to >> val;
            from--;
            to--;
            addEdge(from, to, val);
            addEdge(to, from, val);
            leftPt = min(leftPt, val);
            rightPt = max(rightPt, val);
        }

        int ans = -1;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt))
            {
                rightPt = midPt - 1;
                ans = midPt;
            }
            else
            {
                leftPt = midPt + 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}