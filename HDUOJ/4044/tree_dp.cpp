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
#define MON_SIZE 210

typedef struct _Edge
{
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int vertexNum, moneyLim;

vector<pair<int, int> > optArr[SIZE];
int dp[SIZE][MON_SIZE];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    dp[cntPt][0] = INT_MAX;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);

        for (int j = moneyLim; j >= 0; j--)
        {
            int tmp = 0;
            for (int k = 0; k <= j; k++)
            {
                tmp = max(tmp, min(dp[nextPt][k], dp[cntPt][j - k]));
            }
            dp[cntPt][j] = tmp;
        }
    }

    if (dp[cntPt][0] == INT_MAX)
        dp[cntPt][0] = 0;

    for (int i = moneyLim; i >= 0; i--)
    {
        int tmp = dp[cntPt][i];
        for (auto cnt : optArr[cntPt])
        {
            int cost = cnt.first, value = cnt.second;
            if (i - cost < 0)
                continue;
            tmp = max(tmp, dp[cntPt][i - cost] + value);
        }
        dp[cntPt][i] = tmp;
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
        memset(head, -1, sizeof(head));
        memset(dp, 0, sizeof(dp));
        arrPt = 0;

        cin >> vertexNum;
        for (int i = 1; i < vertexNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to);
            addEdge(to, from);
        }

        cin >> moneyLim;
        for (int i = 0; i < vertexNum; i++)
        {
            optArr[i].clear();
            int cntNum;
            cin >> cntNum;
            while (cntNum--)
            {
                int cost, value;
                cin >> cost >> value;
                optArr[i].push_back(make_pair(cost, value));
            }
        }

        dfs(0, -1);
        cout << dp[0][moneyLim] << endl;
    }

    return 0;
}