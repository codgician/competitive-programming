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

#define SIZE 6010

typedef struct _Edge
{
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;

int rateArr[SIZE];

int dp[SIZE][2];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    dp[cntPt][0] = 0;
    dp[cntPt][1] = rateArr[cntPt];
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);

        dp[cntPt][0] += max(dp[nextPt][0], dp[nextPt][1]);
        dp[cntPt][1] += dp[nextPt][0];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int vertexNum;
    while (cin >> vertexNum)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;

        for (int i = 0; i < vertexNum; i++)
            cin >> rateArr[i];

        int from, to;
        while (cin >> from >> to)
        {
            if (from == 0 && to == 0)
                break;
            from--;
            to--;
            addEdge(from, to);
            addEdge(to, from);
        }
        dfs(0, -1);
        cout << max(dp[0][0], dp[0][1]) << endl;
    }

    return 0;
}