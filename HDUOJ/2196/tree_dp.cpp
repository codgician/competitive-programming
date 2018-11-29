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

#define SIZE 10010

typedef struct _Edge
{
    int to;
    long long int len;
    int next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int vertexNum;

long long int dp[3][SIZE];
int maxNextPt[SIZE];

void addEdge(int from, int to, long long int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void dfs1(int cntPt, int parentPt)
{
    long long int maxLen = 0, secMaxLen = 0;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs1(nextPt, cntPt);

        long long int nextLen = dp[0][nextPt] + arr[i].len;
        if (maxLen <= nextLen)
        {
            secMaxLen = maxLen;
            maxLen = nextLen;
            maxNextPt[cntPt] = nextPt;
        }
        else if (secMaxLen < nextLen)
        {
            secMaxLen = nextLen;
        }
    }

    dp[0][cntPt] = maxLen;
    dp[1][cntPt] = secMaxLen;
}

void dfs2(int cntPt, int parentPt)
{
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        if (maxNextPt[cntPt] == nextPt)
            dp[2][nextPt] = max(dp[1][cntPt], dp[2][cntPt]) + arr[i].len;
        else
            dp[2][nextPt] = max(dp[0][cntPt], dp[2][cntPt]) + arr[i].len;
        dfs2(nextPt, cntPt);
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
        memset(dp, 0, sizeof(dp));
        memset(maxNextPt, -1, sizeof(maxNextPt));
        arrPt = 0;

        for (int i = 1; i < vertexNum; i++)
        {
            int to, len;
            cin >> to >> len;
            to--;
            addEdge(i, to, len);
            addEdge(to, i, len);
        }

        dfs1(0, -1);
        dfs2(0, -1);

        for (int i = 0; i < vertexNum; i++)
        {
            cout << max(dp[0][i], dp[2][i]) << endl;
        }
    }

    return 0;
}