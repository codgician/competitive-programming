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

#define SIZE 100010

typedef struct _Edge
{
    int to, len, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int vertexNum;

pair<int, int> dp[SIZE];
int maxLen, num;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    dp[cntPt].first = 0;
    dp[cntPt].second = 1;

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);

        int cntLen = dp[nextPt].first + arr[i].len;
        if (cntLen + dp[cntPt].first > maxLen)
        {
            maxLen = cntLen + dp[cntPt].first;
            num = dp[cntPt].second * dp[nextPt].second;
        }
        else if (cntLen + dp[cntPt].first == maxLen)
        {
            num += dp[cntPt].second * dp[nextPt].second;
        }

        if (cntLen > dp[cntPt].first)
        {
            dp[cntPt].first = cntLen;
            dp[cntPt].second = dp[nextPt].second;
        }
        else if (cntLen == dp[cntPt].first)
        {
            dp[cntPt].second += dp[nextPt].second;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> vertexNum)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        maxLen = 0, num = 0;

        for (int i = 1; i < vertexNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--;
            to--;
            addEdge(from, to, len);
            addEdge(to, from, len);
        }

        dfs(0, -1);

        cout << maxLen << " " << num << endl;
    }

    return 0;
}