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

typedef struct _Edge
{
    int to;
    long long int len;
    int next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;

long long int dp[SIZE];

void addEdge(int from, int to, long long int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    dp[cntPt] = LLONG_MAX;
    long long int cntAns = 0;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);
        cntAns += min(arr[i].len, dp[nextPt]);
    }
    if (cntAns != 0)
        dp[cntPt] = cntAns;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int vertexNum, rootPt;
    while (cin >> vertexNum >> rootPt)
    {
        if (vertexNum == 0 && rootPt == 0)
            break;
        rootPt--;

        memset(head, -1, sizeof(head));
        arrPt = 0;

        for (int i = 1; i < vertexNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--;
            to--;
            addEdge(from, to, len);
            addEdge(to, from, len);
        }

        if (vertexNum <= 1)
        {
            cout << 0 << endl;
            continue;
        }

        dfs(rootPt, -1);

        cout << dp[rootPt] << endl;
    }

    return 0;
}