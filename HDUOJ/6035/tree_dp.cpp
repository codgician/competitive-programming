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

#define SIZE 200010

typedef struct _Edge
{
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int colorArr[SIZE], vertexNum;

bool hasColor[SIZE];
int sizeArr[SIZE], colorVtxNum[SIZE];
long long int ans;

long long int getComb2(long long int n)
{
    return (n & 1) ? ((n - 1) >> 1) * n : (n >> 1) * (n - 1);
}

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    sizeArr[cntPt] = 1;
    int cntColor = colorArr[cntPt];
    colorVtxNum[cntColor]++;
    int preVtxNum = colorVtxNum[cntColor];

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;

        dfs(nextPt, cntPt);
        sizeArr[cntPt] += sizeArr[nextPt];

        int cntVtxNum = sizeArr[nextPt] - colorVtxNum[cntColor] + preVtxNum;
        ans += getComb2(cntVtxNum);
        colorVtxNum[cntColor] += cntVtxNum;
        preVtxNum = colorVtxNum[cntColor];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int casePt = 0;
    while (cin >> vertexNum)
    {
        memset(head, -1, sizeof(head));
        memset(sizeArr, 0, sizeof(sizeArr));
        memset(hasColor, false, sizeof(hasColor));
        memset(colorVtxNum, 0, sizeof(colorVtxNum));
        arrPt = 0;
        ans = 0;

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> colorArr[i];
            colorArr[i]--;
            hasColor[colorArr[i]] = true;
        }

        for (int i = 1; i < vertexNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to);
            addEdge(to, from);
        }

        dfs(0, -1);

        int colorNum = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            if (hasColor[i])
            {
                ans += getComb2(vertexNum - colorVtxNum[i]);
                colorNum++;
            }
        }

        ans = getComb2(vertexNum) * colorNum - ans;
        cout << "Case #" << ++casePt << ": " << ans << endl;
    }

    return 0;
}