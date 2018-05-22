#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define VERTEX_SIZE 1010
#define EDGE_SIZE 510000
#define NUM_SIZE 7
using namespace std;

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge graph[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int posArr[NUM_SIZE][VERTEX_SIZE];

int dp[VERTEX_SIZE];
bool hasVisited[VERTEX_SIZE];
int startPt, endPt;

void addEdge(int from, int to)
{
    graph[arrPt] = {to, head[from]};
    head[from] = arrPt++;  
}

int getDp(int cntPt)
{
    if (hasVisited[cntPt] || cntPt == endPt)
        return dp[cntPt];

    hasVisited[cntPt] = true;

    for (int i = head[cntPt]; i != -1; i = graph[i].next)
    {
        int nextDp = getDp(graph[i].to);
        if (nextDp != INT_MIN)
            dp[cntPt] = max(dp[cntPt], nextDp + 1);
    }

    return dp[cntPt];
}

int main()
{
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    arrPt = 0;
    int len, num;
    cin >> len >> num;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < len; j++)
        {
            int cnt;
            cin >> cnt;
            posArr[i][cnt] = j;
        }
    }

    startPt = 0;
    endPt = len + 1;

    for (int i = 1; i <= len; i++)
    {
        addEdge(startPt, i);
        addEdge(i, endPt);

        for (int j = 1; j <= len; j++)
        {
            if (i == j)
                continue;

            bool canAdd = true;
            for (int k = 0; k < num; k++)
            {
                if (posArr[k][i] > posArr[k][j])
                {
                    canAdd = false;
                    break;
                }
            }

            if (canAdd)
            {
                addEdge(i, j);
            }
        }
    }

    memset(hasVisited, false, sizeof(hasVisited));
    for (int i = 0; i < endPt; i++)
        dp[i] = INT_MIN;
    dp[endPt] = 0;

    int ans = getDp(startPt);

    cout << ans - 1 << endl;
    return 0;
}