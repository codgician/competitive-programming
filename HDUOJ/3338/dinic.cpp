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
#define MAT_SIZE 201
#define VERTEX_SIZE 40010
#define EDGE_SIZE 810000
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

string mat[MAT_SIZE][MAT_SIZE];
Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int row, column, vertexNum;

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int getBlockId(int i, int j)
{
    return i * column + j + 1;
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
            lastVisitedEdge[i] = head[i];
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
    while (cin >> row >> column)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> mat[i][j];
            }
        }

        int startPt = 0, endPt = ((row * column) << 1) + 1;
        vertexNum = endPt + 1;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (isDigit(mat[i][j][0]))
                {
                    int columnSum = (mat[i][j][0] - '0') * 100 + (mat[i][j][1] - '0') * 10 + (mat[i][j][2] - '0');
                    int blockNum = 0;
                    for (int k = i + 1; k < row; k++)
                    {
                        if (mat[k][j][0] == '.')
                        {
                            blockNum++;
                            addEdge(getBlockId(i, j), getBlockId(k, j), 8);
                        }
                        else
                        {
                            break;
                        }
                    }
                    addEdge(startPt, getBlockId(i, j), columnSum - blockNum);
                }
                if (isDigit(mat[i][j][4]))
                {
                    int rowSum = (mat[i][j][4] - '0') * 100 + (mat[i][j][5] - '0') * 10 + (mat[i][j][6] - '0');
                    int blockNum = 0;
                    for (int k = j + 1; k < column; k++)
                    {
                        if (mat[i][k][0] == '.')
                        {
                            blockNum++;
                            addEdge(getBlockId(i, k), getBlockId(i, j) + row * column, 8);
                        }
                        else
                        {
                            break;
                        }
                    }
                    addEdge(getBlockId(i, j) + row * column, endPt, rowSum - blockNum);
                }
            }
        }

        int ans = dinic(startPt, endPt);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                if (mat[i][j][0] == '.')
                {
                    int cntFlow = 0;
                    int edgePt = head[getBlockId(i, j)];
                    while (edgePt != -1)
                    {
                        if (!(edgePt & 1))
                        {
                            cntFlow += 8 - arr[edgePt].capacity;
                        }
                        edgePt = arr[edgePt].next;
                    }
                    cout << cntFlow + 1;
                }
                else
                {
                    cout << "_";
                }

                if (j < column - 1)
                    cout << " ";
                else
                    cout << endl;
            }
        }
    }
    return 0;
}
