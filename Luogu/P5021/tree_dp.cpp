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

#define SIZE 50010

typedef struct _Edge
{
    int to, len, next;
} Edge;

Edge arr[SIZE];
int head[SIZE], arrPt;

int okNum[SIZE], maxLen[SIZE];

int vertexNum, pathNum, cntLim;

multiset<int> mst;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;

        dfs(nextPt);
    }

    okNum[cntPt] = 0;
    maxLen[cntPt] = 0;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;

        okNum[cntPt] += okNum[nextPt];
        int cntLen = maxLen[nextPt] + arr[i].len;
        if (cntLen >= cntLim)
            okNum[cntPt]++;
        else
            mst.insert(cntLen);
    }

    while (!mst.empty())
    {
        int cntLen = *mst.begin();
        mst.erase(mst.begin());

        auto it = mst.lower_bound(cntLim - cntLen);
        if (it == mst.end())
        {
            maxLen[cntPt] = max(maxLen[cntPt], cntLen);
        }
        else
        {
            okNum[cntPt]++;
            mst.erase(it);
        }
    }
}

bool check(int cnt)
{
    cntLim = cnt;
    dfs(0);
    if (okNum[0] < pathNum)
        return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(head, -1, sizeof(head));
    arrPt = 0;
    
    cin >> vertexNum >> pathNum;

    int leftPt = INT_MAX, rightPt = 0;
    for (int i = 1; i < vertexNum; i++)
    {
        int from, to, len;
        cin >> from >> to >> len;
        from--, to--;
        if (from > to)
            swap(from, to);
        addEdge(from, to, len);

        leftPt = min(leftPt, len);
        rightPt += len;
    }
    rightPt /= pathNum;

    int ans = leftPt;
    while (leftPt <= rightPt)
    {
        int midPt = (leftPt + rightPt) >> 1;
        if (check(midPt))
        {
            leftPt = midPt + 1;
            ans = midPt;
        }
        else
        {
            rightPt = midPt - 1;
        }
    }

    cout << ans << endl;
    return 0;
}