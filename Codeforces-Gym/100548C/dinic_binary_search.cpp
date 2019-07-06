#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <cfloat>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define EDGE_SIZE 44100
#define VERTEX_SIZE 210

const double eps = 1e-9;

typedef struct _Inv
{
    int from, to;
} Inv;

Inv invArr[EDGE_SIZE];
int invPt;

typedef struct _Edge
{
    int to;
    double capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int vertexNum;

int numArr[VERTEX_SIZE], degArr[VERTEX_SIZE], len;


void addEdge(int from, int to, double capacity)
{
    arr[arrPt] = {to, capacity, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, head[to]};
    head[to] = arrPt++;
}

bool updateDepth(int startPt, int endPt)
{
    memset(depth, -1, sizeof(depth));
    queue<int> q;

    depth[startPt] = 0;
    q.push(startPt);

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            if (depth[nextPt] == -1 && arr[i].capacity > eps)
            {
                depth[nextPt] = depth[cntPt] + 1;
                if (nextPt == endPt)
                    return true;
                q.push(nextPt);
            }
        }
    }
    return false;
}

double findAugPath(int cntPt, int endPt, double minCap)
{
    if (cntPt == endPt)
        return minCap;

    double cntFlow = 0;
    for (int & i = lastVisitedEdge[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (depth[nextPt] == depth[cntPt] + 1 && arr[i].capacity > eps)
        {
            double flowInc = findAugPath(nextPt, endPt, min(minCap - cntFlow, arr[i].capacity));
            if (fabs(flowInc) <= eps)
            {
                depth[nextPt] = -1;
            }
            else
            {
                arr[i].capacity -= flowInc;
                arr[i ^ 1].capacity += flowInc;
                cntFlow += flowInc;
                if (cntFlow == minCap)
                    break;
            }
        }
    }
    return cntFlow;
}

double dinic(int startPt, int endPt)
{
    double ans = 0;
    while (updateDepth(startPt, endPt))
    {
        for (int i = 0; i < vertexNum; i++)
            lastVisitedEdge[i] = head[i];

        double flowInc =  findAugPath(startPt, endPt, DBL_MAX);
        if (fabs(flowInc) <= eps)
            break;
        ans += flowInc;
    }
    return ans;
}

bool check(double cntDensity)
{
    memset(head, -1, sizeof(head));
    arrPt = 0;

    int startPt = len, endPt = len + 1;
    vertexNum = len + 2;

    for (int i = 0; i < invPt; i++)
    {
        addEdge(invArr[i].from, invArr[i].to, 1.0);
        addEdge(invArr[i].to, invArr[i].from, 1.0);
    }

    for (int i = 0; i < len; i++)
    {
        addEdge(startPt, i, invPt);
        addEdge(i, endPt, (double)invPt + 2 * cntDensity - degArr[i]);
    }

    double res = dinic(startPt, endPt);
    return (double)invPt * len - res >= eps;
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
        memset(degArr, 0, sizeof(degArr));
        invPt = 0;

        cin >> len;
        for (int i = 0; i < len; i++)
        {
            cin >> numArr[i];
            for (int j = 0; j < i; j++)
            {
                if (numArr[j] > numArr[i])
                {
                    invArr[invPt++] = {j, i};
                    degArr[j]++;
                    degArr[i]++;
                }
            }
        }

        double leftPt = 0, rightPt = invPt;
        double ans = 0;
        while (rightPt - leftPt > eps)
        {
            double midPt = (leftPt + rightPt) / 2;
            if (check(midPt))
            {
                ans = midPt;
                leftPt = midPt;
            }
            else
            {
                rightPt = midPt;
            }
        }

        cout << "Case #" << t << ": ";
        cout << fixed << setprecision(7) << ans << endl;
    }

    return 0;
}