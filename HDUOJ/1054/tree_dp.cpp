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

#define SIZE 1510

typedef struct _Edge
{
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int dp[2][SIZE];
int vertexNum;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    dp[0][cntPt] = 0;
    dp[1][cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);
        dp[0][cntPt] += dp[1][nextPt];
        dp[1][cntPt] += min(dp[0][nextPt], dp[1][nextPt]);
    }
}

int main()
{
    while (scanf("%d", &vertexNum) != EOF)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            int from, cntNum;
            scanf("%d:(%d)", &from, &cntNum);
            while (cntNum--)
            {
                int to;
                scanf("%d", &to);
                addEdge(from, to);
                addEdge(to, from);
            }
        }

        dfs(0, -1);
        cout << min(dp[0][0], dp[1][0]) << endl;
    }

    return 0;
}