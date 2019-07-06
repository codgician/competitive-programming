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
#define MAP_SIZE 21
#define VERTEX_SIZE 810
#define EDGE_SIZE 321000
#define IN false
#define OUT true
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
string pillar[MAP_SIZE];
int row, column, vertexNum;

int getBlockId(int i, int j, bool type)
{
    int ans = i * column + j + 1;
    if (type == OUT)
        ans += row * column;
    return ans;
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
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        int maxLeap;
        cin >> row >> maxLeap;
        for (int i = 0; i < row; i++)
            cin >> pillar[i];
        column = pillar[0].length();
        int startPt = 0, endPt = ((row * column) << 1) + 1;
        vertexNum = endPt + 1;

        int lizardNum = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                char ch;
                cin >> ch;
                if (ch == 'L')
                {
                    addEdge(startPt, getBlockId(i, j, IN), 1);
                    lizardNum++;
                }

                if (pillar[i][j] == '0')
                    continue;

                if (i < maxLeap || j < maxLeap || i > row - maxLeap - 1 || j > column - maxLeap - 1)
                {
                    addEdge(getBlockId(i, j, IN), endPt, pillar[i][j] - '0');
                }
                else
                {
                    addEdge(getBlockId(i, j, IN), getBlockId(i, j, OUT), pillar[i][j] - '0');
                    for (int k = -maxLeap; k <= maxLeap; k++)
                    {
                        for (int l = -(maxLeap - abs(k)); l <= maxLeap - abs(k); l++)
                        {
                            if ((k == 0 && l == 0) || pillar[i + k][j + l] == '0')
                                continue;
                            addEdge(getBlockId(i, j, OUT), getBlockId(i + k, j + l, IN), INT_MAX);
                        }
                    }
                }
            }
        }

        int ans = lizardNum - dinic(startPt, endPt);
        cout << "Case #" << t << ": ";
        if (ans == 0)
            cout << "no";
        else
            cout << ans;

        if (ans <= 1)
            cout << " lizard was";
        else
            cout << " lizards were";
        cout << " left behind." << endl;
    }
    return 0;
}
