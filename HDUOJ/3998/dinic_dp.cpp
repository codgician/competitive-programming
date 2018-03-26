#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SEQ_SIZE 1010
#define VERTEX_SIZE 2050
#define EDGE_SIZE 8700000
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int vertexNum;

int seqArr[SEQ_SIZE], dp[SEQ_SIZE];

void addEdge(int from, int to, int capacity)
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

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            if (depth[arr[edgePt].to] == -1 && arr[edgePt].capacity > 0)
            {
                depth[arr[edgePt].to] = depth[cntPt] + 1;
                if (arr[edgePt].to == endPt)
                    return true;
                q.push(arr[edgePt].to);
            }
            edgePt = arr[edgePt].next;
        }
    }
    return false;
}

int findAguPath(int cntPt, int endPt, int minCapacity)
{
    if (cntPt == endPt)
        return minCapacity;

    int cntFlow = 0;
    int &edgePt = lastVisitedEdge[cntPt];
    while (edgePt != -1)
    {
        if (depth[arr[edgePt].to] == depth[cntPt] + 1 && arr[edgePt].capacity > 0)
        {
            int flowInc = findAguPath(arr[edgePt].to, endPt, min(minCapacity - cntFlow, arr[edgePt].capacity));
            if (flowInc == 0)
            {
                depth[arr[edgePt].to] = -1;
            }
            else
            {
                arr[edgePt].capacity -= flowInc;
                arr[edgePt ^ 1].capacity += flowInc;
                cntFlow += flowInc;
                if (cntFlow == minCapacity)
                    break;
            }
        }
        edgePt = arr[edgePt].next;
    }
    return cntFlow;
}


int dinic(int startPt, int endPt)
{
    int ans = 0;
    while (updateDepth(startPt, endPt))
    {
        for (int i = 0; i < vertexNum; i++)
            lastVisitedEdge[i] = head[i];
        int flowInc = findAguPath(startPt, endPt, INT_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int seqSize;
    while (cin >> seqSize)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < seqSize; i++)
        {
            cin >> seqArr[i];
        }

        for (int i = 0; i < seqSize; i++)
            dp[i] = 1;
        int len = 1;
        for (int i = 1; i < seqSize; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (seqArr[i] > seqArr[j])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                    len = max(len, dp[i]);
                }
            }
        }

        cout << len << endl;

        int startPt = 0, endPt = (seqSize << 1) + 1;
        vertexNum = endPt + 1;

        for (int i = 0; i < seqSize; i++)
        {
            addEdge(i + 1, i + seqSize + 1, 1);
            if (dp[i] == 1)
                addEdge(startPt, i + 1, 1);
            if (dp[i] == len)
                addEdge(i + seqSize + 1, endPt, 1);

            for (int j = i + 1; j < seqSize; j++)
            {
                if (seqArr[j] > seqArr[i] && dp[j] == dp[i] + 1)
                {
                    addEdge(i + seqSize + 1, j + 1, 1);
                }
            }
        }

        int num = dinic(startPt, endPt);
        cout << num << endl;
    }
    return 0;
}
