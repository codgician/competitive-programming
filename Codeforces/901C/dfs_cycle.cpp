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

#define VERTEX_SIZE 300010
#define EDGE_SIZE 600010

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

stack<int> stk;
bool hasVisited[VERTEX_SIZE], inStack[VERTEX_SIZE];

int pfxMaxMinPt[VERTEX_SIZE];
long long int pfxMaxMinPtSum[VERTEX_SIZE];

int vertexNum, edgeNum;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int prevPt)
{
    hasVisited[cntPt] = true;
    inStack[cntPt] = true;
    stk.push(cntPt);

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == prevPt)
            continue;
        if (hasVisited[nextPt] && !inStack[nextPt])
            continue;

        if (hasVisited[nextPt])
        {
            int minPt = INT_MAX, maxPt = -1;

            while (!stk.empty())
            {
                int cntTop = stk.top();
                stk.pop();
                inStack[cntTop] = false;

                minPt = min(minPt, cntTop);
                maxPt = max(maxPt, cntTop);

                if (cntTop == nextPt)
                    break;
            }

            pfxMaxMinPt[maxPt] = max(pfxMaxMinPt[maxPt], minPt);
        }
        else
        {
            dfs(nextPt, cntPt);
        }
    }

    if (!stk.empty() && stk.top() == cntPt)
    {
        stk.pop();
        inStack[cntPt] = false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(head, -1, sizeof(head));
    arrPt = 0;
    cin >> vertexNum >> edgeNum;
    for (int i = 0; i < edgeNum; i++)
    {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        addEdge(from, to);
        addEdge(to, from);
    }

    memset(inStack, false, sizeof(inStack));
    memset(hasVisited, false, sizeof(hasVisited));
    memset(pfxMaxMinPt, -1, sizeof(pfxMaxMinPt));
    for (int i = 0; i < vertexNum; i++)
    {
        assert(stk.empty() == true);
        if (!hasVisited[i])
            dfs(i, -1);
    }

    pfxMaxMinPtSum[0] = pfxMaxMinPt[0];
    for (int i = 1; i < vertexNum; i++)
    {
        pfxMaxMinPt[i] = max(pfxMaxMinPt[i], pfxMaxMinPt[i - 1]);
        pfxMaxMinPtSum[i] = pfxMaxMinPtSum[i - 1] + pfxMaxMinPt[i];
    }

    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        int qLeftPt, qRightPt;
        cin >> qLeftPt >> qRightPt;
        qLeftPt--;
        qRightPt--;

        long long int ans = ((long long int)(qLeftPt + qRightPt) * (qRightPt - qLeftPt + 1)) >> 1;
        int pos = upper_bound(pfxMaxMinPt + qLeftPt, pfxMaxMinPt + qRightPt + 1, qLeftPt - 1) - (pfxMaxMinPt + qLeftPt) - 1;
        ans -= (long long int)(qLeftPt - 1) * (pos + 1) + (qLeftPt + pos <= qRightPt ? pfxMaxMinPtSum[qRightPt] - (qLeftPt + pos >= 0 ? pfxMaxMinPtSum[qLeftPt + pos] : 0) : 0);
        cout << ans << endl;
    }

    return 0;
}