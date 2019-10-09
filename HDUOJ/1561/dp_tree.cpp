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

#define SIZE 210

typedef struct _Edge
{
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int valArr[SIZE];

int dp[SIZE][SIZE];
int vertexNum, bagSize;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    dp[cntPt][1] = valArr[cntPt];
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        dfs(nextPt);

        for (int j = bagSize + 1; j >= 2; j--)
        {
            for (int k = 0; k < j; k++)
            {
                dp[cntPt][j] = max(dp[cntPt][j], dp[cntPt][j - k] + dp[nextPt][k]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> vertexNum >> bagSize)
    {
        if (vertexNum == 0 && bagSize == 0)
            break;
        memset(head, -1, sizeof(head));
        memset(dp, 0, sizeof(dp));
        arrPt = 0;

        valArr[0] = 0;
        for (int i = 1; i <= vertexNum; i++)
        {
            int from;
            cin >> from >> valArr[i];
            addEdge(from, i);
        }

        dfs(0);

        cout << dp[0][bagSize + 1] << endl;
    }

    return 0;
}