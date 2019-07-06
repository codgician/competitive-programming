#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define MAT_SIZE 21
#define VERTEX_SIZE 900
#define EDGE_SIZE 410000
#define IN true
#define OUT false
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
int mat[MAT_SIZE][MAT_SIZE];
int matrixSize, vertexNum;

int getBlockId(int i, int j)
{
    return i * matrixSize + j + 1;
}

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

int findAugPath(int cntPt, int endPt, int minCapacity)
{
    if (cntPt == endPt)
        return minCapacity;

    int cntFlow = 0;
    int &edgePt = lastVisitedEdge[cntPt];
    while (edgePt != -1)
    {
        if (depth[arr[edgePt].to] == depth[cntPt] + 1 && arr[edgePt].capacity > 0)
        {
            int flowInc = findAugPath(arr[edgePt].to, endPt, min(minCapacity - cntFlow, arr[edgePt].capacity));
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
        {
            lastVisitedEdge[i] = head[i];
        }
        int flowInc = findAugPath(startPt, endPt, INT_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> matrixSize)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        int sum = 0;
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                cin >> mat[i][j];
                sum += mat[i][j];
            }
        }

        int startPt = 0, endPt = matrixSize * matrixSize + 1;
        vertexNum = endPt + 1;
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                if ((i + j) & 1)
                {
                    addEdge(getBlockId(i, j), endPt, mat[i][j]);
                }
                else
                {
                    addEdge(startPt, getBlockId(i, j), mat[i][j]);
                    if (i > 0)
                        addEdge(getBlockId(i, j), getBlockId(i - 1, j), INT_MAX);
                    if (i < matrixSize - 1)
                        addEdge(getBlockId(i, j), getBlockId(i + 1, j), INT_MAX);
                    if (j > 0)
                        addEdge(getBlockId(i, j), getBlockId(i, j - 1), INT_MAX);
                    if (j < matrixSize - 1)
                        addEdge(getBlockId(i, j), getBlockId(i, j + 1), INT_MAX);
                }
            }
        }

        int ans = sum - dinic(startPt, endPt);
        cout << ans << endl;
    }
    return 0;
}
