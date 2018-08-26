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
using namespace std;

#define EDGE_SIZE 100010
#define VERTEX_SIZE 100010

const int mod = 1e9 + 7;

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum;

long long int factorialArr[VERTEX_SIZE];
long long int dp[VERTEX_SIZE], ans;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < VERTEX_SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

void dfs(int cntPt)
{
    dp[cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        dfs(nextPt);
        dp[cntPt] += dp[nextPt];
        if (dp[cntPt] >= mod)
            dp[cntPt] %= mod;
        ans += dp[nextPt] * (vertexNum - dp[nextPt]) % mod * arr[i].len % mod;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initFactorial();
    while (cin >> vertexNum)
    {
        memset(head, -1, sizeof(head));
        memset(dp, 0, sizeof(dp));
        arrPt = 0;

        for (int i = 0; i < vertexNum - 1; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--;
            to--;
            if (from > to)
                swap(from, to);
            addEdge(from, to, len);
        }

        ans = 0;
        dfs(0);

        ans = (ans << 1) % mod * factorialArr[vertexNum - 1] % mod;
        cout << ans << endl; 
    }

    return 0;
}