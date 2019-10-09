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

int dp[SIZE];
long long int ans;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    dp[cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);
        dp[cntPt] += dp[nextPt];
        int minNum = min(dp[nextPt], vertexNum - dp[nextPt]);
        ans += 2ll * minNum * arr[i].len;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;

        cin >> vertexNum;
        for (int i = 1; i < vertexNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--;
            to--;
            addEdge(from, to, len);
            addEdge(to, from, len);
        }
        ans = 0;
        dfs(0, -1);
        cout << "Case #" << t << ": " << ans << endl;
   }

    return 0;
}