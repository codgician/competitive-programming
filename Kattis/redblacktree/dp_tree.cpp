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

#define SIZE 200001
#define RED_SIZE 1001

const int mod = 1e9 + 7;

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[SIZE];
int head[SIZE], arrPt;

int dp[SIZE][RED_SIZE], tmp[RED_SIZE];
int sizeArr[SIZE], redSize[SIZE];

int vertexNum, redNum;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    sizeArr[cntPt] = redSize[cntPt];
    dp[cntPt][0] = 1;

    // Not select cntPt
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        dfs(nextPt);

        for (int j = 0; j <= min(sizeArr[cntPt] + sizeArr[nextPt], redNum); j++)
            tmp[j] = 0;
        for (int j = 0; j <= min(sizeArr[nextPt], redNum); j++)
        {
            for (int k = 0; k <= sizeArr[cntPt] && j + k <= redNum; k++)
            {
                tmp[j + k] = (1ll * dp[nextPt][j] * dp[cntPt][k] % mod + tmp[j + k]) % mod;
            }
        }
        sizeArr[cntPt] += sizeArr[nextPt];
        for (int j = 0; j <= min(sizeArr[cntPt] + sizeArr[nextPt], redNum); j++)
        {
            dp[cntPt][j] = tmp[j];
        }
    }

    // Select cntPt
    dp[cntPt][redSize[cntPt]] = (dp[cntPt][redSize[cntPt]] + 1) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> vertexNum >> redNum)
    {
        memset(head, -1, sizeof(head));
        memset(sizeArr, 0, sizeof(sizeArr));
        memset(redSize, 0, sizeof(redSize));
        arrPt = 0;
        for (int i = 1; i < vertexNum; i++)
        {
            int parent;
            cin >> parent;
            parent--;
            addEdge(parent, i);
        }

        for (int i = 0; i < redNum; i++)
        {
            int cntPt;
            cin >> cntPt;
            cntPt--;
            redSize[cntPt] = 1;
        }

        dfs(0);

        for (int i = 0; i <= redNum; i++)
        {
            cout << dp[0][i] << endl;
        }
    }

    return 0;
}