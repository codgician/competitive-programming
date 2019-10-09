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

#define SIZE 105
#define LIM_SIZE 505

typedef struct _Edge
{
    int to, len, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int vertexNum, lim;

int valArr[SIZE], minLen;
int dp[SIZE][LIM_SIZE];

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

bool dfs1(int cntPt, int parentPt)
{
    if (cntPt == vertexNum - 1)
        return true;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        if (dfs1(nextPt, cntPt))
        {
            minLen += arr[i].len;
            arr[i].len = 0;
            arr[i ^ 1].len = 0;
            return true;
        }
    }
    return false;
}

void dfs2(int cntPt, int parentPt)
{
    for (int i = 0; i <= lim; i++)
        dp[cntPt][i] = valArr[cntPt];

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs2(nextPt, cntPt);

        int cost = arr[i].len << 1;
        for (int i = lim; i >= cost; i--)
        {   
            for (int k = 0; k <= i - cost; k++)
            {
                dp[cntPt][i] = max(dp[cntPt][i], dp[cntPt][i - cost - k] + dp[nextPt][k]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> vertexNum >> lim)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        for (int i = 1; i < vertexNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--, to--;
            addEdge(from, to, len);
            addEdge(to, from, len);
        }

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> valArr[i];
        }

        minLen = 0;
        dfs1(0, -1);
        lim -= minLen;
        if (lim < 0)
        {
            cout << "Human beings die in pursuit of wealth, and birds die in pursuit of food!" << endl;
            continue;
        }

        dfs2(0, -1);
        cout << dp[0][lim] << endl;
    }

    return 0;
}